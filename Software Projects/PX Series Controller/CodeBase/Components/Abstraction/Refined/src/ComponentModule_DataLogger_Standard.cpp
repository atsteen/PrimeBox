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

#include "..\include\ComponentModule_DataLogger_Standard.h"
#include "..\..\..\..\Configurations\PX4_Config.h"

ComponentModule_DataLogger_Standard::ComponentModule_DataLogger_Standard(ComponentModule_Imp_DataLogger *imp, ComponentModule_RTC *timeProvider) : ComponentModule_DataLogger(imp), _timeProvider(timeProvider){}

ComponentModule_DataLogger_Standard::~ComponentModule_DataLogger_Standard(){}

EventLog_Item_Collection * ComponentModule_DataLogger_Standard::GetEvents()
{
	return &_eventLog;
}

void ComponentModule_DataLogger_Standard::LogSystemEvent(const ViewstateStringAlias textAlias)
{
	_imp->LogMessage(Viewstate_String_Generator::GetViewstateString(textAlias));
	_eventLog.LogEvent(textAlias, &_timeProvider->GetCurrentSystemTime());
}

void ComponentModule_DataLogger_Standard::LogSystemEvent(IViewstate_Element * eventElement)
{
	char dispRowText[DISPLAY_ROW_LENGTH] = "\0";
	eventElement->emplace(dispRowText, DISPLAY_ROW_LENGTH - 1);
	_imp->LogMessage(dispRowText);
	_eventLog.LogEvent(eventElement, &_timeProvider->GetCurrentSystemTime());
}

void ComponentModule_DataLogger_Standard::LogSystemEventImmediate(const ViewstateStringAlias textAlias)
{
	_imp->LogMessageImmediate(Viewstate_String_Generator::GetViewstateString(textAlias));
	_eventLog.LogEvent(textAlias, &_timeProvider->GetCurrentSystemTime());
}

void ComponentModule_DataLogger_Standard::LogMessage(const char * logStr)
{
	_imp->LogMessage(logStr);
}

void ComponentModule_DataLogger_Standard::LogMessageImmediate(const char * logStr)
{
	_imp->LogMessageImmediate(logStr);
}

void ComponentModule_DataLogger_Standard::LogMessageVerbose(const ViewstateStringAlias textAlias, const bool value)
{
	_imp->LogMessageImmediate(Viewstate_String_Generator::GetViewstateString(textAlias), true, false);
	_imp->LogMessageImmediate(value ? "true" : "false", false, true);
}

void ComponentModule_DataLogger_Standard::LogMessageVerbose(const ViewstateStringAlias textAlias, const int value)
{
	if (value > 9999 || value < -9999) { return; } //todo... cmon man...
	char buff[6];

	#if defined(TARGET_PLAT_WIN32)
		_itoa_s(value, buff, 10);
	#else
		itoa(value, buff, 10);
	#endif

	_imp->LogMessageImmediate(Viewstate_String_Generator::GetViewstateString(textAlias), true, false);
	_imp->LogMessageImmediate(buff, false, true);
}

void ComponentModule_DataLogger_Standard::LogMessageVerbose(const ViewstateStringAlias textAlias, const TimeSignature * value)
{
	char timeText[11] = { '\0' };
	timeText[0] = '[';
	value->TimeText_hhmm(timeText,1);
	timeText[6] = ':';
	value->TimeText_ss(timeText, 7);
	timeText[9] = ']';

	_imp->LogMessageImmediate(Viewstate_String_Generator::GetViewstateString(textAlias), true, false);
	_imp->LogMessageImmediate(timeText, false, true);
}

bool ComponentModule_DataLogger_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}
