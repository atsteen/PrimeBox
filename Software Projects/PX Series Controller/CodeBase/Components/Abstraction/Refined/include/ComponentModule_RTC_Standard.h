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
#include "..\..\ComponentModule_RTC.h"
#include <stdlib.h>

class ComponentModule_RTC_Standard :
	public ComponentModule_RTC
{
public:
	ComponentModule_RTC_Standard(ComponentModule_Imp_RTC *imp);

	virtual ~ComponentModule_RTC_Standard() override;
	
	// Inherited via ComponentModule
	virtual bool DoSelfDiagnostic() override;

	// Inherited via ComponentModule_RTC
	virtual const char* GetCurrentTimeText() override;
	virtual const TimeSignature& GetCurrentSystemTime() override;

protected:
	char _time_text[6]; //TODO imp param get from DS
	TimeSignature _time_sig;
};

