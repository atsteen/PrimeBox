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
#include "..\include\ComponentModule_Imp_RTC_ATMega.h"

#if defined (TARGET_PLAT_AVR)

ComponentModule_Imp_RTC_ATMega::ComponentModule_Imp_RTC_ATMega()
{
  if (! _rtc.begin()) {
	  Serial.println("Couldn't find RTC");
	  while (1);
  }

  if (_rtc.lostPower()) {
	//reset from time service if applicable
  }
}

ComponentModule_Imp_RTC_ATMega::~ComponentModule_Imp_RTC_ATMega(){}

void ComponentModule_Imp_RTC_ATMega::GetCurrentSystemTime(TimeSignature& ts)
{
	DateTime now = _rtc.now();
	ts.SetSignature(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
}

bool ComponentModule_Imp_RTC_ATMega::DoSelfDiagnostic_Imp()
{
	return _rtc.begin();
}

#endif
