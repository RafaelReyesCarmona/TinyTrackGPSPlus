#include "TimeZoneMapper.h"
#include <UTMConversion.h>

float flat[] = {37.8959210,40.033223,40.774997,66.077490,33.406994,-11.551785,7.333418,-41.266792,-21.643807,-37.463226};
float flon[] = {-4.7478210,-2.567744,15.582325,-45.853359,-84.482198,-45.151016,-69.030662,-67.625977,18.059812,146.629184};
long Llat[] = {378959210L,400332230L,407749970L,660774900L,334069940L,-115517850L,73334180L,-412667920L,-216438070L,-374632260L};
long Llon[] = {-47478210L,-25677440L,155823250L,-458533590L,-844821980L,-451510160L,-690306620L,-676259770L,180598120L,1466291840L};

GPS_UTM utm;
time_t _localtime, _utctime;
TimeElements time_gps;

void setup() {

}

void loop() {
    char utmstr[] = "30S 123456 1234567";
    char utmstr_L[] = "30S 12345600 123456700";

    time_gps.Year = 2022 - 1970;
    time_gps.Month = 5;
    time_gps.Day = 2;
    time_gps.Hour = 12;
    time_gps.Minute = 0;
    time_gps.Second = 0;

    _utctime = makeTime(time_gps);

    for(int i = 0; i < 10;i++){
        char line[60];
        char strhour[18];
        char strlat[12];
        char strlon[12];
        dtostrf(flat[i],8,7,strlat);
        dtostrf(flon[i],8,7,strlon);
        sprintf(line, "Coordenates %s, %s -> UTM: ", strlat, strlon);
        Serial.print(line);
        utm.UTM(flat[i], flon[i]);
        sprintf(utmstr, "%02d%c %ld %ld", utm.zone(), utm.band(), utm.X(), utm.Y());
        Serial.println(utmstr);
        int int_lat = Llat[i] / 10000000L;
        int int_lon = Llon[i] / 10000000L;
        sprintf(strlat, "%ld", (int_lat > 0) ? Llat[i]-(long)int_lat*10000000L : -(Llat[i]-(long)int_lat*10000000L));
        sprintf(strlon, "%ld", (int_lon > 0) ? Llon[i]-(long)int_lon*10000000L : -(Llon[i]-(long)int_lon*10000000L));
        sprintf(line, "Coordenates High %d.%s, %d.%s -> UTM: ", int_lat, strlat, int_lon, strlon);
        Serial.print(line);
        utm.UTM(Llat[i], Llon[i]);
        sprintf(utmstr_L, "%02d%c %ld %ld", utm.zone(), utm.band(), utm.X(), utm.Y());
        Serial.println(utmstr_L);
        TimeZoneMapper TimeZoneGPS;
        TimeChangeRule UST = TimeZoneGPS.latLongToTimezone_summer(flat[i], flon[i]);
        TimeChangeRule UT = TimeZoneGPS.latLongToTimezone(flat[i], flon[i]);
        Timezone TimeZone(UST, UT);

        _localtime = TimeZone.toLocal(_utctime);
        sprintf(strhour, " Hour -> %02d:%02d:%02d", hour(_localtime), minute(_localtime), second(_localtime));
        Serial.println(strhour);
        Serial.println();
    }
}
