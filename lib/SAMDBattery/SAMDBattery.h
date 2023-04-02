/*
SAMDBattery.h - Ligth Library for Arduino Environment to Battery management.
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


#ifndef SAMDBattery_h
#define SAMDBattery_h

#include "Arduino.h"

class SAMDBattery {
  private:
    int _ADC_MAX = 4096;  //ADC max. value.
    float _VREF = 3300.0;
    byte _PIN;
    float _FACTOR;
    float _MIN_V;
    float _MAX_V;

  public:
    SAMDBattery(byte, float, long, long, float, float);
    SAMDBattery(byte, float, float, float, float);
    SAMDBattery() = delete;
    SAMDBattery(const SAMDBattery&) = delete;

    byte GetChargeLevel();
    float GetVoltage();

    void setADCres(uint8_t);
    void analogRef(eAnalogReference mode);
    
    // Set Vref (value * 1000) 3.3 -> 3300.0
    void setVref(float Vref){_VREF = Vref;};  
};

#endif
