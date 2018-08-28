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
#include "..\..\include\ComponentModule_Imp\ComponentModule_Imp_Buzzer_ATMega.h"

#if defined (TARGET_PLAT_AVR)

#include <Wire.h>
#include <Arduino.h>

ComponentModule_Imp_Buzzer_ATMega::ComponentModule_Imp_Buzzer_ATMega()
{
	pinMode(BUZZER_PIN, OUTPUT);
}

ComponentModule_Imp_Buzzer_ATMega::~ComponentModule_Imp_Buzzer_ATMega(){}

bool ComponentModule_Imp_Buzzer_ATMega::DoSelfDiagnostic_Imp()
{
	return true;
}

void ComponentModule_Imp_Buzzer_ATMega::MakeTone(const ToneItem * const buzzerTone)
{
	tone(BUZZER_PIN, buzzerTone->toneFrequency, buzzerTone->toneDurationMs);
	delay(buzzerTone->toneDurationMs);
}

void ComponentModule_Imp_Buzzer_ATMega::MakeTune(T_queue<ToneItem *> buzzerTones)
{
	ToneItem *ti = buzzerTones.Dequeue();
	while (ti)
	{
		MakeTone(ti);
		ti = buzzerTones.Dequeue();
	}
}

#endif
