/*
config.h - Config file for TinyTrackGPSPlus, a simple track GPS to SD card logger.
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

// Definimos nombre aplicación y versión.
#define NAME "TinyTrackGPSPlus"
#define NAME_M "TinyTrackGPSPLUS"
#define VERSION "V1.0.1"

// Descomentar solo uno de los displays utilizados. Comentar todas las líneas para uso NO DISPLAY.
#define DISPLAY_TYPE_SDD1306_128X64 // Para usar pantalla OLED 0.96" I2C 128x64 pixels
//#define DISPLAY_TYPE_SH1106_128X64         // Define para usar pantalla OLED 1.30" I2C 128x64 pixels (SH1106)

