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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_PowerRelayStateList.h"
#include "..\..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_PowerRelayStateList_Row.h"

Viewstate_Element_Text_PowerRelayStateList::Viewstate_Element_Text_PowerRelayStateList(const int start_index, const int imbricationLevel, IModelViewstateData * viewstateData, IPowerRelayArray * powerRelays)
	: Viewstate_Element_Text(start_index, imbricationLevel, SELECTABLE_SCHEDULED_TASKLIST_EDIT_ELEMENT), _viewstateData(viewstateData), _powerRelays(powerRelays){}

Viewstate_Element_Text_PowerRelayStateList::~Viewstate_Element_Text_PowerRelayStateList(){}

int Viewstate_Element_Text_PowerRelayStateList::emplace(char * target, const int targetlen)
{
	//check and correct selectedListIndex against powerRelayArray count
	const uint8_t selectedListIndex = _viewstateData->GetViewstateSelectableElementIndex();
	const uint8_t lastTaskPowerRelayIndex = _powerRelays->CircuitCount();
	if (selectedListIndex > lastTaskPowerRelayIndex) { _viewstateData->SetViewstateSelectableElementIndex(lastTaskPowerRelayIndex); }
	
	uint8_t emplacedChars = 0;
	
	if (selectedListIndex < 3)
	{
		//dynamically emplace first three items using Viewstate_Element_Text_ScheduledTaskList_Edit_Row
		for (int i = 0; i < 3; i++)
		{
			const ComponentPowerState state = _powerRelays->GetRelayPowerStateByIndex(i);
			const ComponentAssociation componentAssociation = *_powerRelays->GetRelayComponentAssociationByIndex(i);

			Viewstate_Element_Text_PowerRelayStateList_Row listRowVE_PowerRelay(_startIndex + 1 + i * 21, 2, i, componentAssociation, state);

			//prefix select arrow on row if row is selected
			if (i == selectedListIndex && _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement == SELECTABLE_ELEMENT_DYNAMIC)
			{
				Viewstate_Element_Text_SelectArrowRight selectArrow(-1, 1);
				emplacedChars += selectArrow.emplaceLeft(target, targetlen, &listRowVE_PowerRelay);
			}
				
			emplacedChars += listRowVE_PowerRelay.emplace(target, targetlen);
		}			
	}
	else
	{		
		//dynamically emplace block of up to four rows
		for (int i = (((selectedListIndex + 1)/4) * 4) -1; i < (((selectedListIndex + 1) / 4) * 4) + 3; ++i)
		{
			if (i >= _powerRelays->CircuitCount()) { break; }

			const ComponentPowerState state = _powerRelays->GetRelayPowerStateByIndex(i);
			const ComponentAssociation * association = _powerRelays->GetRelayComponentAssociationByIndex(i);

			Viewstate_Element_Text_PowerRelayStateList_Row listRowVE_PowerRelay(_startIndex + 1 + (((i + 1) % 4) * 21), 2, i, *association, state);

			//prefix select arrow on row if row is selected
			if (i == selectedListIndex && _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement == SELECTABLE_ELEMENT_DYNAMIC)
			{
				Viewstate_Element_Text_SelectArrowRight selectArrow(-1, 1);
				emplacedChars += selectArrow.emplaceLeft(target, targetlen, &listRowVE_PowerRelay);
			}
				
			emplacedChars += listRowVE_PowerRelay.emplace(target, targetlen);
		}
	}

	return emplacedChars;
}
