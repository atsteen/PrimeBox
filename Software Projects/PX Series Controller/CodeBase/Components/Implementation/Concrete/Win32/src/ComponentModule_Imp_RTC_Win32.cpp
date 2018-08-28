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

#include "..\include\ComponentModule_Imp_RTC_Win32.h"

#if defined(TARGET_PLAT_WIN32)

ComponentModule_Imp_RTC_Win32::ComponentModule_Imp_RTC_Win32(){}

ComponentModule_Imp_RTC_Win32::~ComponentModule_Imp_RTC_Win32(){}

bool ComponentModule_Imp_RTC_Win32::DoSelfDiagnostic_Imp()
{
	time_t t;
	if (time(&t) < 0) { return false; };  // time() returns -1 on fail
	return true;
}

void ComponentModule_Imp_RTC_Win32::GetCurrentSystemTime(TimeSignature& ts)
{
	time_t _t;
	tm _tm;
	time(&_t);
	localtime_s(&_tm,&_t);

	ts.SetSignature(_tm.tm_year + 1900, _tm.tm_mon + 1, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec);
}

#endif