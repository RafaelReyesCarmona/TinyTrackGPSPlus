/*
Display.cpp - A simple track GPS to SD card logger. Display module.
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

#include "Display.h"

Display::Display(Display_Type t):_screen(t){
    _width = 128;
    _height = (_screen > 0) ? 32 : 64;
}

void Display::start(){
    #if defined(DISPLAY_TYPE_SDD1306_128X64)
        u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);
        u8g2->begin();
        //u8g2_SSD1306->setFont(u8x8_font_7x14B_1x2_r);
    #endif

    #if defined(DISPLAY_TYPE_SH1106_128X64)
        u8g2 = new U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);
        u8g2->begin();
        //u8g2->setFont(u8x8_font_7x14B_1x2_r);
    #endif        
    u8g2->setFontRefHeightExtendedText();
    u8g2->setFontPosTop();
    //u8g2->setFont(u8g2_font_artossans8_8u);
    u8g2->setFont(u8g2_font_siji_t_6x10);
    u8g2->enableUTF8Print();
    this->clear();
}

void Display::clear(){
    u8g2->clearBuffer();
}

void Display::draw(){
    u8g2->updateDisplay();
}

void Display::print(int vertical, int horizontal, const char text[]){
    u8g2->setCursor(vertical, horizontal);
    this->print(text);
}

void Display::print(int line, const char text[]){
    // uint8_t h, c;
    u8g2_uint_t d, l;

    //h = u8g2->getMaxCharHeight();
    l = u8g2->getStrWidth(text);
    d = ((_width - l) / 2) - 1;
    //c = ((_height - h) / 2) - 1;

    this->print((int)d, (int)line, text);
}

void Display::print(const char text[]){
    //u8g2->setFont(u8g2_font_siji_t_6x10);
    //u8g2->setFont(u8g2_font_artossans8_8u);
    u8g2->print(text);
}

void Display::print_date(time32_t t){
  char line[13];
  //u8g2->setFont(u8g2_font_siji_t_6x10);
  u8g2->drawGlyph(0,0,0xe225);
  u8g2->setCursor(14,0);
  u8g2->print(dayShortStr_es(weekday(t)));

  sprintf(line," %02d-%s-%04d",day(t),monthShortStr_es(month(t)),year(t));
  u8g2->print(line);
}

void Display::print_time(const char tz[], time32_t t){
  char line[10];
  uint16_t sep = 0xe192;
  u8g2->drawGlyph(0,8,0xe1b9);
  u8g2->setCursor(14,8);
  u8g2->print(tz);
  //u8g2->setFont(u8g2_font_siji_t_6x10);
  sprintf(line," %02d:%02d:%02d",hour(t),minute(t),second(t));
  for(uint8_t i=0;i<sizeof(line);i++){
    switch(line[i]){
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        u8g2->drawGlyph(18+14+(i*8),8, (uint16_t)line[i]+57667);
        break;
      case ':':
        u8g2->drawGlyph(18+14+(i*8),8, sep);
    }
  }
  //u8g2->print(line);
}

void Display::print_promt(){
  u8g2->drawHLine(0,16,u8g2->getWidth());
  u8g2->drawHLine(0,43,u8g2->getWidth());
  u8g2->drawHLine(80,30,u8g2->getWidth()-80);
  u8g2->drawVLine(100,16,14);
  u8g2->drawVLine(80,30,14);
  u8g2->drawVLine(100,43,24);
}

void Display::wait_anin(unsigned int t){
        /*
        const char p[4] = {(char)47,(char)45,(char)92,(char)124};
        u8g2->setCursor((_width-1),6);
        u8g2->print(p[t%4]);
        */
        static uint8_t hourglass_UP[5][8] = {  0x01,0x1f,0x7f,0xff,0xff,0x7f,0x1f,0x01,
                                        0x01,0x1f,0x7d,0xf9,0xf9,0x7d,0x1f,0x01,
                                        0x01,0x1f,0x79,0xf1,0xf1,0x79,0x1f,0x01,
                                        0x01,0x1f,0x71,0xe1,0xe1,0x71,0x1f,0x01,
                                        0x01,0x1f,0x61,0x81,0x81,0x61,0x1f,0x01
                                        };

        static uint8_t hourglass_DOWN[5][8] = {0x80,0xf8,0x86,0x81,0x81,0x86,0xf8,0x80,
                                        0x80,0xf8,0xc6,0xe1,0xe1,0xc6,0xf8,0x80,
                                        0x80,0xf8,0xe6,0xf1,0xf1,0xe6,0xf8,0x80,
                                        0x80,0xf8,0xfe,0xf9,0xf9,0xfe,0xf8,0x80,
                                        0x80,0xf8,0xfe,0xff,0xff,0xfe,0xf8,0x80
                                        };
        u8g2->drawTile(0, 6, 1, hourglass_UP[t%5]);
        u8g2->drawTile(0, 7, 1, hourglass_DOWN[t%5]);
}

void Display::print_PChar(byte c) {
  switch(c){
    case 1: //Altitude
      u8g2->drawGlyph(80,33,0xe0a1);
      break;
    case 2: //GPS
      u8g2->drawGlyph(103,20,0xe1ba);
      break;
    case 3: //SD
      u8g2->drawGlyph(127-12,8,0xe144);
      break;
    case 4: //SD no inserted
      u8g2->drawGlyph(127-12,7,0xe217);
      break;
    case 5: //BT
      u8g2->drawGlyph(127-12,67-12,0xe00b);
      break;
    case 6: //Temp.
      u8g2->drawGlyph(100,45,0xe01d);
      u8g2->drawCircle(125,47,1);
      //u8g2->drawCircle(112,47,1);
      break;
  }
}

void Display::print_PChar_sat(byte c){
  if(c > 15) u8g2->drawGlyph(127-21,7,0xe222);
  else if(c > 10) u8g2->drawGlyph(127-21,7,0xe221);
  else if(c > 5) u8g2->drawGlyph(127-21,7,0xe220);
  else u8g2->drawGlyph(127-21,7,0xe21f);
  /*
  uint8_t cob = 0;
  if(bitRead(c,3))
    cob+=1;
  if(bitRead(c,4)) 
    cob+=2;
  u8g2->drawGlyph(127-12,20,0xe21f+cob);
  */
}

void Display::print_PChar_Nosat(){
  u8g2->drawGlyph(127-18,6,0x78);
  u8g2->drawGlyph(127-21,7,0xe21f);
}

void Display::print_UTM_x(long x){
  char line[8];
  sprintf(line, "%ld", x);
  for(uint8_t i=0;i<strlen(line)-2;i++){
    u8g2->drawGlyph(20+(i*8),20,(uint16_t)line[i]+57677);
    }
  u8g2->drawPixel(20+((strlen(line)-2)*8)+3,20);
  u8g2->drawPixel(20+((strlen(line)-2)*8)+4,20);
  u8g2->drawPixel(20+((strlen(line)-2)*8)+3,21);
  u8g2->drawGlyph(20+((strlen(line)-2)*8)+5,20,(uint16_t)line[strlen(line)-2]+57667);
  u8g2->drawGlyph(20+((strlen(line)-1)*8)+5,20,(uint16_t)line[strlen(line)-1]+57667);
}

void Display::print_UTM_y(long y){
  char line[9];
  sprintf(line, "%ld", y);
  for(uint8_t i=0;i<sizeof(line)-2;i++){
    u8g2->drawGlyph(0+(i*8)-2,32,(uint16_t)line[i]+57677);
    }
  u8g2->drawPixel(0+((strlen(line)-2)*8)+1,32);
  u8g2->drawPixel(0+((strlen(line)-2)*8)+2,32);
  u8g2->drawPixel(0+((strlen(line)-2)*8)+1,33);
  u8g2->drawGlyph(0+((sizeof(line)-2)*8)+3,32,(uint16_t)line[sizeof(line)-2]+57667);
  u8g2->drawGlyph(0+((sizeof(line)-1)*8)+3,32,(uint16_t)line[sizeof(line)-1]+57667);
}

void Display::DrawLogo() {
    static uint8_t Logo_UP[8][8] = { 
    0x00, 0x00, 0x80, 0xC0, 0x60, 0x10, 0x98, 0x4C,
    0x64, 0x26, 0x12, 0x12, 0x0B, 0x09, 0x09, 0x49,
    0x49, 0x09, 0x09, 0x0B, 0x12, 0x12, 0x26, 0x64,
    0x48, 0x98, 0x10, 0x60, 0xC0, 0x00, 0x00, 0x00,
    0x0F, 0x78, 0xC0, 0x0F, 0x30, 0xC0, 0x81, 0x00,
    0xC0, 0xE0, 0x78, 0x26, 0x23, 0x10, 0x18, 0x08,
    0x0D, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x81, 0xC0, 0x30, 0x0F, 0xC0, 0x78, 0x0F
    };
    static uint8_t Logo_DOWN[8][8] = {
    0xF0, 0x1E, 0x03, 0xF0, 0x0C, 0x03, 0x81, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0xB0,
    0x10, 0x18, 0x08, 0xC4, 0x64, 0x1E, 0x07, 0x03,
    0x00, 0x81, 0x03, 0x0C, 0xF0, 0x03, 0x1E, 0xF0,
    0x00, 0x00, 0x01, 0x03, 0x06, 0x08, 0x19, 0x32,
    0x26, 0x64, 0x48, 0x48, 0xD0, 0x90, 0x90, 0x92,
    0x92, 0x90, 0x90, 0xD0, 0x48, 0x48, 0x64, 0x26,
    0x32, 0x19, 0x08, 0x06, 0x03, 0x01, 0x00, 0x00
    };
    this->print(4,0,VERSION);
    u8g2->drawTile(6, 3, 4, Logo_UP[0]);
    u8g2->drawTile(6, 4, 4, Logo_DOWN[0]);
    u8g2->drawTile(6, 5, 4, Logo_UP[4]);
    u8g2->drawTile(6, 6, 4, Logo_DOWN[4]);
}

void Display::drawbattery(int8_t level){
  u8g2->setFont(u8g2_font_battery19_tn);
  u8g2->setFontDirection(1);
  if(level > 80) u8g2->drawGlyph(127,0,0x35);
  else if(level > 65) u8g2->drawGlyph(127,0,0x34);
  else if(level > 50) u8g2->drawGlyph(127,0,0x33);
  else if(level > 30) u8g2->drawGlyph(127,0,0x32);
  else if(level > 15) u8g2->drawGlyph(127,0,0x31);
  else if(level >= 0) u8g2->drawGlyph(127,0,0x30);
  else u8g2->drawGlyph(127,0,0x36);
  u8g2->setFont(u8g2_font_siji_t_6x10);
  u8g2->setFontDirection(0);
}
