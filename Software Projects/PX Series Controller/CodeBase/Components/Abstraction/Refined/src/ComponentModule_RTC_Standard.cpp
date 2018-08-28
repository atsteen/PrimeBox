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

#include "..\include\ComponentModule_RTC_Standard.h"
#include "..\..\..\..\Configurations\PX4_Config.h"

ComponentModule_RTC_Standard::ComponentModule_RTC_Standard(ComponentModule_Imp_RTC* imp) : ComponentModule_RTC(imp){}

ComponentModule_RTC_Standard::~ComponentModule_RTC_Standard(){}

bool ComponentModule_RTC_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}

const char * ComponentModule_RTC_Standard::GetCurrentTimeText()
{
	char buff[3];
	GetCurrentSystemTime();
	
	#if defined(TARGET_PLAT_WIN32)
		_itoa_s(_time_sig.hour(), buff, 10);
	#else
		itoa(_time_sig.hour(), buff, 10);
	#endif

	if(_time_sig.hour() < 10)
	{
		_time_text[0] = '0';
		_time_text[1] = buff[0];
	}
	else {
		_time_text[0] = buff[0];
		_time_text[1] = buff[1];
	}

	_time_text[2] = ':';

	#if defined(TARGET_PLAT_WIN32)
		_itoa_s(_time_sig.minute(), buff, 10);
	#else
		itoa(_time_sig.minute(), buff, 10);
	#endif

	if (_time_sig.minute() < 10)
	{
		_time_text[3] = '0';
		_time_text[4] = buff[0];
	}
	else {
		_time_text[3] = buff[0];
		_time_text[4] = buff[1];
	}

	_time_text[5] = '\0';
	return _time_text;

	//_parentGroup->GetRtc()->DoSelfDiagnostic();
}

const TimeSignature & ComponentModule_RTC_Standard::GetCurrentSystemTime()
{
	_imp->GetCurrentSystemTime(_time_sig);
	return _time_sig;
}
