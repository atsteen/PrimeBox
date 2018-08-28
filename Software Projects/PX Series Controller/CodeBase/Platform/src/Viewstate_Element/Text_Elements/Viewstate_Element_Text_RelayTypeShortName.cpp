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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayTypeShortName.h"
#include "..\..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

Viewstate_Element_Text_RelayTypeShortName::Viewstate_Element_Text_RelayTypeShortName(const int start_index, const int imbricationLevel, const ComponentTypeAssociation typeAssociation)
	: Viewstate_Element_Text(start_index, imbricationLevel), _typeAssociation(typeAssociation) {}

Viewstate_Element_Text_RelayTypeShortName::~Viewstate_Element_Text_RelayTypeShortName(){}

int Viewstate_Element_Text_RelayTypeShortName::emplace(char * target, const int targetlen)
{
	switch (_typeAssociation) {

		case ComponentTypeAssociation::FAN_CIRCULATION :
			return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(ViewstateStringAlias::COMPONENT_TEXT_SHORT_CIRCULATION_FAN));
			break;

		case ComponentTypeAssociation::FAN_EXHAUST :
			return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(ViewstateStringAlias::COMPONENT_TEXT_SHORT_EXHAUST_FAN));
			break;

		case ComponentTypeAssociation::LIGHT_PRIMARY :

			return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(ViewstateStringAlias::COMPONENT_TEXT_SHORT_LIGHT));
			break;

		case ComponentTypeAssociation::PUMP_WATER:	
			return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(ViewstateStringAlias::COMPONENT_TEXT_SHORT_PUMP));
			break;

		default:
			return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(ViewstateStringAlias::COMPONENT_TEXT_SHORT_OUTLET));
	}
}
