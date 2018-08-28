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

#include "..\..\ComponentModule_DataLogger.h"
#include "..\..\ComponentModule_RTC.h"
#include "..\..\..\..\Platform\include\SharedStructure\EventLog_Item_Collection.h"

class ComponentModule_DataLogger_Standard :
	public ComponentModule_DataLogger
{
public:
	ComponentModule_DataLogger_Standard(ComponentModule_Imp_DataLogger *imp, ComponentModule_RTC *timeProvider);
	virtual ~ComponentModule_DataLogger_Standard() override;

	EventLog_Item_Collection * GetEvents();

	void LogSystemEventImmediate(const ViewstateStringAlias textAlias);
	void LogMessageImmediate(const char * message);

	void LogMessageVerbose(const ViewstateStringAlias textAlias, const bool value);
	void LogMessageVerbose(const ViewstateStringAlias textAlias, const int value);
	void LogMessageVerbose(const ViewstateStringAlias textAlias, const TimeSignature * value);

	virtual void LogSystemEvent(IViewstate_Element *);

	// Inherited via ComponentModule
	virtual bool DoSelfDiagnostic() override;

	// Inherited via ComponentModule_DataLogger
	virtual void LogSystemEvent(const ViewstateStringAlias) override;	
	virtual void LogMessage(const char *) override;

private:
	EventLog_Item_Collection _eventLog;
	ComponentModule_RTC * _timeProvider;
};