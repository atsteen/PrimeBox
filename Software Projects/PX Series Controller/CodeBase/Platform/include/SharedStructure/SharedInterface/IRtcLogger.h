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
#include "..\TimeSignature.h"
#include "..\EventLog_Item_Collection.h"
#include "..\..\Viewstate_Element\IViewstate_Element.h"
#include "..\..\Viewstate_String_Generator\Viewstate_String_Generator.h" //todo - move ViewstateStringAlias to shared structures

class IRtcLogger
{
public:
	IRtcLogger() {};
	~IRtcLogger();

	virtual const TimeSignature& CurrentTime() = 0;
	virtual const char* CurrentTimeAsText() = 0;
	virtual const EventLog_Item_Collection * GetEventLogItems() = 0;

	virtual void LogEvent(const ViewstateStringAlias) = 0;
	virtual void LogEvent(IViewstate_Element *) = 0;
	virtual void LogMessage(const char *) = 0;
	virtual void LogMessage(const ViewstateStringAlias textAlias) = 0;
	virtual void LogMessage(const ViewstateStringAlias textAlias, const bool value) = 0;
	virtual void LogMessage(const ViewstateStringAlias textAlias, const int value) = 0;
	virtual void LogMessage(const ViewstateStringAlias textAlias, const TimeSignature * value) = 0;	
};

inline IRtcLogger::~IRtcLogger() {}