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

#include "..\..\include\SharedStructure\EventLog_Item_Collection.h"

void EventLog_Item_Collection::LogEvent(const ViewstateStringAlias newLogEventText, const TimeSignature * newLogEventTime)
{
	for (uint8_t i = EVENT_LOG_CACHE_SIZE - 1; i > 0; --i)
	{
		if (i == EVENT_LOG_CACHE_SIZE - 1 && _eventLogItems[i].eventViewstateElement != nullptr)
		{
			delete _eventLogItems[i].eventViewstateElement; //clean up heap allocated element
		}

		_eventLogItems[i] = _eventLogItems[i - 1];
	}

	_eventLogItems[0].eventTextAlias = newLogEventText;
	_eventLogItems[0]._eventTS = *newLogEventTime;
}

void EventLog_Item_Collection::LogEvent(IViewstate_Element * newLogViewstateElement, const TimeSignature * newLogEventTime)
{
	for (uint8_t i = EVENT_LOG_CACHE_SIZE - 1; i > 0; --i)
	{
		if (i == EVENT_LOG_CACHE_SIZE - 1 && _eventLogItems[i].eventViewstateElement != nullptr)
		{
			delete _eventLogItems[i].eventViewstateElement; //clean up heap allocated element
		}

		_eventLogItems[i] = _eventLogItems[i - 1];
	}

	_eventLogItems[0].eventTextAlias = ALIAS_NOT_SET;
	_eventLogItems[0].eventViewstateElement = newLogViewstateElement;
	_eventLogItems[0]._eventTS = *newLogEventTime;
}

EventLog_Item * EventLog_Item_Collection::GetEventLogItem(uint8_t index)
{
	if (index >= EVENT_LOG_CACHE_SIZE) { return nullptr; }
	return &_eventLogItems[index];
}
