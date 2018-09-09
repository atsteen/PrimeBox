/*
* This file is part of the PX series horticulture appliance codebase (https://github.com/atsteen/PrimeBox).
* Copyright (c) 2017-2018 Sound Venture Group LLC.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "PX4_Config.h"

#if defined (TARGET_PLAT_AVR)
/*
 * Rotary encoder library for Arduino.
 */

#ifndef rotary_h
#define rotary_h
#include "Arduino.h"
// Enable this to emit codes twice per step.
#define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
  public:
    Rotary(char, char);
    // Process pin(s)
    unsigned char process();
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
};

#endif
#endif