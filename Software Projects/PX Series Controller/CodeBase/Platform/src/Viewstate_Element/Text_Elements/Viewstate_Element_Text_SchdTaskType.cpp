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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SchdTaskType.h"

Viewstate_Element_Text_SchdTaskType::Viewstate_Element_Text_SchdTaskType(const int start_index, const int imbricationLevel, const TaskAlias taskAlias) :
	Viewstate_Element_Text(start_index, imbricationLevel), _taskAlias(taskAlias){}

Viewstate_Element_Text_SchdTaskType::~Viewstate_Element_Text_SchdTaskType(){}

int Viewstate_Element_Text_SchdTaskType::emplace(char * target, const int targetlen)
{
	switch (_taskAlias) {
		case TaskAlias::TASKALIAS_NOT_SET:
			return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_NOT_SET));
	
		//case TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_PUMP:
		//	return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_ENABLE_PUMP));

		//case TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_PUMP:
		//	return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_DISABLE_PUMP));

		//case TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_FAN:
		//	return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_ENABLE_FANS));

		//case TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_FAN:
		//	return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_DISABLE_FANS));

		//case TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_LIGHTS:
		//	return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_ENABLE_LIGHTS));

		//case TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_LIGHTS:
		//	return _emplace(target, targetlen, Viewstate_String_Generator::GetViewstateString(TASKALIAS_DISPLAY_TEXT_DISABLE_LIGHTS));

		default:
			//todo... fix this dynamic viewstate element
			return 0;
		}
}
