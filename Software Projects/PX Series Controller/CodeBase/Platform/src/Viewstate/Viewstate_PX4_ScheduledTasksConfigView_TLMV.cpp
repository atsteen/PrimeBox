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

#include "..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfigView_TLMV.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\SharedStructure\VElementList.h"
#include "..\..\include\SharedStructure\ViewstateAlias.h"

Viewstate_PX4_ScheduledTasksConfigView_TLMV::Viewstate_PX4_ScheduledTasksConfigView_TLMV()
	: Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW_TLMV){}

Viewstate_PX4_ScheduledTasksConfigView_TLMV::~Viewstate_PX4_ScheduledTasksConfigView_TLMV() {}

char * Viewstate_PX4_ScheduledTasksConfigView_TLMV::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_DynamicText _dynamicVE_TLMV_TitleLine1{ 23, 0, SCH_TASK_CONFIG_TLMV_TEXT_TITLE };
	Viewstate_Element_Text_DynamicText _dynamicVE_TLMV_TitleLine2{ 43, 0, DEFAULT_TLMV_TEXT_SETTINGS };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	//add viewstate elements to element collection
	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_dynamicVE_TLMV_TitleLine1);
	_vsDynElements.AddElement(&_dynamicVE_TLMV_TitleLine2);
	_vsDynElements.AddElement(&_ve_LineBreaks);

	Viewstate_Element_Text * v = _vsDynElements.GetTop();

	while (v)
	{
		v->emplace(vs_OutBuffer, outBufferSize);
		v = v->nextElement;
	}

	return vs_OutBuffer;
}
