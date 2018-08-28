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
#include "..\..\include\PreProcDirectives.h"
#include "..\..\include\ComponentModule_imp\ComponentModule_Imp_RTC.h"

#if defined(TARGET_PLAT_AVR)

#include "..\..\include\libraries\RTCLib\RTClib.h"
#include <Wire.h>

class ComponentModule_Imp_RTC_ATMega :
	public ComponentModule_Imp_RTC
{
public:
	ComponentModule_Imp_RTC_ATMega();
	virtual ~ComponentModule_Imp_RTC_ATMega() override;

	// Inherited via ComponentModule_Imp_RTC
	virtual bool DoSelfDiagnostic_Imp() override;
	virtual void GetCurrentSystemTime(TimeSignature&) override;

protected:
	RTC_DS3231 _rtc;
};

#endif 