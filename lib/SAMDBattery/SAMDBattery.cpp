/*
SAMDBattery.cpp - Ligth Library for Arduino Environment to Battery management.
v0.1

Copyright © 2021 Francisco Rafael Reyes Carmona.
All rights reserved.

rafael.reyes.carmona@gmail.com


  This file is part of SAMDBattery Library.

  SAMDBattery Library is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  SAMDBattery Library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with SAMDBattery Library.  If not, see <https://www.gnu.org/licenses/>.

*/

/**
 * Ligth Library for Arduino Enveroment to Battery management.
 */

#include "SAMDBattery.h"
#include <EMA.h>
#include "ATSAMD21_ADC.h"

SAMDBattery::SAMDBattery(byte PIN,
                         float VREF,
                         long RESISTOR_VDD,
                         long RESISTOR_GND,
                         float MIN_VOLT,
                         float MAX_VOLT) {
  _PIN = PIN;
  _VREF = VREF;
  _MIN_V = MIN_VOLT;
  _MAX_V = MAX_VOLT;

  // Calculate conversion factor (maximum output voltage of the voltage divider)
  _FACTOR = RESISTOR_VDD + RESISTOR_GND;
  _FACTOR /= RESISTOR_GND;

  pinMode(_PIN, INPUT);
}


SAMDBattery::SAMDBattery(byte PIN,
                         float VREF,
                         float MIN_VOLT,
                         float MAX_VOLT,
                         float FACTOR) {
  _PIN = PIN;
  _VREF = VREF;
  _MIN_V = MIN_VOLT;
  _MAX_V = MAX_VOLT;
  _FACTOR = FACTOR;

  pinMode(_PIN, INPUT);
}

float SAMDBattery::GetVoltage(){
  uint16_t ADC_filtered;
  uint16_t pVal;
  static EMA<3> EMA_filter(analogRead(_PIN));

  pVal = analogRead(_PIN);

  ADC_filtered = EMA_filter(pVal);

  return ( ( ( ((float)ADC_filtered * _VREF ) / 1000.0 ) / (float)_ADC_MAX ) * _FACTOR );
  }


byte SAMDBattery::GetChargeLevel()
{
    if (_MAX_V - _MIN_V == 0.0) {
      return 0;
    }
    int Level;
    float Current_Level = GetVoltage();
    
    Current_Level -= _MIN_V;
    Current_Level *= 100;
    Current_Level /= (_MAX_V - _MIN_V);

    Level = (int)Current_Level;
    return (byte)constrain(Level, 0, 100);
}


void SAMDBattery::setADCres(uint8_t res){
  analogReadExtended(res);
  _ADC_MAX = (1 << res); 
}


void SAMDBattery::analogRef(eAnalogReference mode){
analogReference(mode);
switch(mode) {
  case AR_INTERNAL1V0:
    _VREF = 1024.0;
    break;
  case AR_INTERNAL1V1:
    _VREF = 1100.0;
    break;
  case AR_INTERNAL1V2:
    _VREF = 1200.0;
    break;
  case AR_INTERNAL1V25:
    _VREF = 1250.0;
    break;
  case AR_INTERNAL2V0:
    _VREF = 2000.0;
    break;
  case AR_INTERNAL2V2:
    _VREF = 2200.0;
    break;
  case AR_INTERNAL2V23:
    _VREF = 2230.0;
    break;
  case AR_INTERNAL2V4:
    _VREF = 2400.0;
    break;
  case AR_INTERNAL2V5:
    _VREF = 2500.0;
    break;
  case AR_INTERNAL1V65:
    _VREF = 1650.0;
    break;
  default:
    _VREF = 3300.0;
    break;
  }
}
