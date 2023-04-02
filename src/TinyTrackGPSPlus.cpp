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

//#include <LowPower.h>

#include <DS3232RTC.h> 
#define USE_UINT64_T 1

#include <SDFat.h>
#include <sdios.h>

#define SD_FAT_TYPE 3
#define SPI_SPEED SD_SCK_MHZ(50)
#define SDCARD_SS_PIN (uint8_t)3U

#include "SAMDBattery.h"
#include <UTMConversion.h>
#include <TimeLib32.h>
#include <Timezone32.h>
#include "ConfigFile.h"
#include "Semphr.h"
#include "TimeZoneMapper.h"
#include "ahrs_ukf.h"
//#include "uNavINS.h"

// Definimos el Display
Display oled(SIZE_128X64);

// Definimos el MPU6050
//#include <MPU6050_light.h>
//MPU6050 mpu(Wire);

// Sensores instalados
#include "I2Cdev.h"
#include "BMP085.h"
#include "HMC5883L.h"
#include "MPU6050.h"
BMP085 barometer;
HMC5883L mag;
MPU6050 accelgyro(0x69);

// Definimos la conexion con el modulo Bluetooth hm11
SoftwareSerial BT(2,1);  // RX - 2, TX - 1 BT(recivePin,transmitPin)
bool bluetooth_connected = false;

SdFat card;   //SdFat.h library.
File32 file;
bool SDReady;
bool SaveOK;

// Variables y clases para obtener datos del GPS y conversion UTM.
static NMEAGPS gps;
static gps_fix gps_data;
static GPS_UTM utm;
struct pos_fix{
  long lati_L;
  long longi_L;
} REAL_POS;
double last_velocity;
#define KPH_TO_MPS 0.27777777777777777
//uNavINS Filter;

// Variables para configurar Timezone.
static TimeChangeRule UT = {"UTC", Last, Sun, Mar, 1, 0};     // UTC
static TimeChangeRule UST;
static Timezone TimeZone(UT);
static TimeChangeRule *trc;

#define TIMEZONE_FILE 2
#define TIMEZONE_ZONEMAPPER 1
#define TIMEZONE_UTC 0
int TimeZoneConfig;

Semphr drawBattery;
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
//time_t _utctime;    // El reloj lo establecemos siempre a UTC y ajustamos la hora local. 
time32_t _localtime;
time32_t _prevtime;
DS3232RTC rtc;
//unsigned long ti;


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
#define BAT_MAX  4.150

SAMDBattery vcc(PIN_BAT, VREF_BAT, RESISTOR_VDD, RESISTOR_GND, BAT_MIN, BAT_MAX);

int8_t charge_level(){
    if(vcc.GetVoltage() > BAT_MAX) return -1; // Está cargandose la batería.
    return (int8_t)(vcc.GetChargeLevel());
}

bool GPSData() {
  static bool save = false;
  char GPSLogFile[13];

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
  if (SDReady && (file.open(GPSLogFile, O_APPEND | O_WRITE))) {
    //Serial.print(F("Open GPSLogFile to write..."));
    char str[25];
    char comma = 0X2c;

    sprintf(str, "%02d:%02d:%02d", hour(_localtime), minute(_localtime), second(_localtime));
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
    
    file.print((gps_data.altitude_cm()/100));
    file.print(comma);
    sprintf(str, "%02d%c %ld %ld", utm.zone(), utm.band(), utm.X(), utm.Y());
    file.print(str);
    file.print("\n");
    file.close();
    save = true;
    //Serial.println(F("Done."));
  } //else {
    //Serial.println(F("** Error opening GPSLogFile. **"));
  //}
  //} //else Serial.println(F("** GPS signal lost. **"));
  return (save && SDReady);
}

void drawBatteryIcon(){
  oled.drawbattery(charge_level());
  //oled.drawiconbat(charge_level());
}

void BLE(){
  if (BT.availableForWrite()) BT.print("at\r\n");
  if (BT.available()){
    String c = BT.readString();
    String status = c.substring(7);
    Serial.println(c);
    Serial.println(status);
  }
}

void ScreenPrint(){
    char line[17];

    oled.clear();

      oled.print_date(_localtime);
      oled.print_time(trc->abbrev, _localtime);
      //BT.printf("%2.6f",vcc.GetVoltage());
      sprintf(line, "%02d%c ", utm.zone(), utm.band());
      //Serial.println(line); //
      oled.print(0,18,line);
      oled.print_UTM_x(utm.X());
      sprintf(line, "%02hu", gps_data.satellites);
      //Serial.println(line); //
      oled.print_PChar(2);
      oled.print(116,20,line);
      if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location) oled.print_PChar_sat(gps_data.satellites);
      else oled.print_PChar_Nosat();

      // New line
      oled.print_UTM_y(utm.Y());
      
      int32_t altitude = gps_data.altitude_cm()/100L;

      //uint8_t elev_n = (uint8_t)(altitude < 0) ? (-altitude) : altitude;
      sprintf(line, "%05ldm", altitude);
/*
      byte n = 1;
      while (elev_n > 9){
        elev_n /= 10;
        n++;
      }

      for(byte i = 5-n; i>0; i--) oled.print(9+i,1," ");
      if(altitude < 0) oled.print(15-n-1,1,"-");

      */
      oled.print_PChar(1);
      oled.print(92,32,line);
      //Serial.println(line); //

      /*
      if (elev < 10) oled.print(14,1,line);
      else if (elev < 100) oled.print(13,1,line);
      else if (elev < 1000) oled.print(12,1,line);
      else oled.print(11,1,line);
      */

      oled.print(0,44,"LAT:");
      //int int_lat = Filter.getLatitude_rad()*RAD_TO_DEG;
      //long f_lat = (Filter.getLatitude_rad()*RAD_TO_DEG - int_lat)*10000000L ;
      //sprintf(line, "%d.%07ld",int_lat, (int_lat > 0) ? f_lat : -(f_lat));
      int int_lat = gps_data.latitudeL() / 10000000L;
      sprintf(line, "%d.%07ld",int_lat, (int_lat > 0) ? gps_data.latitudeL()-(long)int_lat*10000000L : -(gps_data.latitudeL()-(long)int_lat*10000000L));
      //sprintf(line,"%f",Filter.getLatitude_rad()*RAD_TO_DEG);
      oled.print(21+(strlen(line)-8)*8,45,line);
      Serial.print("Latitude:\t");Serial.println(line); //

      oled.print(0,54,"LON:");
      //int int_lon = Filter.getLongitude_rad()*RAD_TO_DEG;
      //long f_lon = (Filter.getLongitude_rad()*RAD_TO_DEG - int_lon)*10000000L ;
      //sprintf(line, "%d.%07ld",int_lon, (int_lon > 0) ? f_lon : -(f_lon));  
      int int_lon = gps_data.longitudeL() / 10000000L;
      sprintf(line, "%d.%07ld",int_lon, (int_lon > 0) ? gps_data.longitudeL()-(long)int_lon*10000000L : -(gps_data.longitudeL()-(long)int_lon*10000000L));
      //sprintf(line,"%f",Filter.getLongitude_rad()*RAD_TO_DEG);
      oled.print(21+(strlen(line)-8)*8,55,line);
      Serial.print("Longitude:\t");Serial.println(line); //

/*
      dtostrf(gps_data.latitude(), 8, 7, line);
      oled.print(2,2,line);
      Serial.print("LAT=");
      Serial.println(line); //

      dtostrf(gps_data.longitude(), 8, 7, line);
      oled.print(2,3,line);
      Serial.print("LON=");
      Serial.println(line); //
    */
    
    int c = rtc.temperature();
    int celsius = (c >> 2);
    //DEBUG_PORT.println(celsius);
    sprintf(line,"%02d",celsius);
    oled.print(127-16,44,line);
    oled.print_PChar(6);
    
    drawBattery(drawBatteryIcon);
    (SaveOK) ? oled.print_PChar(3) : oled.print_PChar(4);
    if (bluetooth_connected) oled.print_PChar(5);
    oled.print_promt();
    //BLE();
    oled.draw();
}

time32_t gps_time_rtc(){
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
    rtc.set(gps_time_rtc());
    return gps_time_rtc();
  } else return rtc.get();
}

inline void update_time(){
  _localtime = TimeZone.toLocal(now(),&trc);
}

inline void sync_time(){
  setTime(gps_time());
  //Serial.println((long)gps_time());
  //rtc.set(now());
  //_localtime = TimeZone.toLocal(now(),&trc);
  update_time();
}

void setup(void) {
  delay(5000);
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  DEBUG_PORT.begin(115200); //115200

//---------------------------------------------------------------------------
// Este código escanea las direcciones del bus I2C.
//*
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
//*/

  // initialize MPU6050 device
  DEBUG_PORT.println("Initializing MPU6050 device...");
  //byte status = mpu.begin();
  DEBUG_PORT.print(F("MPU6050 status: "));
  //DEBUG_PORT.println(status);

  // Calibrando el sensor.
  
  DEBUG_PORT.println(F("Calculating offsets, do not move MPU6050"));
  //delay(1000);
  //mpu.calcOffsets(true,true); // gyro and accelero
  DEBUG_PORT.println("Done!\n");
  

  // Datos de calibracion del sensor.
  //mpu.setAccOffsets(0.03184131, 0.00907129, -1.92812943);
  //mpu.setGyroOffsets(0.79480880, 0.70482421, -0.24815249);

      //mpu.update();

  /* Inicialización del RTC DS3231 */
  rtc.begin();
  //setSyncProvider(gps_time);
  //setTime(rtc.get());
  //rtc.set(_localtime);

  BT.begin(9600);
  gpsPort.begin(9600); 

  /* Iniciaización del display oled u OLED */
  oled.start();
  
  //pinMode(A0,INPUT); // Initialized in class SAMDBattery.

  DEBUG_PORT.print(F("Initializing SD card...")); //

  SDReady = card.begin(SDCARD_SS_PIN, SPI_SPEED);
  (SDReady) ? Serial.println(F("Done.")) : Serial.println(F("FAILED!")); //
  
  // Config TimeZone (_localtime) with 'Time.cfg' file on SD.
  loadConfigurationProgram();
  //setTime(rtc.get());
  //sync_time();
  
  DEBUG_PORT.print(F("Waiting for GPS signal..."));
  
  unsigned int time = 0;

  vcc.analogRef(AR_DEFAULT);
  //vcc.analogRef(AR_INTERNAL1V65);
  vcc.setADCres(12);
  //vcc.setVref(3.3);
  //for(uint8_t i = 8; i--;) charge_level();

  bool config = false;
  setTime(rtc.get());
  if(timeStatus() != timeSet)
    DEBUG_PORT.println("Unable to sync with the RTC");
  else
    DEBUG_PORT.println("RTC has set the system time");
  DEBUG_PORT.println((long)now());
  _prevtime = now();

  /* Iniciaización del display oled u OLED */
  oled.start();

  do {
    if(BT.isListening()) bluetooth_connected = true;

    //delay(300);

    if((charge_level() < 5) && !(charge_level() < 0)) {
    oled.clear();
    oled.drawbattery(charge_level());
    oled.draw();
    do {
      delay(500);
      oled.clear();
      delay(500);
      oled.drawbattery(charge_level());
      oled.draw();
      } while(!(charge_level() > 4)) ;
    setup();
    }

    update_time();
    if(_prevtime < now()) {
      oled.clear();
      oled.print_date(_localtime);
      oled.print_time(trc->abbrev, _localtime);
      oled.drawbattery(charge_level());
      (SDReady) ? oled.print_PChar(3) : oled.print_PChar(4);
      if (bluetooth_connected) oled.print_PChar(5);
      oled.draw();
      oled.DrawLogo();
      oled.wait_anin(time++);
      _prevtime = now();



/*
    Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));
*/

    }

    //for (unsigned long start = millis(); millis() - start < 1000;) {
      while (gps.available(gpsPort)) {
        gps_data = gps.read();
        trace_all( DEBUG_PORT, gps, gps_data );  // uncomment this line if you want to see the GPS data flowing
        //Serial.write(c); 
        if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location) {// Did a new valid sentence come in?
          config = true;
          last_velocity = gps_data.speed_kph() * KPH_TO_MPS;
          setSyncProvider(gps_time);
          rtc.set(gps_time_rtc());
          //DEBUG_PORT.println((long)gps_time_rtc());
          //delay(100);
          //DEBUG_PORT.println((long)rtc.get());

        } //else config = false;
        //else setTime(rtc.get());
      }
    //}
  }while(!config);

  if(TimeZoneConfig == TIMEZONE_ZONEMAPPER) {
    TimeZoneMapper TimeZoneGPS;
    UST = TimeZoneGPS.latLongToTimezone_summer(gps_data.latitude(), gps_data.longitude());
    UT = TimeZoneGPS.latLongToTimezone(gps_data.latitude(), gps_data.longitude());
    TimeZone.setRules(UST, UT);
    update_time();
    //rtc.set(gps_time_rtc());
    DEBUG_PORT.print(F("Time configured."));
  }

  _prevtime = now();
  
  //kalmanX.setAngle(mpu.getAccAngleX()); // Set starting angle
  //kalmanY.setAngle(mpu.getAccAngleY());
  
  //DEBUG_PORT.println(F("Done."));
  DEBUG_PORT.println(F("Configuration ended.")); //
  oled.clear();
  //if (calibrate) ScreenPrintTest();

  //ti = micros();
  trace_header( DEBUG_PORT );
  DEBUG_PORT.flush();
}

void loop(void) {

  static bool needcharge = false;
  static uint8_t charge;
  uint8_t errorSD;
  //double X,Y;
  //static double dist_x = 0.0, dist_y = 0.0, dist_z = 0.0;
  //static double vel_x = 0.0, vel_y = 0.0, vel_z = 0.0;
/*
  double dT = (double)(micros() - ti) / 1000000; // Calculate delta time
  ti = micros();

  mpu.update();
  X = kalmanX.getAngle(mpu.getAccAngleX(),mpu.getGyroX(),dT);
  Y = kalmanY.getAngle(mpu.getAccAngleY(),mpu.getGyroY(),dT);

  Serial.println(X);
  Serial.println(Y);
  Serial.println(dT,6);
*/
/*
  mpu.fetchDataRaw();
  int acc_mov_x = acc_avg_x.reading(mpu.getAccXRaw());
  int acc_mov_y = acc_avg_y.reading(mpu.getAccYRaw());
  int acc_mov_z = acc_avg_z.reading(mpu.getAccZRaw());
  int gyro_mov_x = gyro_avg_x.reading(mpu.getGyroXRaw());
  int gyro_mov_y = gyro_avg_y.reading(mpu.getGyroYRaw());
  int gyro_mov_z = gyro_avg_z.reading(mpu.getGyroZRaw());

  if(_prevtime < now()) {
    
    double aT = (float)(now() - _prevtime)/(float)((n_x + n_y + n_z) / 3.0);
    int *acc_x = acc_avg_x.getReadings();  // returns a pointer to the readings
    int n_x = acc_avg_x.getCount();
    int *acc_y = acc_avg_y.getReadings();  // returns a pointer to the readings
    int n_y = acc_avg_y.getCount(); 
    int *acc_z = acc_avg_z.getReadings();  // returns a pointer to the readings
    int n_z = acc_avg_z.getCount();
    for(int i = 0; i < n_x; i++){
      vel_x += (float)(*acc_x++) / mpu.getAccConfig() - mpu.getAccXoffset() * aT;
      dist_x += vel_x * aT + 0.5 * ((float)(*acc_x++) / mpu.getAccConfig() - mpu.getAccXoffset()) * sq(aT);
    }
    for(int i = 0; i < n_y; i++){
      vel_y += (float)(*acc_y++) / mpu.getAccConfig() - mpu.getAccYoffset() * aT;
      dist_y += vel_y * aT + 0.5 * ((float)(*acc_y++) / mpu.getAccConfig() - mpu.getAccYoffset()) * sq(aT);
    }
    for(int i = 0; i < n_z; i++){
      vel_z += (float)(*acc_z++) / mpu.getAccConfig() - mpu.getAccZoffset() * aT;
      dist_z += vel_z * aT + 0.5 * ((float)(*acc_z++) / mpu.getAccConfig() - mpu.getAccZoffset()) * sq(aT);
    }
    
    float acc_mov_xf = ((float)acc_mov_x  / mpu.getAccConfig() - mpu.getAccXoffset())*(float)(now() - _prevtime);
    float dist_mov_xf = acc_mov_xf * (float)(now() - _prevtime) + 0.5 * ((float)acc_mov_x  / mpu.getAccConfig() - mpu.getAccYoffset())*sq((float)(now() - _prevtime));
    float acc_mov_yf = ((float)acc_mov_y  / mpu.getAccConfig() - mpu.getAccYoffset())*(float)(now() - _prevtime);
    float dist_mov_yf = acc_mov_yf * (float)(now() - _prevtime) + 0.5 * ((float)acc_mov_x  / mpu.getAccConfig() - mpu.getAccYoffset())*sq((float)(now() - _prevtime));
    float acc_mov_zf = ((float)acc_mov_z  / mpu.getAccConfig() - mpu.getAccZoffset())*(float)(now() - _prevtime);
    float dist_mov_zf = acc_mov_zf * (float)(now() - _prevtime) + 0.5 * ((float)acc_mov_x  / mpu.getAccConfig() - mpu.getAccYoffset())*sq((float)(now() - _prevtime));
*/
    //BT.print("Distancia X = ");/*Serial.print(dist_x,2);*/BT.print("\t");BT.println(dist_mov_xf,2);
    //BT.print("Distancia Y = ");/*Serial.print(dist_y,2);*/BT.print("\t");BT.println(dist_mov_yf,2);
    //BT.print("Distancia Z = ");/*Serial.print(dist_z,2);*/BT.print("\t");BT.println(dist_mov_zf,2);
/*
    dist_x = 0.0;
    dist_y = 0.0;
    dist_z = 0.0;

    acc_avg_x.reset();
    acc_avg_y.reset();
    acc_avg_z.reset();
  }
*/
  //mpu.update();

  if(BT.isListening()) bluetooth_connected = true;

  while (gps.available(gpsPort)) {
    gps_data = gps.read();
    trace_all( DEBUG_PORT, gps, gps_data );
    //trace_all(BT,gps,gps_data);
    //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
    if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location) {// Did a new valid sentence come in?
      update_time();
      drawBattery.set();
      drawDisplay.set();
      if(!SDReady) {
        SDReady = card.begin(SDCARD_SS_PIN, SPI_SPEED);
        if(SDReady) {
          loadConfigurationProgram();
          if(TimeZoneConfig == TIMEZONE_ZONEMAPPER) {
            TimeZoneMapper TimeZoneGPS;
            UT = TimeZoneGPS.latLongToTimezone(gps_data.latitude(), gps_data.longitude());
            UST = TimeZoneGPS.latLongToTimezone_summer(gps_data.latitude(), gps_data.longitude());
            TimeZone.setRules(UST, UT);
            update_time();
          }
        }
      }
    }
  }

  //Serial.println(_utctime);
  //Serial.println(_localtime);

  charge = charge_level();

  if (/*gps_data.valid.time && gps_data.valid.date && gps_data.valid.location &&*/ !(needcharge)) { 
   

    if (now() > _prevtime) {
      (!(errorSD = card.sdErrorCode())) ? SDReady = true : SDReady = false;
      if (errorSD == 11) card.end();
      //Serial.println(errorSD);
      if (!errorSD) SaveOK = GPSData();
      else SaveOK = false;
      _prevtime = now();
      update_time();
      drawBattery.set();
      drawDisplay.set();
/*
          Filter.update(gps_data.dateTime_us(),    // Marca de tiempo.
                        gps_data.velocity_north/100.0, 
                        gps_data.velocity_east/100.0, 
                        gps_data.velocity_down/100.0, 
                        gps_data.latitude()*DEG_TO_RAD,   // Radianes
                        gps_data.longitude()*DEG_TO_RAD,  // Radianes
                        gps_data.altitude_cm()/100L, 
                        mpu.getGyroY()*DEG_TO_RAD, 
                        -1*mpu.getGyroX()*DEG_TO_RAD, 
                        mpu.getGyroZ()*DEG_TO_RAD, 
                        mpu.getAccY()*9.807f, 
                        -1*mpu.getAccX()*9.807f, 
                        mpu.getAccZ()*9.807f,
                        0.88,30.35,32.31); 
                        //205.16,37.72,410.32);
                        //Imu.getMagX_uT(), 
                        //Imu.getMagY_uT(), 
                        //Imu.getMagZ_uT());
          */
    //utm.UTM((long)(Filter.getLatitude_rad()*RAD_TO_DEG*10000000.0), (long)(Filter.getLongitude_rad()*RAD_TO_DEG*10000000.0));
    utm.UTM(gps_data.latitudeL(),gps_data.longitudeL());
    drawDisplay(ScreenPrint);
    }
  }
  else if (charge==0){
    while (charge < 5) {
      oled.clear();
      delay(500);
      oled.print_date(_localtime);
      oled.print_time(trc->abbrev, _localtime);
      oled.drawbattery(charge_level());
      charge = charge_level();
    }
      
      needcharge = true;
  }
  else {
    if (now() > _prevtime) {
      _prevtime = now();
      update_time();
      drawBattery.set();
      drawDisplay.set();
      drawDisplay(ScreenPrint);
    }
  }

/*
  if((charge==0) && bitRead(millis(),9))
    drawBattery.set();
  else if((millis()&0x1ff) == 0x1ff)
    drawBattery.set();
  */
  //drawDisplay(ScreenPrint);

  if(needcharge) (charge > 5) ? needcharge = false : needcharge = true;
  /*
  rtc.setAlarmTime(17, 00, 10);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);

  rtc.attachInterrupt(alarmMatch);
  rtc.standbyMode();
  */
}
