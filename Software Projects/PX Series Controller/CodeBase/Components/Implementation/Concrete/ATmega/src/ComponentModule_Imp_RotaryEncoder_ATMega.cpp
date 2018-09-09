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
#include "..\include\componentmodule_imp_rotaryencoder_atmega.h"

#if defined (TARGET_PLAT_AVR)

Rotary rEncoder(ENCODER_D1, ENCODER_D2);
volatile bool btnReleased = true;
volatile TaskAlias FlaggedTask = TASKALIAS_NOT_SET;

//ISR for encoder
void isr_rotate()
{
	unsigned char result = rEncoder.process();
	if (result == DIR_CW)
	{
		FlaggedTask = TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT;
	} 
	else if (result == DIR_CCW)
	{
		FlaggedTask = TASKALIAS_NAVIGATION_MENU_MOVE_LEFT;
	}
}

void isr_select()
{
	btnReleased = !btnReleased; //encoder select triggers twice, once down, then up - only count up trigger
	if(btnReleased){ FlaggedTask = TASKALIAS_NAVIGATION_MENU_SELECT; }	
}

ComponentModule_Imp_RotaryEncoder_ATMega::ComponentModule_Imp_RotaryEncoder_ATMega()
{
	pinMode(ENCODER_SW, INPUT);
	digitalWrite (ENCODER_SW, HIGH);

	attachInterrupt(digitalPinToInterrupt(ENCODER_SW), isr_select, CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENCODER_D1), isr_rotate, CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENCODER_D2), isr_rotate, CHANGE);
}

ComponentModule_Imp_RotaryEncoder_ATMega::~ComponentModule_Imp_RotaryEncoder_ATMega() {}

bool ComponentModule_Imp_RotaryEncoder_ATMega::DoSelfDiagnostic_Imp()
{
	return true;
}

TaskAlias ComponentModule_Imp_RotaryEncoder_ATMega::GetFlaggedTask()
{
	const TaskAlias currentFlaggedTask = FlaggedTask;
	FlaggedTask = TASKALIAS_NOT_SET; // Clear flagged task
	return currentFlaggedTask;
}

#endif