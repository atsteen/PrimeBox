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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_PowerRelayStateEvent.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_UnsignedTwoSegmentValue.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ComponentState.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ComponentState_Override.h"
#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayTypeShortName.h"
#include "..\..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

Viewstate_Element_Text_PowerRelayStateEvent::Viewstate_Element_Text_PowerRelayStateEvent(const int start_index, const int imbricationLevel, const int circuitIndex, const ComponentAssociation association, const ComponentPowerState powerState)
	: Viewstate_Element_Text(start_index, imbricationLevel, SELECTABLE_ELEMENT_NOT_SET), _circuitIndex(circuitIndex), _association(association), _powerState(powerState) {}

Viewstate_Element_Text_PowerRelayStateEvent::~Viewstate_Element_Text_PowerRelayStateEvent(){}

int Viewstate_Element_Text_PowerRelayStateEvent::emplace(char * target, const int targetlen)
{
	int emplacedCharCount = 0;
	
	//emplace circuit index
	Viewstate_Element_Text_UnsignedTwoSegmentValue staticVe_CircuitIndex(_startIndex, 1, _circuitIndex);
	emplacedCharCount += staticVe_CircuitIndex.emplace(target, targetlen);

	Viewstate_Element_Text_StaticText staticVe_colon(_startIndex + 2, 1, ":");
	emplacedCharCount += staticVe_colon.emplace(target, targetlen);

	//emplace shorthand alias text according to group affiliation
	Viewstate_Element_Text_RelayTypeShortName staticVe_relayShortTypeText(_startIndex + 3, 1, _association.typeAssociation);
	emplacedCharCount += staticVe_relayShortTypeText.emplace(target, targetlen);

	//emplace powerstate status at
	Viewstate_Element_Text_ComponentState staticVe_PowerState(_startIndex + 9, 1, _powerState);
	emplacedCharCount += staticVe_PowerState.emplace(target, targetlen);

	return emplacedCharCount;	
}
