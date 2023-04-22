/*
TinyTrackGPSPlus.cpp - A simple track GPS to SD card logger.
TinyTrackGPSPlus v1.0

Copyright © 2023 Francisco Rafael Reyes Carmona.
All rights reserved.

rafael.reyes.carmona@gmail.com

  This file is part of TinyTrackGPSPlus.

  TinyTrackGPSPlus is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  TinyTrackGPSPlus is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with TinyTrackGPSPlus.  If not, see <https://www.gnu.org/licenses/>.
*/

/****************************************************************************
/  Programa de localizacion por gps que graba las posiciones en
/  un fichero de texto cada segundo, de forma diaria.
/
/  - Conectar módulo SD con pin CS (naranja) en pin 10 arduino.
/   
/  Uso de librería TinyGPS.
/   Requiere uso de librería SoftwareSerial, se presupone que disponemos
/   de un dispositivo GPS serie de 9600-bauds conectado en pines 9(rx) y 8(tx).
/  - Conectar módulo NMEA-6M (gps) pines 8,9 (9 - pin rx negro)
/
/  - Conectar OLED 0.96" en SDA y SCL. pines A4 y A5 del Arduino UNO.
********************************************************************************/

// Include libraries.
#include <Arduino.h>
#include <SPI.h>
#include "config.h"
#include "Display.h"
#include <SoftwareSerial.h>

#include <Wire.h>

#include <NMEAGPS.h>
#include <GPSport.h>
#include <GPSfix.h>
#include <Streamers.h>

#include <DS3232RTC.h> 
#define USE_UINT64_T 1

#define SD_FAT_TYPE 3
#define SPI_SPEED SD_SCK_MHZ(24)
#define SDCARD_SS_PIN (uint8_t)3U
//#define SPI_DRIVER_SELECT 2
#include <SDFat.h>
#include <sdios.h>
#define SD_CONFIG SdSpiConfig(SDCARD_SS_PIN, DEDICATED_SPI, SPI_SPEED)
const uint8_t CardDetect = 1U;
bool CardInserted;

#include "SAMDBattery.h"
#include <UTMConversion.h>
#include <TimeLib32.h>
#include <Timezone32.h>
#include "ConfigFile.h"
#include "Semphr.h"
#include "TimeZoneMapper.h"
#include <elapsedMillis.h>

elapsedMillis timerdeltatime = 0;
enum {
  STARTING,
  GPS_WAITING,
  GPS_OK,
} STATE;

#include "Fusion.h"
#define SAMPLE_RATE (30) // replace this with actual sample rate (Hz) Samples per second.
#define SAMPLE_MILIS (float)(1.0/SAMPLE_RATE*1000.0)  /* ms */
//#define SS_DT       (float)(SS_DT_MILIS/1000.0)   /* Sampling time */

const FusionMatrix gyroscopeMisalignment =      {1.0f, 0.0f, 0.0f, 
                                                 0.0f, 1.0f, 0.0f, 
                                                 0.0f, 0.0f, 1.0f};
const FusionVector gyroscopeSensitivity =       {1.0f, 1.0f, 1.0f};
const FusionVector gyroscopeOffset =            {0.0f, 0.0f, 0.0f};
const FusionMatrix accelerometerMisalignment =  {1.0f, 0.0f, 0.0f, 
                                                 0.0f, 1.0f, 0.0f, 
                                                 0.0f, 0.0f, 1.0f};
const FusionVector accelerometerSensitivity =   {1.0f, 1.0f, 1.0f};
const FusionVector accelerometerOffset =        {0.0f, 0.0f, 0.0f};
const FusionMatrix softIronMatrix =             { 1.0f, 0.0f, 0.0f, 
                                                 0.0f, 1.0f, 0.0f, 
                                                 0.0f, 0.0f, 1.0f};
const FusionVector hardIronOffset =             {0.0f, 0.0f, 0.0f};
// Initialise algorithms
FusionOffset offset;
FusionAhrs ahrs;
// Set AHRS algorithm settings
const FusionAhrsSettings settings = {
  .convention = FusionConventionNed,
  .gain = 0.5f,
  .accelerationRejection = 10.0f,
  .magneticRejection = 20.0f,
  .rejectionTimeout = 5 * SAMPLE_RATE, /* 5 seconds */
};

// Definimos el Display
Display oled(SIZE_128X64);

// Sensores instalados
#include <SFE_BMP180.h>
#include <QMC5883LCompass.h>
#include <MPU6050_light.h>
SFE_BMP180 pressure;
QMC5883LCompass compass;
MPU6050 mpu(Wire);
// const uint8_t MPUStatus_DMP = 2U; // Esta en estudio el uso del DMP.
double barometer_Alt;

// Definimos la conexion con el modulo Bluetooth hm11
//SoftwareSerial BT(2,1);  // RX - 2, TX - 1 BT(recivePin,transmitPin)
//bool bluetooth_connected = false;

SPISettings SPI_settings = SPISettings(250000,MSBFIRST,SPI_MODE0);
SdFat card;   //SdFat.h library.
File32 file;
bool SDReady;
bool SaveOK;

// Variables y clases para obtener datos del GPS y conversion UTM.
static NMEAGPS gps;
static gps_fix gps_data;
static GPS_UTM utm;
bool gps_signal;

// Variables para configurar Timezone.
static TimeChangeRule UT = {"UTC", Last, Sun, Mar, 1, 0};     // UTC
static TimeChangeRule UST;
static Timezone TimeZone(UT);
static TimeChangeRule *trc;

#define TIMEZONE_FILE 2
#define TIMEZONE_ZONEMAPPER 1
#define TIMEZONE_UTC 0
int TimeZoneConfig;

//Semphr drawBattery;
Semphr drawDisplay;

// Loads the configuration from a file
bool loadConfiguration(TimeChangeRule *UST,TimeChangeRule *UT) {

  boolean file;
  uint8_t read = 0;
  ConfigFile<12> TimeConf;

  if((file = TimeConf.begin("Time.cfg"))){
    while(TimeConf.readNextSetting()){
    
      char opt[5];
      strcpy(opt,TimeConf.getName());

      if (!strcmp(opt,"USTw")) {
        read++;
        UST->week = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"USTd")) {
        read++;
        UST->dow = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"USTm")) {
        read++;
        UST->month = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"USTh")) {
        read++;
        UST->hour = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"USTo")) {
        read++;
        UST->offset = TimeConf.getIntValue();
      }
    
      else if (!strcmp(opt,"UTw")) {
        read++;
        UT->week = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"UTd")) {
        read++;
        UT->dow = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"UTm")) {
        read++;
        UT->month = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"UTh")) {
        read++;
        UT->hour = TimeConf.getIntValue();
      }
      else if (!strcmp(opt,"UTo")) {
        read++;
        UT->offset = TimeConf.getIntValue();
      }
    /*
    // Put a nameIs() block here for each setting you have.
    //if(TimeConf.nameIs("USTabbre"))
    //  strcpy(UST.abbrev,"UST");

    if(TimeConf.nameIs("USTw"))
      UST->week = TimeConf.getIntValue();
    else if(TimeConf.nameIs("USTd"))
      UST->dow = TimeConf.getIntValue();
    else if(TimeConf.nameIs("USTm"))
      UST->month = TimeConf.getIntValue();
    else if(TimeConf.nameIs("USTh"))
      UST->hour = TimeConf.getIntValue();
    else if(TimeConf.nameIs("USTo"))
      UST->offset = TimeConf.getIntValue();

    //else if(TimeConf.nameIs("UTabbre"))
    //  strcpy(UST.abbrev,"UT");
    else if(TimeConf.nameIs("UTw"))
      UT->week = TimeConf.getIntValue();
    else if(TimeConf.nameIs("UTd"))
      UT->dow = TimeConf.getIntValue();
    else if(TimeConf.nameIs("UTm"))
      UT->month = TimeConf.getIntValue();
    else if(TimeConf.nameIs("UTh"))
      UT->hour = TimeConf.getIntValue();
    else if(TimeConf.nameIs("UTo"))
      UT->offset = TimeConf.getIntValue();
    */
    strcpy(UST->abbrev,"UST");
    strcpy(UT->abbrev,"UT");
    }
  }
  TimeConf.end();

  //Serial.print(UST->offset);
  //Serial.println(UST->abbrev);
  //Serial.print(UT->offset);
  //Serial.println(UT->abbrev);

  if(read == 10) return true;
  return false;
}

void loadConfigurationProgram() {
  boolean file;
  ConfigFile<15> ConfProg;
  if((file = ConfProg.begin("ConfProg.cfg"))){
    while(ConfProg.readNextSetting()){
      char opt[9];
      strcpy(opt,ConfProg.getName());
      if (!strcmp(opt,"TIMEZONE")) {
        TimeZoneConfig = ConfProg.getIntValue();
      }
    }
  } 
  else TimeZoneConfig = TIMEZONE_UTC;
  
  ConfProg.end();

  if(TimeZoneConfig == TIMEZONE_FILE) 
    if(loadConfiguration(&UST,&UT)) TimeZone.setRules(UST,UT);
}

// Variables para gestionar el tiempo local.
TimeElements time_gps;
time32_t _time_gps;
//time_t _utctime;    // El reloj lo establecemos siempre a UTC y ajustamos la hora local. 
time32_t _localtime;
time32_t _prevtime;
DS3232RTC rtc;

//------------------------------------------------------------------------------
/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
void dateTime(uint16_t* date, uint16_t* time) {
  // User gets date and time from GPS or real-time
  // clock in real callback function

  // return date using FAT_DATE macro to format fields
  //*date = FAT_DATE(year, month, day);
  *date = (year(_localtime)-1980) << 9 | month(_localtime) << 5 | day(_localtime);

  // return time using FAT_TIME macro to format fields
  //*time = FAT_TIME(hour, minute, second);
  *time = hour(_localtime) << 11 | minute(_localtime) << 5 | second(_localtime) >> 1;
}
//------------------------------------------------------------------------------

#define PIN_BAT A0
#define VREF_BAT 3300.0
#define RESISTOR_VDD  21600L  // Valor de resistencia medida con polimetro.
#define RESISTOR_GND  47100L  // Valor de resistencia medida con polimetro.
#define BAT_MIN  3.500
#define BAT_MAX  4.250

SAMDBattery vcc(PIN_BAT, VREF_BAT, RESISTOR_VDD, RESISTOR_GND, BAT_MIN, BAT_MAX);

int8_t charge_level(){
    if(vcc.GetVoltage() > BAT_MAX) return -1; // Está cargandose la batería.
    return (int8_t)(vcc.GetChargeLevel());
}

inline time32_t gps_time_rtc(){
  time_gps.Year = gps_data.dateTime.full_year() - 1970;
  time_gps.Month = gps_data.dateTime.month;
  time_gps.Day = gps_data.dateTime.date;
  time_gps.Hour = gps_data.dateTime.hours;
  time_gps.Minute = gps_data.dateTime.minutes;
  time_gps.Second = gps_data.dateTime.seconds;
  return makeTime(time_gps);
}

time32_t gps_time(){
  //static TimeElements time_gps;
  if (gps_data.valid.time && gps_data.valid.date){
    _time_gps = gps_time_rtc();
    rtc.set(_time_gps);
    return _time_gps;
  } else return rtc.get();
}

inline void update_time(){
  _localtime = TimeZone.toLocal(now(),&trc);
}

inline void sync_time(){
  setTime(gps_time());
  //Serial.println((long)gps_time());
  update_time();
}

bool GPSData() {
  static bool save = false;
  char GPSLogFile[14];
  uint8_t errorSD;

  sprintf(GPSLogFile, "%04d%02d%02d.csv", year(_localtime), month(_localtime), day(_localtime));

  //SdFile::dateTimeCallback(dateTime);
  FsDateTime::setCallback(dateTime);
  
  // Si no existe el fichero lo crea y añade las cabeceras.
  if (SDReady && !card.exists(GPSLogFile)) {
    if (file.open(GPSLogFile, O_CREAT | O_APPEND | O_WRITE)) {
      //Serial.print(F("New GPSLogFile, adding heads..."));
      file.println(F("Time,Latitude,Longitude,Elevation,UTM Coords(WGS84)"));
      //Serial.println(F("Done."));
      file.close();
      }
      //else {
      //Serial.println(F("** Error creating GPSLogFile. **"));
      //}
  }
  if (SDReady && (save=file.open(GPSLogFile, O_APPEND | O_WRITE))) {
    //Serial.print(F("Open GPSLogFile to write..."));
    char str[25];
    char comma = 0X2c;

    //sprintf(str, "%02d:%02d:%02d", hour(_localtime), minute(_localtime), second(_localtime));
    time32_t save_time_gps = _time_gps; // ------>  gps_time_rtc();
    time32_t save_time_local = TimeZone.toLocal(save_time_gps);
    sprintf(str, "%02d:%02d:%02d.%03d", hour(save_time_local), minute(save_time_local), second(save_time_local),gps_data.dateTime_cs);
    file.print(str);
    file.print(comma);

    //int int_lat = Filter.getLatitude_rad()*RAD_TO_DEG;
    //long f_lat = (Filter.getLatitude_rad()*RAD_TO_DEG - int_lat)*10000000L ;
    //sprintf(str, "%d.%07ld",int_lat, (int_lat > 0) ? f_lat : -(f_lat));
    int int_lat = gps_data.latitudeL() / 10000000L;
    sprintf(str, "%d.%07ld",int_lat, (int_lat > 0) ? gps_data.latitudeL()-(long)int_lat*10000000L : -(gps_data.latitudeL()-(long)int_lat*10000000L));
    file.print(str);
    file.print(comma);

    //int int_lon = Filter.getLongitude_rad()*RAD_TO_DEG;
    //long f_lon = (Filter.getLongitude_rad()*RAD_TO_DEG - int_lon)*10000000L ;
    //sprintf(str, "%d.%07ld",int_lon, (int_lon > 0) ? f_lon : -(f_lon));    
    int int_lon = gps_data.longitudeL() / 10000000L;
    sprintf(str, "%d.%07ld",int_lon, (int_lon > 0) ? gps_data.longitudeL()-(long)int_lon*10000000L : -(gps_data.longitudeL()-(long)int_lon*10000000L));
    file.print(str);
    file.print(comma);
    
    //file.print((gps_data.altitude_cm()/100));
    file.print(barometer_Alt,2);
    file.print(comma);
    sprintf(str, "%02d%c %ld %ld", utm.zone(), utm.band(), utm.X(), utm.Y());
    file.print(str);
    file.print("\n");
    file.close();
    save = true;
    //Serial.println(F("Done."));
  } //else {
    //Serial.println(F("** Error opening GPSLogFile. **"));
  (!(errorSD = card.sdErrorCode())) ? SDReady = true : SDReady = false;
  if (errorSD == 11) card.end();
  return (save && SDReady);
}

void ScreenPrint(){
  char line[17];

  oled.clear();

  oled.print_date(_localtime);
  oled.print_time(trc->abbrev, _localtime);
  //Serial.printf("%2.6f",vcc.GetVoltage());
  sprintf(line, "%02d%c ", utm.zone(), utm.band());
  //Serial.println(line); //
  oled.print(0,18,line);
  oled.print_UTM_x(utm.X());
  sprintf(line, "%02hu", gps_data.satellites);
  //Serial.println(line); //
  oled.print_PChar(2);
  oled.print(116,20,line);
  if (gps_data.status == gps_fix::status_t::STATUS_STD) oled.print_PChar_sat(gps_data.satellites);
    else oled.print_PChar_Nosat();

  // New line
  oled.print_UTM_y(utm.Y());
      
  //int32_t altitude = gps_data.altitude_cm()/100L;
  int32_t altitude = barometer_Alt;

  //uint8_t elev_n = (uint8_t)(altitude < 0) ? (-altitude) : altitude;
  sprintf(line, "%05ldm", altitude);
  oled.print_PChar(1);
  oled.print(92,32,line);
  //Serial.println(line); //

  oled.print(0,44,"LAT:");
  //int int_lat = Filter.getLatitude_rad()*RAD_TO_DEG;
  //long f_lat = (Filter.getLatitude_rad()*RAD_TO_DEG - int_lat)*10000000L ;
  //sprintf(line, "%d.%07ld",int_lat, (int_lat > 0) ? f_lat : -(f_lat));
  int int_lat = gps_data.latitudeL() / 10000000L;
  sprintf(line, "%d.%07ld",int_lat, (int_lat > 0) ? gps_data.latitudeL()-(long)int_lat*10000000L : -(gps_data.latitudeL()-(long)int_lat*10000000L));
  //sprintf(line,"%f",Filter.getLatitude_rad()*RAD_TO_DEG);
  oled.print(21+(strlen(line)-8)*8,45,line);
  //Serial.print("Latitude:\t");Serial.println(line); //

  oled.print(0,54,"LON:");
  //int int_lon = Filter.getLongitude_rad()*RAD_TO_DEG;
  //long f_lon = (Filter.getLongitude_rad()*RAD_TO_DEG - int_lon)*10000000L ;
  //sprintf(line, "%d.%07ld",int_lon, (int_lon > 0) ? f_lon : -(f_lon));  
  int int_lon = gps_data.longitudeL() / 10000000L;
  sprintf(line, "%d.%07ld",int_lon, (int_lon > 0) ? gps_data.longitudeL()-(long)int_lon*10000000L : -(gps_data.longitudeL()-(long)int_lon*10000000L));
  //sprintf(line,"%f",Filter.getLongitude_rad()*RAD_TO_DEG);
  oled.print(21+(strlen(line)-8)*8,55,line);
  //Serial.print("Longitude:\t");Serial.println(line); //
    
  int c = rtc.temperature();
  int celsius = (c >> 2);
  //Serial.println(celsius);
  sprintf(line,"%02d",celsius);
  oled.print(127-16,44,line);
  oled.print_PChar(6);
    
  //drawBattery(drawBatteryIcon);
  oled.drawbattery(charge_level());

  (SaveOK) ? oled.print_PChar(3) : oled.print_PChar(4);
  //if (bluetooth_connected) oled.print_PChar(5); // No tiene módulo Bluetooth.
  oled.print_promt();
  oled.draw();
}

void calc_altitude(){
  char status;
  double barometer_T;
  double barometer_P;

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);
    status = pressure.getTemperature(barometer_T);
    if (status != 0)
    {
      status = pressure.startPressure(2);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);
        status = pressure.getPressure(barometer_P,barometer_T);
        if (status != 0)
        {
          barometer_Alt = pressure.altitude(barometer_P,1023.25);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  /* ------- Códigos de ejemplo para calcular la altura en funcion de la presion (mbar)-------
  // barometer_Alt = (1-pow(barometer_P/1023.25,0.190284))*44307.69396; //(145366.45*0.3048)
  // barometer_Alt = -8434.6677992257846160657 * log(barometer_P / 1013.25);
  // barometer_Alt = log(1013.25/barometer_P)*7238.003;
  // -----------------------------------------------------------------------------------------
  */

  //double alt_dif = barometer_Alt - gps_data.altitude();
  //barometer_Alt -= alt_dif;  
  //barometer_Alt += gps_data.altitude();
  //barometer_Alt /= 2;
}

inline bool CardChange() {
  bool CardStatus;
  bool change;
  CardStatus = digitalRead(CardDetect);
  change = CardInserted ^ CardStatus;
  if(change) {
    CardInserted = CardStatus;
    //Serial.println("Card has change!");
    //Serial.print("Satus ");Serial.println(CardInserted);
  }
  return change;
}

inline void CardDetectFunction() {
  if(CardInserted) {
    //Serial.print(F("SD card detect...")); //
    delay(500);
    SDReady = card.begin(SD_CONFIG);
    //(SDReady) ? Serial.println(F("Done.")) : Serial.println(F("FAILED!")); //
    loadConfigurationProgram();
    if(TimeZoneConfig == TIMEZONE_ZONEMAPPER) {
      TimeZoneMapper TimeZoneGPS;
      UT = TimeZoneGPS.latLongToTimezone(gps_data.latitude(), gps_data.longitude());
      UST = TimeZoneGPS.latLongToTimezone_summer(gps_data.latitude(), gps_data.longitude());
      TimeZone.setRules(UST, UT);
      update_time();
    }
  } else {
    Serial.print(F("SD card... REMOVED!")); //
    card.end();
    SDReady = false;
  }
}

void setup(void) {
  pinMode(CardDetect, INPUT_PULLDOWN);
  CardInserted = digitalRead(CardDetect);
  //attachInterrupt(digitalPinToInterrupt(CardDetect), CardDetectFunction, CHANGE);
  
  delay(10);
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  delay(10);
  Serial.begin(115200); //115200

//---------------------------------------------------------------------------
// Este código escanea las direcciones del bus I2C.
/*
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
//-------------------------------------------------------------------------
*/

  /* Inicialización del RTC DS3231 */
  rtc.begin();
  setTime(rtc.get());
  _prevtime = now();

  if(timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");
  Serial.println((long)now());

  // Inicializacion del sensor de presión BMP180.
  bool pressure_success = pressure.begin();
  Serial.print("Initializing BMP180 device... ");
  if (pressure_success) Serial.println("success!");
  else Serial.println("FAULT!!!\nBMP180 init fail (disconnected?)\n\n");

      // initialize MPU6050 device
  Serial.println("Initializing MPU6050 device...");
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  
  // Calibrando el sensor.
  //Serial.println(F("Calculating offsets, do not move MPU6050"));
  //delay(1000);
  //mpu.calcOffsets(true,true); // gyro and accelero
  //Serial.println("Done!\n");
  
  // Datos de calibracion del sensor.
  mpu.setAccOffsets(0.03184131, 0.00907129, -1.92812943);
  mpu.setGyroOffsets(0.79480880, 0.70482421, -0.24815249);

  mpu.update();

  compass.init();
  compass.setCalibration(-1153082723, 999124224, -2111, 820, -1390, 1133314048);
  //compass.setSmoothing(5, true);
  compass.read();

// Rutina para calibracion del magnetrometro.------------------------
/*
  Serial.println("This will provide calibration settings for your QMC5883L chip. When prompted, move the magnetometer in all directions until the calibration is complete.");
  Serial.println("Calibration will begin in 5 seconds.");
  delay(5000);
  int x, y, z;
  int calibrationData[3][2];
  bool changed = false;
  bool done = false;
  int t = 0;
  int c = 0;
  do{  
  // Read compass values
  compass.read();

  // Return XYZ readings
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();

  changed = false;

  if(x < calibrationData[0][0]) {
    calibrationData[0][0] = x;
    changed = true;
  }
  if(x > calibrationData[0][1]) {
    calibrationData[0][1] = x;
    changed = true;
  }

  if(y < calibrationData[1][0]) {
    calibrationData[1][0] = y;
    changed = true;
  }
  if(y > calibrationData[1][1]) {
    calibrationData[1][1] = y;
    changed = true;
  }

  if(z < calibrationData[2][0]) {
    calibrationData[2][0] = z;
    changed = true;
  }
  if(z > calibrationData[2][1]) {
    calibrationData[2][1] = z;
    changed = true;
  }

  if (changed && !done) {
    Serial.println("CALIBRATING... Keep moving your sensor around.");
    c = millis();
  }
    t = millis();
  
  
  if ( (t - c > 5000) && !done) {
    done = true;
    Serial.println("DONE. Copy the line below and paste it into your projects sketch.);");
    Serial.println();
      
    Serial.print("compass.setCalibration(");
    Serial.print(calibrationData[0][0]);
    Serial.print(", ");
    Serial.print(calibrationData[0][1]);
    Serial.print(", ");
    Serial.print(calibrationData[1][0]);
    Serial.print(", ");
    Serial.print(calibrationData[1][1]);
    Serial.print(", ");
    Serial.print(calibrationData[2][0]);
    Serial.print(", ");
    Serial.print(calibrationData[2][1]);
    Serial.println(");");
    }
  }while(!done);
*/
//Rutina calibracion magnetrometro.----------------------------------------

  //BT.begin(9600); 
  gpsPort.begin(9600); 

  /* Iniciaización del display oled u OLED */
  oled.start();
  
  //pinMode(A0,INPUT); // Initialized in class SAMDBattery.

  Serial.print(F("Initializing SD card...")); //
  SDReady = card.begin(SD_CONFIG);
  (SDReady) ? Serial.println(F("Done.")) : Serial.println(F("FAILED!")); //
  
  // Config TimeZone (_localtime) with 'Time.cfg' file on SD.
  loadConfigurationProgram();
  
  vcc.analogRef(AR_DEFAULT);
  vcc.setADCres(12);

  /* Iniciaización del display oled u OLED */
  oled.start();

  if(vcc.GetChargeLevel() < 5) {
    oled.clear();
    oled.drawbattery(vcc.GetChargeLevel());
    oled.draw();
    do {
      delay(500);
      oled.clear();
      delay(500);
      oled.drawbattery(vcc.GetChargeLevel());
      oled.draw();
      } while(vcc.GetChargeLevel() < 5);
    //setup();
    }

  STATE = STARTING;
  
  FusionOffsetInitialise(&offset, SAMPLE_RATE);
  FusionAhrsInitialise(&ahrs);
  FusionAhrsSetSettings(&ahrs, &settings);

  Serial.print(F("Waiting for GPS signal..."));
}

void loop(void) {
  static bool needcharge = false;
  static uint8_t charge;
  uint8_t errorSD;

  if(timerdeltatime >= SAMPLE_MILIS){
    timerdeltatime = 0;

    // Read mpu and compass values
    mpu.update();
    compass.read();

    // Acquire latest sensor data
    const clock_t timestamp = micros(); // replace this with actual gyroscope timestamp
    FusionVector gyroscope = {mpu.getGyroX(), mpu.getGyroY(), mpu.getGyroZ()}; // replace this with actual gyroscope data in degrees/s
    FusionVector accelerometer = {mpu.getAccX(), mpu.getAccY(), mpu.getAccZ()}; // replace this with actual accelerometer data in g
    FusionVector magnetometer = {(float)compass.getX(), (float)compass.getY(), (float)compass.getZ()}; // replace this with actual magnetometer data in arbitrary units

    //FusionVector GPS = {gps_data.latitude(), gps_data.longitude(), gps_data.heading()};
    //FusionVector GPS_err = {gps_data.lat_err(), gps_data.lon_err(), gps_data.hdg_err()};
    //FusionVector velocity = {gps_data.velocity_north/100.0f, gps_data.velocity_east/100.0f, gps_data.speed()};

    // Apply calibration
    gyroscope = FusionCalibrationInertial(gyroscope, gyroscopeMisalignment, gyroscopeSensitivity, gyroscopeOffset);
    accelerometer = FusionCalibrationInertial(accelerometer, accelerometerMisalignment, accelerometerSensitivity, accelerometerOffset);
    magnetometer = FusionCalibrationMagnetic(magnetometer, softIronMatrix, hardIronOffset);

    // Update gyroscope offset correction algorithm
    gyroscope = FusionOffsetUpdate(&offset, gyroscope);

    // Calculate delta time (in seconds) to account for gyroscope sample clock error
    static clock_t previousTimestamp;
    const float deltaTime = (float) (timestamp - previousTimestamp) / (/*(float) CLOCKS_PER_SEC */ 1000000.0);
    previousTimestamp = timestamp;

    // Update gyroscope AHRS algorithm
    FusionAhrsUpdate(&ahrs, gyroscope, accelerometer, magnetometer, deltaTime);

    // Print algorithm outputs
    const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
    const FusionVector earth = FusionAhrsGetEarthAcceleration(&ahrs);
    //const FusionQuaternion quad = FusionAhrsGetQuaternion(&ahrs);
    //const FusionVector accel = FusionAhrsGetLinearAcceleration(&ahrs);
    Serial.print("Roll:  ");Serial.print(euler.angle.roll,2);Serial.print(",\t");
    Serial.print("Pitch: ");Serial.print(euler.angle.pitch,2);Serial.print(",\t");
    Serial.print("Yaw: ");Serial.print(euler.angle.yaw,2);Serial.print(",\t-> ");
    Serial.print("X: ");Serial.print(earth.axis.x,2);Serial.print(", \t");
    Serial.print("Y: ");Serial.print(earth.axis.y,2);Serial.print(", \t");
    Serial.print("Z: ");Serial.print(earth.axis.z,2);Serial.print("\r");
  }

  //if(BT.isListening()) bluetooth_connected = true;

  charge = charge_level();
  (charge > 5) ? needcharge = false : needcharge = true;

  if(CardChange()) CardDetectFunction();

  while (gps.available(gpsPort)) {
    gps_data = gps.read();
    //Serial.println();
    //trace_all( Serial, gps, gps_data );  // uncomment this line if you want to see the GPS data flowing
  }

  if(STATE == STARTING) {
    update_time();
    if(_prevtime < now()) {
      oled.clear();
      oled.print_date(_localtime);
      oled.print_time(trc->abbrev, _localtime);
      oled.drawbattery(charge_level());
      (SDReady) ? oled.print_PChar(3) : oled.print_PChar(4);
      //if (bluetooth_connected) oled.print_PChar(5);  // No tiene módulo Bluetooth.
      oled.draw();
      oled.DrawLogo();
      oled.wait_anin(_prevtime);
      _prevtime = now(); ///----------------
    }
    if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location) {// Did a new valid sentence come in?
      
      setSyncProvider(gps_time);
      gps_time(); // ---->  rtc.set(gps_time_rtc());
      Serial.println((long)_time_gps);

      if(TimeZoneConfig == TIMEZONE_ZONEMAPPER) {
        TimeZoneMapper TimeZoneGPS;
        UST = TimeZoneGPS.latLongToTimezone_summer(gps_data.latitude(), gps_data.longitude());
        UT = TimeZoneGPS.latLongToTimezone(gps_data.latitude(), gps_data.longitude());
        TimeZone.setRules(UST, UT);
        update_time();
        Serial.print(F("Time configured."));
      }
      Serial.println(F("Done."));
      Serial.println(F("Configuration ended.")); //
      oled.clear();

      trace_header( Serial );
      Serial.flush();

      STATE = GPS_WAITING;
    }
    _prevtime = now();
  } else if(STATE == GPS_WAITING) {
    if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location) {// Did a new valid sentence come in?
      _time_gps = gps_time_rtc();
      update_time();
      //drawBattery.set();
      drawDisplay.set();
      utm.UTM(gps_data.latitudeL(),gps_data.longitudeL());
      STATE = GPS_OK;
    } else {
      if (now() > _prevtime) {
        calc_altitude();
        _prevtime = now();
        update_time();
        //drawBattery.set();
        drawDisplay.set();
        drawDisplay(ScreenPrint);
      }
    }
  } else if(STATE == GPS_OK) {
    if (/*gps_data.valid.time && gps_data.valid.date && gps_data.valid.location &&*/ !(needcharge)) { 
      if (now() > _prevtime) {
        _prevtime = now();
        update_time();
        calc_altitude();
        (!(errorSD = card.sdErrorCode())) ? SDReady = true : SDReady = false;
        if (errorSD == 11) card.end();
        //Serial.println(errorSD);
        SaveOK = (SDReady) ? GPSData() : false;
        //drawBattery.set();
        drawDisplay.set();
        drawDisplay(ScreenPrint);
      }
      STATE = GPS_WAITING;
    } else {
      needcharge = true;
      while (needcharge) {
        _prevtime = now();
        update_time();
        oled.clear();
        oled.print_date(_localtime);
        oled.print_time(trc->abbrev, _localtime);
        charge = charge_level();
        oled.drawbattery(charge_level());
        oled.draw();
        delay(500);
        oled.DrawLowBat();
        oled.draw();
        (charge_level() > 5 || charge_level() < 0) ? needcharge = false : needcharge = true;
      }
      needcharge = false;
      STATE = GPS_WAITING;
    }
  }

}
