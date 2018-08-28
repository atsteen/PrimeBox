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

#include "..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateTaskByRelayView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayTypeShortName.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayGroupShortName.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_UnsignedTwoSegmentValue.h"
#include "..\..\include\SharedStructure\VElementList.h"

Viewstate_PX4_ScheduledTasksConfig_CreateTaskByRelayView::Viewstate_PX4_ScheduledTasksConfig_CreateTaskByRelayView(IModelTaskData * taskData, IModelViewstateData * viewstateData) :
	_viewstateData(viewstateData), _taskData(taskData), Viewstate_PX4(VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_RELAY_VIEW){}

char * Viewstate_PX4_ScheduledTasksConfig_CreateTaskByRelayView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);
	const int * const selectedRelayIndex = _taskData->GetCreateSchdTaskTargetIndex();
	const ComponentAssociation * currentRelayAssociation = _taskData->GetCreateSchdTaskTarget();

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, ViewstateStringAlias::DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_SaveLabel{ 15, 0, ViewstateStringAlias::DEFAULT_SAVE_TEXT, SelectableViewstateElementAlias::SELECTABLE_SAVE_ELEMENT };

	Viewstate_Element_Text_DynamicText _dynamicVE_ByIndexLabel{ 22, 0, ViewstateStringAlias::SCH_TASK_CONFIG_CREATE_TEXT_TASKTARGET, SelectableViewstateElementAlias::SELECTABLE_SCHEDULED_TASK_CREATE_RELAY_TASK_ELEMENT };
	Viewstate_Element_Text_StaticText _staticVe_LabelColon(28, 1, ":");

	Viewstate_Element_Text_UnsignedTwoSegmentValue _staticVe_CircuitIndex(30, 1, *selectedRelayIndex);
	Viewstate_Element_Text_StaticText _staticVe_IndexColon(32, 1, ":");
	Viewstate_Element_Text_RelayTypeShortName _dynamicVE_RelayType(33, 1, currentRelayAssociation->typeAssociation);

	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };
	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ 19, 1 };

	//add viewstate elements to element collection
	AddViewstateElement(&_dynamicTextVE_BackLabel);	
	AddViewstateElement(&_dynamicTextVE_SaveLabel);
	AddViewstateElement(&_dynamicVE_ByIndexLabel);
	AddViewstateElement(&_staticVe_LabelColon);
	AddViewstateElement(&_staticVe_CircuitIndex);
	AddViewstateElement(&_staticVe_IndexColon);
	AddViewstateElement(&_dynamicVE_RelayType);
	AddViewstateElement(&_ve_LineBreaks);
	const SelectableViewstateElementAlias selectedElementAlias = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;

	if (selectedElementAlias == SELECTABLE_BACK_ELEMENT)
	{
		_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
	}
	else { _staticVE_BackSymbol.emplace(vs_OutBuffer, outBufferSize); }

	Viewstate_Element_Text * v = _vsElements.GetTop();
	while (v)
	{
		if (v->alias == selectedElementAlias)
		{
			_selectArrowRight.emplaceLeft(vs_OutBuffer, outBufferSize, v);
		}

		v->emplace(vs_OutBuffer, outBufferSize);
		v = v->nextElement;
	}

	return vs_OutBuffer;
}
