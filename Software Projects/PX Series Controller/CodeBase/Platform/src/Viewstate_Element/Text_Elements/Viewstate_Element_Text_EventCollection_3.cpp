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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_EventCollection_3.h"

Viewstate_Element_Text_EventCollection_3::Viewstate_Element_Text_EventCollection_3(const int start_index, const int imbricationLevel, EventLog_Item_Collection * eventLog) :
	Viewstate_Element_Text(start_index, imbricationLevel), _eventLog(eventLog){}
Viewstate_Element_Text_EventCollection_3::~Viewstate_Element_Text_EventCollection_3(){}

int Viewstate_Element_Text_EventCollection_3::emplace(char * target, const int targetlen)
{
	uint8_t emplacedChars = 0;
	uint8_t timeStampOffset = 15;	

	for (uint8_t i = 0; i < EVENT_LOG_CACHE_SIZE; ++i)
	{
		EventLog_Item * log = _eventLog->GetEventLogItem(i);
		ViewstateStringAlias textAlias = log->eventTextAlias;

		if (textAlias != ViewstateStringAlias::ALIAS_NOT_SET)
		{
			Viewstate_Element_Text_DynamicText eventTxtVe{ _startIndex + (21 * i), imbricationLevel, textAlias };
			emplacedChars += eventTxtVe.emplace(target, targetlen);
		}
		else if (log->eventViewstateElement != nullptr)
		{
			log->eventViewstateElement->resetStartIndex(_startIndex + (21 * i));
			emplacedChars += log->eventViewstateElement->emplace(target, targetlen);
		}

		Viewstate_Element_Text_StaticTimeState eventTimeTxtVe{ (_startIndex + timeStampOffset) + (21 * i), imbricationLevel + 1, &log->_eventTS };		
		emplacedChars += eventTimeTxtVe.emplace(target, targetlen);
	}

	return emplacedChars;
}
