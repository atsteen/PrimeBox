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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ScheduledTaskList_Edit_Row.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayTypeShortName.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayGroupShortName.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_UnsignedTwoSegmentValue.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticTimeState.h"

Viewstate_Element_Text_ScheduledTaskList_Edit_Row::Viewstate_Element_Text_ScheduledTaskList_Edit_Row(const int start_index, const int imbricationLevel, ScheduledTaskDetail * taskDetail)
	: Viewstate_Element_Text(start_index, imbricationLevel, SELECTABLE_ELEMENT_NOT_SET), _taskDetail(taskDetail){}

Viewstate_Element_Text_ScheduledTaskList_Edit_Row::~Viewstate_Element_Text_ScheduledTaskList_Edit_Row(){}

int Viewstate_Element_Text_ScheduledTaskList_Edit_Row::emplace(char * target, const int targetlen)
{
	uint8_t emplacedCharCount = 0;

	//emplace type association
	Viewstate_Element_Text_RelayTypeShortName dynamicText_relayType(_startIndex + 1, 0, _taskDetail->GetScheduledTaskrelayAssociation()->typeAssociation);
	emplacedCharCount += dynamicText_relayType.emplace(target, targetlen);

	//emplace group association or relay index
	if (*_taskDetail->GetScheduledTaskrelayIndex() > 0)
	{
		Viewstate_Element_Text_StaticText staticText_RelayIdPrefix(_startIndex + 7, 0, Viewstate_String_Generator::defaultRelayIdPrefixText);
		emplacedCharCount += staticText_RelayIdPrefix.emplace(target, targetlen);

		Viewstate_Element_Text_UnsignedTwoSegmentValue staticVe_CircuitIndex(_startIndex + 9, 1, *_taskDetail->GetScheduledTaskrelayIndex());
		emplacedCharCount += staticVe_CircuitIndex.emplace(target, targetlen);
	}
	else
	{
		Viewstate_Element_Text_RelayGroupShortName dynamicText_relayGroup(_startIndex + 7, 0, _taskDetail->GetScheduledTaskrelayAssociation()->groupAssociation);
		emplacedCharCount += dynamicText_relayGroup.emplace(target, targetlen);
	}

	//emplace task time text
	Viewstate_Element_Text_StaticTimeState staticVe_taskTimeText(_startIndex + 12, 1, _taskDetail->GetScheduledTaskExecutionTime());
	emplacedCharCount += staticVe_taskTimeText.emplace(target, targetlen);

	//emplace task status symbol
	if (*_taskDetail->GetScheduledTaskEnabledState())
	{
		Viewstate_Element_Text_StaticText staticText_taskStatus(_startIndex + 18, 0, Viewstate_String_Generator::enabledSymbol);
		emplacedCharCount += staticText_taskStatus.emplace(target, targetlen);
	}
	else
	{
		Viewstate_Element_Text_StaticText staticText_taskStatus(_startIndex + 18, 0, Viewstate_String_Generator::disabledSymbol);
		emplacedCharCount += staticText_taskStatus.emplace(target, targetlen);
	}

	return emplacedCharCount;	
}
