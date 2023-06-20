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
#define SPI_SPEED SD_SCK_MHZ(50)
#define SDCARD_SS_PIN (uint8_t)3U
//#define SPI_DRIVER_SELECT 2
#include <BufferedPrint.h>
#include <SDFat.h>
#include <sdios.h>
#define SD_CONFIG SdSpiConfig(SDCARD_SS_PIN, DEDICATED_SPI, SPI_SPEED)
const uint8_t CardDetect = 1U;
bool CardInserted;
char GPSLogFile[23];

#include "SAMDBattery.h"
#include <UTMConversion.h>
#include <TimeLib32.h>
#include <RTC_SAMD21.h>
#include <DateTime.h>

RTC_SAMD21 clock_rtc;

#include <Timezone32.h>
#include "ConfigFile.h"
#include "TimeZoneMapper.h"
#include <elapsedMillis.h>

elapsedMillis timerdeltatime = 0;
elapsedMillis timersave = 0;
elapsedMillis timemillis = 0;
enum {
  STARTING,
  GPS_WAITING,
  GPS_SAVE,
  LOW_BATTERY
} STATE;

#include "semphr.h"

Semphr display;
Semphr GPSUpdate;

#include "Fusion.h"
#define SAMPLE_RATE (10) // replace this with actual sample rate (Hz) Samples per second.
#define SAMPLE_MILIS (float)(1.0/SAMPLE_RATE*1000.0)  /* ms */
//#define SS_DT       (float)(SS_DT_MILIS/1000.0)   /* Sampling time */

/* -----Estos valores son para calibrar y ajustar los sensores.-----------------
// Sólo son necesarios si no se ajustan con la librería correspondiente.
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
//------------------------------------------------------------------------------
*/
// Initialise algorithms
FusionOffset offset;
FusionAhrs ahrs;
FusionGPS GPS;

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
#include <QMC5883L.h>
#include <MPU6050_light.h>
SFE_BMP180 pressure;
QMC5883L compass;
MPU6050 mpu(Wire);
// const uint8_t MPUStatus_DMP = 2U; // Esta en estudio el uso del DMP.
double barometer_Alt;
double barometer_Alt_prev;

// Definimos la conexion con el modulo Bluetooth hm11
//SoftwareSerial BT(2,1);  // RX - 2, TX - 1 BT(recivePin,transmitPin)
//bool bluetooth_connected = false;

//SPISettings SPI_settings = SPISettings(250000,MSBFIRST,SPI_MODE0);
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

bool AGPS() {
  char AGPS[]="casic.base64";
  if (card.exists(AGPS)) {
    if(file.open(AGPS,O_READ)){
      uint16_t date_AGPS, time_AGPS;
      file.getModifyDateTime(&date_AGPS, &time_AGPS);
      time32_t time = (clock_rtc.now().unixtime() - (SECS_PER_HOUR * 6));
      uint16_t date = (year(time)-1980) << 9 | month(time) << 5 | day(time);
      if (date <= date_AGPS) {
        String data = file.readString();
        gpsPort.print(data);
        //Serial.print(data); // Fos debug only.
      }
      file.close();
      return (date <= date_AGPS) ? true : false;
    }
  }
  return false;
}

enum GPS_Mode{
    PORTABLE,
    STATIONARY,
    PEDESTRIAN,
    AUTOMOTIVE,
    SEA,
    AIRBONE_1G
  };

void GPS_Mode_Config(GPS_Mode status){
  switch(status){
    case PORTABLE:
      gpsPort.print("$PCAS11,0*1D\r\n");
      break;
    case STATIONARY:
      gpsPort.print("$PCAS11,1*1C\r\n");
      break;
    case PEDESTRIAN:
      gpsPort.print("$PCAS11,2*1F\r\n");
      break;
    case AUTOMOTIVE:
      gpsPort.print("$PCAS11,3*1E\r\n");
      break;
    case SEA:
      gpsPort.print("$PCAS11,4*19\r\n");
      break;
    case AIRBONE_1G:
      gpsPort.print("$PCAS11,5*18\r\n");
      break;
  }

  //gpsPort.print("$PCAS11,0*1D\r\n");    // Config reciever as portable model. <------------------------
  //gpsPort.print("$PCAS11,1*1C\r\n");    // Config reciever as stationary model.
  //gpsPort.print("$PCAS11,2*1F\r\n");    // Config reciever as pedestrian model.
  //gpsPort.print("$PCAS11,3*1E\r\n");    // Config reciever as automotive model.
  //gpsPort.print("$PCAS11,4*19\r\n");    // Config reciever as sea model.
  //gpsPort.print("$PCAS11,5*18\r\n");    // Config reciever as airbone<1g model. (drone)
}

void GPS_config(float vel){
  if(vel < 0.1) GPS_Mode_Config(STATIONARY);
  else if(vel < 4) GPS_Mode_Config(PEDESTRIAN);
  else GPS_Mode_Config(PORTABLE);
}

// Variables para gestionar el tiempo local.
TimeElements time_gps;
time32_t _time_gps;
//time_t _utctime;    // El reloj lo establecemos siempre a UTC y ajustamos la hora local. 
time32_t _localtime;
DateTime _prevtime;
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
#define BAT_MIN  3.400
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
  if((clock_rtc.now() > _prevtime) || (timemillis >= 1000)) {
    timemillis = 0;
    _prevtime = clock_rtc.now();
    _localtime = TimeZone.toLocal(clock_rtc.now().unixtime(),&trc);
    display.set();
  }
}

inline void sync_time(){
  DateTime sync_gps_time = gps_time();
  clock_rtc.adjust(sync_gps_time);
  //setTime(gps_time());
  //Serial.println((long)gps_time());
  _localtime = TimeZone.toLocal(clock_rtc.now().unixtime(),&trc);
  //_prevtime = clock_rtc.now();
  //update_time();
}

bool GPSData() {
  static bool save = false;
  uint8_t errorSD;

  //sprintf(GPSLogFile, "%04d%02d%02d.csv", year(_localtime), month(_localtime), day(_localtime));

  //SdFile::dateTimeCallback(dateTime);
  FsDateTime::setCallback(dateTime);
  
  // Si no existe el fichero lo crea y añade las cabeceras.
  if (SDReady && !card.exists(GPSLogFile)) {
    if (file.open(GPSLogFile, O_CREAT | O_APPEND | O_WRITE)) {
      //Serial.print(F("New GPSLogFile, adding heads..."));
      file.println(F("Date,Time,Latitude,Longitude,Elevation,Speed,UTM Zone,X,Y"));
      //Serial.println(F("Done."));
      file.close();
      }
      //else {
      //Serial.println(F("** Error creating GPSLogFile. **"));
      //}
  }
  if (SDReady && (save=file.open(GPSLogFile, O_APPEND | O_WRITE))) {
    if(timemillis >= 1000) update_time();
    DateTime time = TimeZone.toLocal(_prevtime.unixtime(),&trc);
  
    BufferedPrint<File32, 78> bp;
    bp.begin(&file);
    //Date  YYYY-MM-DD
    bp.print(time.year());
    bp.print('-');
    if (time.month() < 10) bp.print('0');
    bp.print(time.month());
    bp.print('-');
    if (time.day() < 10) bp.print('0');
    bp.print(time.day());
    bp.print(',');
    //Time HH:MM:SS.ssss
    if (time.hour() < 10) bp.print('0');
    bp.print(time.hour());
    bp.print(':');
    if (time.minute() < 10) bp.print('0');
    bp.print(time.minute());
    bp.print(':');
    if (time.second() < 10) bp.print('0');
    bp.print(time.second());
    bp.print('.');
    if (timemillis < 100) bp.print('0');
    if (timemillis < 10) bp.print('0');
    bp.print((long)timemillis);
    bp.print(',');

    bp.printField(GPS.location_ins.axis.x,',',7); //Latitude in degrees.
    bp.printField(GPS.location_ins.axis.y,',',7); //Longitud in degrees.

    float altitude = GPS.location_ins.axis.z + (barometer_Alt - barometer_Alt_prev)/2.0;
    float speed_ms = (float)gps_data.speed_metersph()/3600.0f; //FusionVectorMagnitude(GPS.velocity_ins); // sqrt(FusionVectorMagnitudeSquared(GPS.velocity_ins));
    bp.printField(altitude,',',2);
    bp.printField(speed_ms,',',2);

    if (utm.zone() < 10) bp.print('0');
    bp.print(utm.zone());
    bp.print(utm.band());
    bp.print(',');
    bp.printField(utm.X()/100.0,',',2);
    bp.printField(utm.Y()/100.0,'\n',2);
    bp.sync();

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
  //update_time();
  oled.print_date(_localtime);
  oled.print_time(trc->abbrev, _localtime);
  //Serial.printf("%2.6f",vcc.GetVoltage());
  sprintf(line, "%02d%c ", utm.zone(), utm.band());
  //Serial.println(line); //
  oled.print(0,18,line);
  //utm.UTM((long)(GPS.location_ins.axis.x*10000000L), (long)(GPS.location_ins.axis.y*10000000L));
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
  int32_t altitude_bar = barometer_Alt;
  int32_t altitude_bar_prev = barometer_Alt_prev;
  int32_t altitude_ins = GPS.location_ins.axis.z;

  int32_t altitude = altitude_ins + (altitude_bar - altitude_bar_prev) / 2;

  //uint8_t elev_n = (uint8_t)(altitude < 0) ? (-altitude) : altitude;
  sprintf(line, "%05ldm", altitude);
  oled.print_PChar(1);
  oled.print(92,32,line);
  //Serial.println(line); //

  oled.print(0,44,"LAT:");
  int int_lat = GPS.location_ins.axis.x;
  long f_lat = (GPS.location_ins.axis.x - int_lat)*10000000L ;
  sprintf(line, "%d.%07ld",int_lat, (int_lat > 0) ? f_lat : -(f_lat));
  //int int_lat = gps_data.latitudeL() / 10000000L;
  //sprintf(line, "%d.%07ld",int_lat, (int_lat > 0) ? gps_data.latitudeL()-(long)int_lat*10000000L : -(gps_data.latitudeL()-(long)int_lat*10000000L));
  //sprintf(line,"%f",GPS.location_ins.axis.x);
  oled.print(21+(strlen(line)-8)*8,45,line);
  //Serial.print("Latitude:\t");Serial.println(line); //

  oled.print(0,54,"LON:");
  int int_lon = GPS.location_ins.axis.y;
  long f_lon = (GPS.location_ins.axis.y - int_lon)*10000000L ;
  sprintf(line, "%d.%07ld",int_lon, (int_lon > 0) ? f_lon : -(f_lon));  
  //int int_lon = gps_data.longitudeL() / 10000000L;
  //sprintf(line, "%d.%07ld",int_lon, (int_lon > 0) ? gps_data.longitudeL()-(long)int_lon*10000000L : -(gps_data.longitudeL()-(long)int_lon*10000000L));
  //sprintf(line,"%f",Filter.getLongitude_rad()*RAD_TO_DEG);
  oled.print(21+(strlen(line)-8)*8,55,line);
  //Serial.print("Longitude:\t");Serial.println(line); //
    
  int c = rtc.temperature();
  int celsius = (c >> 2);
  //Serial.println(celsius);
  sprintf(line,"%02d",celsius);
  oled.print(127-16,44,line);
  oled.print_PChar(6);

  float speed_ms = (float)gps_data.speed_metersph()/3600.0f;  //FusionVectorMagnitude(GPS.velocity_ins);
  sprintf(line,"%02d",(int)(speed_ms));
  //sprintf(line,"%02d",(int)(gps_data.speed_metersph()/3600));
  oled.print(104,55,line);
  oled.print_PChar(7);
    
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
          barometer_Alt_prev = barometer_Alt;
          barometer_Alt = pressure.altitude(barometer_P,1013.25);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  /* ------- Códigos de ejemplo para calcular la altura en funcion de la presion (mbar)-------
  // barometer_Alt = (1-pow(barometer_P/1013.25,0.190284))*44307.69396; //(145366.45*0.3048)
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
      UT = TimeZoneGPS.latLongToTimezone((float)GPS.location_ins.axis.x, (float)GPS.location_ins.axis.y);
      UST = TimeZoneGPS.latLongToTimezone_summer((float)GPS.location_ins.axis.x, (float)GPS.location_ins.axis.y);
      TimeZone.setRules(UST, UT);
      update_time();
    }
    sync_time();
    sprintf(GPSLogFile, "%04d%02d%02dT%02d%02d%02d.csv", year(_localtime), month(_localtime), day(_localtime),
            hour(_localtime),minute(_localtime),second(_localtime));
  } else {
    //Serial.print(F("SD card... REMOVED!")); //
    card.end();
    SDReady = false;
  }
}

FusionVector calculateNEDVelocity(const FusionVector accelerometer, const FusionVector magnetometer, const float deltatime) {
  //float courseGPS = gps_data.heading() * NeoGPS::Location_t::RAD_PER_DEG;
  float course = FusionCompassCalculateHeading(FusionConventionNed, accelerometer, magnetometer);
  //float courseIMU = FusionCompassCalculateHeading2(magnetometer);
  //Serial.print("Course: ");Serial.print(courseIMU);Serial.print("\t");
  //float course = (courseGPS + courseIMU) / 2;
  //float course = FusionDegreesToRadiansf((float)compass.readHeading());
  float speed_m_per_s = (float)(gps_data.speed_metersph()) / 3600.0f;
  const FusionVector NED = { .axis = {
    .x = round( speed_m_per_s * cos( course ) ),
    .y = round( speed_m_per_s * sin( course ) ),
    .z = (float)(barometer_Alt - barometer_Alt_prev) / deltatime // calcular la velocidad con el barometro.
  }};
  return NED;
}

FusionVector calculateNEDVelocityGPS() {
  const FusionVector NED = { .axis = {
    .x = (float)gps_data.velocity_north / 100.0f,
    .y = (float)gps_data.velocity_east / 100.0f,
    .z = (float)gps_data.velocity_down / 100.0f
  }};
  return NED;
}

int sign(float num) {
  return (num < 0.0f) ? -1 : 1;
}
/*----------------------------------------------------------------------------------------------------
void gps_update_info() {
if (gps_data.valid.location) {
      FusionVectorDouble  GPS_loc = {(double)gps_data.latitudeL()/10e6, (double)gps_data.longitudeL()/10e6, (double)gps_data.altitude()};
      FusionVector velocity = calculateNEDVelocityGPS();
      float courseGPS = gps_data.heading() * NeoGPS::Location_t::RAD_PER_DEG;
      const FusionQuaternion quaternion = FusionAhrsGetQuaternion(&ahrs); 
      FusionVector magnetometer = {compass.getX(), -compass.getY(), -compass.getZ()}; // replace this with actual magnetometer data in arbitrary units
      float courseIMU = FusionCompassCalculateHeading2(FusionVectorRotatebyQuaternion(magnetometer,quaternion,FusionConventionNed));
      FusionVector GPS_error = { .axis = {
        .x = gps_data.lon_err() * (float)sign(cosf(courseGPS*DEG_TO_RAD)-cosf(courseIMU*DEG_TO_RAD)),
        .y = gps_data.lat_err() * (float)sign(sinf(courseIMU*DEG_TO_RAD)-sinf(courseGPS*DEG_TO_RAD)),
        .z = 0.0f
      }};
      FusionGPSUpdate(&GPS, GPS_loc, velocity, GPS_error);
    } else {
      //FusionVector earth = FusionAhrsGetEarthAcceleration(&ahrs);
      //if (FusionVectorIsZero(earth))
      //FusionGPSPredict(&GPS);
      //else 
      FusionQuaternion quaternion = FusionAhrsGetQuaternion(&ahrs);
      const FusionVector accel = FusionAhrsGetLinearAcceleration(&ahrs);
      //FusionEuler euler = FusionQuaternionToEuler(quaternion);
      FusionGPSAHRSUpdate(&GPS, quaternion, accel, 1.0f / *(float)timemillis/1000.0f* /);
    }
    // *
    if (timemillis > 500U) {
      FusionGPSPredict(&GPS);
    }
    else 
    if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location && gps_data.status == gps_data.STATUS_STD){
      FusionVector velocity = calculateNEDVelocityGPS();
      FusionVector GPS_error = { .axis = {
        .x = gps_data.lat_err(),
        .y = gps_data.lon_err(),
        .z = 0.0f
      }};
      FusionGPSUpdate(&GPS, GPS_loc, velocity, GPS_error);
    } else {
      FusionVector earth = FusionAhrsGetEarthAcceleration(&ahrs);
      FusionQuaternion quaternion = FusionAhrsGetQuaternion(&ahrs);
      //const FusionVector accel = FusionAhrsGetLinearAcceleration(&ahrs);
      //FusionEuler euler = FusionQuaternionToEuler(quaternion);
      FusionGPSAHRSUpdate(&GPS, quaternion, earth, 1.0f);
    } //FusionGPSPredict(&GPS);
    * /
}
------------------------------------------------------------------------------------------------*/
void setup(void) {
  pinMode(CardDetect, INPUT_PULLDOWN);
  CardInserted = digitalRead(CardDetect);
  //attachInterrupt(digitalPinToInterrupt(CardDetect), CardDetectFunction, CHANGE);
  
  //delay(4000);
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
  DateTime rtc_time = rtc.get();
  clock_rtc.begin();
  clock_rtc.adjust(rtc_time);

  _prevtime = clock_rtc.now();
  //setTime(rtc.get()); // Use RTC SAMD21 instead.
  //_prevtime = now();
  
  //if(timeStatus() != timeSet)
  //  Serial.println("Unable to sync with the RTC");
  //else
    Serial.println("RTC has set the system time");
  Serial.println((long)clock_rtc.now().unixtime());

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
  mpu.setAccOffsets(0.03184131, 0.00907129, -1.92812943 /*0.03327057*/); // Zoffset = -1.92812943 - (2*0.9807)
  mpu.setGyroOffsets(0.79480880, 0.70482421, -0.24815249);

  mpu.update();

  compass.init();
	compass.setSamplingRate(10);
  while(!compass.readHeading());

  //BT.begin(9600); 
  gpsPort.begin(9600);
  
  //gpsPort.print("$PCAS10,3*1F\r\n");  // Reboot Factory reset.
  //gpsPort.print("$PCAS02,1000*2E\r\n"); // Set gps to 1Hz.
  gpsPort.print("$PCAS02,500*1A\r\n");  // Set gps to 2Hz. <-----------------
  //gpsPort.print("$PCAS02,250*18\r\n");  // Set gps to 4Hz.
  //gpsPort.print("$PCAS02,200*1D\r\n");  // Set gps to 5Hz.
  
  delay(10);
  
  gpsPort.print("$PCAS11,0*1D\r\n");    // Config reciever as portable model. <------------------------
  //gpsPort.print("$PCAS11,1*1C\r\n");    // Config reciever as stationary model.
  //gpsPort.print("$PCAS11,2*1F\r\n");    // Config reciever as pedestrian model.
  //gpsPort.print("$PCAS11,3*1E\r\n");    // Config reciever as automotive model.
  //gpsPort.print("$PCAS11,4*19\r\n");    // Config reciever as sea model.
  //gpsPort.print("$PCAS11,5*18\r\n");    // Config reciever as airbone<1g model. (drone)

  //gpsPort.print("$PCAS04,9,9,9*10\r\n");    // GPS+GALILEO
  //gpsPort.print("$PCAS04,1F,1F,19*21\r\n");    // GPS+BDS+GLONASS+GALILEO

  //delay(10);
  //gpsPort.print("$PCAS01,1*1D\r\n");    // Set baudrate to 9600.
  gpsPort.print("$PCAS01,2*1E\r\n");    // Set baudrate to 19200. <----------------
  //gpsPort.print("$PCAS01,3*1F\r\n");    // Set baudrate to 38400.
  //gpsPort.print("$PCAS01,4*18\r\n");    // Set baudrate to 57600.
  //gpsPort.print("$PCAS10,0*1C\r\n");    // Hot reset

  //gpsPort.end();
  delay(200);
  gpsPort.begin(19200);

  /* Iniciaización del display oled u OLED */
  oled.start();
  
  //pinMode(A0,INPUT); // Initialized in class SAMDBattery.

  Serial.print(F("Initializing SD card...")); //
  SDReady = card.begin(SD_CONFIG);
  (SDReady) ? Serial.println(F("Done.")) : Serial.println(F("FAILED!")); //
  
  Serial.print(F("Writing AGPS data..."));
  if (AGPS()) Serial.print(F("\tOK.\n"));
  else Serial.print(F("\tFAILED!!!\n"));

  // Config TimeZone (_localtime) with 'Time.cfg' file on SD.
  loadConfigurationProgram();
  
  vcc.analogRef(AR_DEFAULT);
  vcc.setADCres(12);

  /* Iniciaización del display oled u OLED */
  oled.start();

  if(vcc.GetChargeLevel() < 5) STATE = LOW_BATTERY;
  else STATE = STARTING;
//--------------------------------------------------------------------------------
//  if(vcc.GetChargeLevel() < 5) {
//    oled.clear();
//    oled.drawbattery(vcc.GetChargeLevel());
//    oled.draw();
//    do {
//      delay(500);
//      oled.clear();
//      delay(500);
//      oled.drawbattery(vcc.GetChargeLevel());
//      oled.draw();
//      } while(vcc.GetChargeLevel() < 5);
//    //setup();
//    }
//---------------------------------------------------------------------------------
  
  
  FusionOffsetInitialise(&offset, SAMPLE_RATE);
  FusionAhrsInitialise(&ahrs);
  FusionAhrsSetSettings(&ahrs, &settings);
  FusionGPSInitialise(&GPS);

  Serial.print(F("Waiting for GPS signal..."));
}

void loop(void) {
  static bool needcharge = false;
  static uint8_t charge;
  uint8_t errorSD;

  // Calculate delta time (in seconds) to account for gyroscope sample clock error
  const clock_t timestamp = micros();
  static clock_t previousTimestamp;
  const float deltaTime = (float) (timestamp - previousTimestamp) / (/*(float) CLOCKS_PER_SEC */ 1000000.0);
  previousTimestamp = timestamp;

  if(timerdeltatime >= SAMPLE_MILIS){
    timerdeltatime = 0;

    // Read mpu and compass values
    mpu.update();
    compass.read();

    // Acquire latest sensor data
    FusionVector gyroscope = {mpu.getGyroX(), -mpu.getGyroY(), -mpu.getGyroZ()}; // replace this with actual gyroscope data in degrees/s
    FusionVector accelerometer = {mpu.getAccX(), -mpu.getAccY(), -mpu.getAccZ()}; // replace this with actual accelerometer data in g
    FusionVector magnetometer = {compass.getX(), -compass.getY(), -compass.getZ()}; // replace this with actual magnetometer data in arbitrary units

    //FusionAxesSwap(gyroscope, FusionAxesAlignmentPXNYNZ);

    // Apply calibration
    //gyroscope = FusionCalibrationInertial(gyroscope, gyroscopeMisalignment, gyroscopeSensitivity, gyroscopeOffset);
    //accelerometer = FusionCalibrationInertial(accelerometer, accelerometerMisalignment, accelerometerSensitivity, accelerometerOffset);
    //magnetometer = FusionCalibrationMagnetic(magnetometer, softIronMatrix, hardIronOffset);

    // Update gyroscope offset correction algorithm
    gyroscope = FusionOffsetUpdate(&offset, gyroscope);

    // Update gyroscope AHRS algorithm
    FusionAhrsUpdate(&ahrs, gyroscope, accelerometer, magnetometer, deltaTime);

    //const FusionVector earth = FusionAhrsGetEarthAcceleration(&ahrs);
    const FusionQuaternion quaternion = FusionAhrsGetQuaternion(&ahrs); 
    const FusionVector accel = FusionAhrsGetLinearAcceleration(&ahrs);
    //FusionEuler euler = FusionQuaternionToEuler(quaternion);
    FusionGPSAHRSUpdate(&GPS, quaternion, accel, deltaTime);
    
    //Serial.print("dx: x:");Serial.print(GPS.dx.axis.x,7);Serial.print(" ");
    //Serial.print("y :");Serial.print(GPS.dx.axis.y,7);Serial.print(" ");
    //Serial.print("z:");Serial.print(GPS.dx.axis.z,4);Serial.print(". - ");
    //Serial.print("dxd: x:");Serial.print(GPS.dxd.axis.x,7);Serial.print(" ");
    //Serial.print("y :");Serial.print(GPS.dxd.axis.y,7);Serial.print(" ");
    //Serial.print("z:");Serial.print(GPS.dxd.axis.z,4);Serial.print(". - ");
    //Serial.print("V.ins X: ");Serial.print(GPS.velocity_ins.axis.x,2);Serial.print(", ");
    //Serial.print("Y: ");Serial.print(GPS.velocity_ins.axis.y,2);Serial.print(", ");
    //Serial.print("Z: ");Serial.print(GPS.velocity_ins.axis.z,2);Serial.print(". - ");
    //Serial.print("V.ang X: ");Serial.print(GPS.angular.axis.x,2);Serial.print(", ");
    //Serial.print("Y: ");Serial.print(GPS.angular.axis.y,2);Serial.print(", ");
    //Serial.print("Z: ");Serial.print(GPS.angular.axis.z,2);Serial.print("\n");
    //Serial.print("Ins: Lat: "); Serial.print(GPS.location_ins.axis.x,7);
    //Serial.print("º, Lon: ");Serial.print(GPS.location_ins.axis.y,7);
    //Serial.print("º, Alt: ");Serial.print(GPS.location_ins.axis.z,2);Serial.print("m\t");
    //Serial.print("AHRS: Lat: "); Serial.print(GPS.location_ahrs.axis.x,7);
    //Serial.print("º, Lon: ");Serial.print(GPS.location_ahrs.axis.y,7);
    //Serial.print("º, Alt: ");Serial.print(GPS.location_ahrs.axis.z,2);Serial.print("m\n");
  }

  //if(BT.isListening()) bluetooth_connected = true;

  charge = charge_level();
  (charge > 5) ? needcharge = false : needcharge = true;

  if(CardChange()) CardDetectFunction();

  if (gps.available(gpsPort)) { //https://github.com/SlashDevin/NeoGPS/issues/111
    gps_data = gps.read();
    //Serial.println();
    //trace_all( Serial, gps, gps_data );  // uncomment this line if you want to see the GPS data flowing
    if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location && gps_data.valid.heading) {
      FusionVectorDouble  GPS_loc = {(double)gps_data.latitudeL()/10e6, (double)gps_data.longitudeL()/10e6, (double)gps_data.altitude()};
      FusionVector velocity = calculateNEDVelocityGPS();
      float courseGPS = gps_data.heading() * NeoGPS::Location_t::RAD_PER_DEG;
      const FusionQuaternion quaternion = FusionAhrsGetQuaternion(&ahrs); 
      FusionVector magnetometer = {compass.getX(), -compass.getY(), -compass.getZ()}; // replace this with actual magnetometer data in arbitrary units
      float courseIMU = FusionCompassCalculateHeading2(FusionVectorRotatebyQuaternion(magnetometer,quaternion,FusionConventionNed));
      FusionVector GPS_error = { .axis = {
        .x = gps_data.lon_err() * (float)sign(cosf(courseGPS*DEG_TO_RAD)-cosf(courseIMU*DEG_TO_RAD)),
        .y = gps_data.lat_err() * (float)sign(sinf(courseIMU*DEG_TO_RAD)-sinf(courseGPS*DEG_TO_RAD)),
        .z = 0.0f
      }};
      FusionGPSUpdate(&GPS, GPS_loc, velocity, GPS_error);
      _time_gps = gps_time_rtc();
      GPS_config((float)gps_data.speed_metersph()/3600.0);
    }
  }

  if(STATE == STARTING) {
    if(_prevtime < clock_rtc.now()) {
      update_time();
      oled.clear();
      oled.print_date(_localtime);
      oled.print_time(trc->abbrev, _localtime);
      oled.drawbattery(charge_level());
      (SDReady) ? oled.print_PChar(3) : oled.print_PChar(4);
      //if (bluetooth_connected) oled.print_PChar(5);  // No tiene módulo Bluetooth.
      oled.print(81,55,VERSION);
      oled.DrawLogo();
      oled.draw();
      oled.wait_anin(_prevtime.second());
    }
    if (gps_data.valid.time && gps_data.valid.date && gps_data.valid.location) {// Did a new valid sentence come in?
      //setSyncProvider(gps_time);
      //setSyncInterval(15);
      DateTime gps_time_local = gps_time();
      clock_rtc.adjust(gps_time_local);
       // ---->  rtc.set(gps_time_rtc());
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
      sync_time();

      sprintf(GPSLogFile, "%04d%02d%02dT%02d%02d%02d.csv", year(_localtime), month(_localtime), day(_localtime),
            hour(_localtime),minute(_localtime),second(_localtime));
      FusionVectorDouble GPS_loc = {(double)gps_data.latitudeL()/10e6, (double)gps_data.longitudeL()/10e6, (double)gps_data.altitude()};
      FusionVector velocity = calculateNEDVelocityGPS();
      FusionVector GPS_error = { .axis = {
        .x = gps_data.lon_err(),
        .y = gps_data.lat_err(),
        .z = 0.0f
      }};
      FusionGPSUpdate(&GPS, GPS_loc, velocity, GPS_error);

      trace_header( Serial );
      Serial.flush();
      timersave = 0;
      while(timersave < 5000) {
        update_time();
        oled.clear();
        oled.print_date(_localtime);
        oled.print_time(trc->abbrev, _localtime);
        oled.drawbattery(charge_level());
        (SDReady) ? oled.print_PChar(3) : oled.print_PChar(4);
        //if (bluetooth_connected) oled.print_PChar(5);  // No tiene módulo Bluetooth.
        oled.DrawCalibrate();
        oled.draw();
        oled.wait_anin(_prevtime.second());
        delay(1000);
      }
      //STATE = GPS_WAITING;
      STATE = (needcharge) ? LOW_BATTERY : GPS_WAITING;
      timersave = 0;
    }
    //_prevtime = clock_rtc.now();
  } else if(STATE == GPS_WAITING) {
    
    STATE = (needcharge) ? LOW_BATTERY : (timersave >= 1000) ? GPS_SAVE : GPS_WAITING; //563-560
  } else if(STATE == GPS_SAVE) {
    timersave = 0;
    if(_time_gps < clock_rtc.now().unixtime()) FusionGPSPredict(&GPS);
    calc_altitude();
    utm.UTM((long)(GPS.location_ins.axis.x*10000000L), (long)(GPS.location_ins.axis.y*10000000L)); 
    (!(errorSD = card.sdErrorCode())) ? SDReady = true : SDReady = false;
    if (errorSD == 11) card.end();
    //Serial.println(errorSD);
    update_time();
    SaveOK = (SDReady) ? GPSData() : false;
    display(ScreenPrint);
    STATE = GPS_WAITING;
    //Serial.print(_prevtime.unixtime());
    //Serial.print(" Loc: Lat: "); Serial.print(GPS.location.axis.x,7);
    //Serial.print("º, Lon: ");Serial.print(GPS.location.axis.y,7);
    //Serial.print("º, Alt: ");Serial.print(GPS.location.axis.z,2);Serial.print("m\t");
    //Serial.print("Ins: Lat: "); Serial.print(GPS.location_ins.axis.x,7);
    //Serial.print("º, Lon: ");Serial.print(GPS.location_ins.axis.y,7);
    //Serial.print("º, Alt: ");Serial.print(GPS.location_ins.axis.z,2);Serial.print("m\n");
    //Serial.print(" - Kalman X: "); Serial.print(GPS.Kalman.axis.x,7);
    //Serial.print(", Y: ");Serial.print(GPS.Kalman.axis.y,7);
    //Serial.print(", Z: ");Serial.print(GPS.Kalman.axis.z,7);Serial.print("m\n");

  } 
  else if(STATE == LOW_BATTERY){
    //needcharge = true;
    while (needcharge) {
      _prevtime = clock_rtc.now();
      update_time();
      oled.clear();
      oled.print_date(_localtime);
      oled.print_time(trc->abbrev, _localtime);
      charge = charge_level();
      oled.drawbattery(charge_level());
      oled.DrawLowBat();
      oled.draw();
      gpsPort.print("$PCAS12,1*1F\r\n"); // GNSS Receiver enter in stanby mode for 1s.
      delay(1000);
      (charge_level() > 10 || charge_level() < 0) ? needcharge = false : needcharge = true;
    }
    //needcharge = false;
    STATE = GPS_WAITING;
  }
    
}
