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

#include "..\include\ComponentPackage_RtcLogger.h"

ComponentPackage_RtcLogger::ComponentPackage_RtcLogger(ComponentModuleImp_Factory_PX4* componentImpFactory)
{
	_rtc = new ComponentModule_RTC_Standard(componentImpFactory->Make_RTC());
	_logger = new ComponentModule_DataLogger_Standard(componentImpFactory->Make_DataLogger(), _rtc);
}

ComponentPackage_RtcLogger::~ComponentPackage_RtcLogger()
{
	delete _rtc;
	delete _logger;
}

const TimeSignature & ComponentPackage_RtcLogger::CurrentTime()
{
	return _rtc->GetCurrentSystemTime();
}

const char * ComponentPackage_RtcLogger::CurrentTimeAsText()
{
	return _rtc->GetCurrentTimeText();
}

void ComponentPackage_RtcLogger::LogEvent(const ViewstateStringAlias eventAlias)
{
	_logger->LogSystemEvent(eventAlias);
}

void ComponentPackage_RtcLogger::LogEvent(IViewstate_Element * eventTextElement)
{
	_logger->LogSystemEvent(eventTextElement);
}

void ComponentPackage_RtcLogger::LogMessage(const char * msgText)
{
	_logger->LogMessage(msgText);
}

void ComponentPackage_RtcLogger::LogMessage(const ViewstateStringAlias textAlias)
{
	_logger->LogMessage(Viewstate_String_Generator::GetViewstateString(textAlias));
}

EventLog_Item_Collection * ComponentPackage_RtcLogger::GetEventLogItems()
{
	return _logger->GetEvents();
}

void ComponentPackage_RtcLogger::LogMessage(const ViewstateStringAlias textAlias, const bool value)
{
	_logger->LogMessageVerbose(textAlias, value);
}

void ComponentPackage_RtcLogger::LogMessage(const ViewstateStringAlias textAlias, const int value)
{
	_logger->LogMessageVerbose(textAlias, value);
}

void ComponentPackage_RtcLogger::LogMessage(const ViewstateStringAlias textAlias, const TimeSignature * value)
{
	_logger->LogMessageVerbose(textAlias, value);
}
