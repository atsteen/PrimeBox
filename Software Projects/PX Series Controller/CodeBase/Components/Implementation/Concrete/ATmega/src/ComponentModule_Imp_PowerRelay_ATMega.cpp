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

#pragma once
#include "..\..\include\ComponentModule_Imp\ComponentModule_Imp_PowerRelay_ATMega.h"

#if defined (TARGET_PLAT_AVR)

#include <Wire.h>
#include <Arduino.h>

ComponentModule_Imp_PowerRelay_ATMega::ComponentModule_Imp_PowerRelay_ATMega(int pin)
{
	_assignedPin = pin;
	pinMode(_assignedPin, OUTPUT);
	digitalWrite(_assignedPin, HIGH);
}

ComponentModule_Imp_PowerRelay_ATMega::~ComponentModule_Imp_PowerRelay_ATMega(){}

bool ComponentModule_Imp_PowerRelay_ATMega::DoSelfDiagnostic_Imp()
{
	return true;
}

const bool ComponentModule_Imp_PowerRelay_ATMega::GetState()
{
	if(digitalRead(_assignedPin) == LOW){ return true; }
	else{ return false; }
}

void ComponentModule_Imp_PowerRelay_ATMega::SetState(bool state)
{
	if(state == true){ digitalWrite(_assignedPin, LOW); }
	else{ digitalWrite(_assignedPin, HIGH); }
}

#endif
