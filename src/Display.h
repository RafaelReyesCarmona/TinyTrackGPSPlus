/*
Display.h - A simple track GPS to SD card logger. Display module.
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

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef Display_h
#define Display_h

#include "config.h"
#include <TimeLib32.h>

#define U8X8_HAVE_HW_I2C
#define U8G2_HAVE_HW_I2C
#include <U8x8lib.h>
#include <U8g2lib.h>

enum Display_Type {
    SIZE_128X64,     // Para usar pantalla OLED 0.96" I2C 128x64 pixels
    SIZE_128X32      // Para usar pantalla OLED 0.96" I2C 128x32 pixels
};

class Display {
    private:
        byte _width;       // Width pixels or numbers of columns for LCD.
        byte _height;       // Height pixels os numbers of rows for LCD.
        Display_Type _screen;
        #if defined(DISPLAY_TYPE_SDD1306_128X64)
            U8G2_SSD1306_128X64_NONAME_F_HW_I2C* u8g2;
            //U8X8_SSD1306_128X64_NONAME_HW_I2C* u8x8;
        #elif defined(DISPLAY_TYPE_SH1106_128X64)
            U8G2_SH1106_128X64_NONAME_F_HW_I2C* u8g2;
            //U8X8_SH1106_128X64_NONAME_HW_I2C* u8x8;
        #endif

    public:
        Display(Display_Type t = SIZE_128X64); 
        Display() = delete;                             // Constructor por defecto.
        Display(const Display&) = delete;               // Constructor de copia.

        void start();
        void clear();
        void draw();
        void print(int, int, const char[]);
        void print(int, const char[]);
        void print(const char[]);
        void print_date(time32_t);
        void print_time(const char[], time32_t);
        void drawtext(int, int, const char[]);
        void wait_anin(unsigned int);
        void draw_wait(byte);
        void print_PChar(byte);
        void print_PChar_sat(byte);
        void print_PChar_Nosat();
        void print_UTM_x(long);
        void print_UTM_y(long);
        void print_promt();
        void DrawLogo();
        void drawbattery(int8_t);
        Display_Type display_type(){return _screen;};
};

#endif