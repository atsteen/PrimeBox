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

#include "..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateTaskView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_TimeState.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SchdTaskType.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_UnsignedTwoSegmentValue.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayTypeShortName.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayGroupShortName.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_BooleanValue.h"

Viewstate_PX4_ScheduledTasksConfig_CreateTaskView::Viewstate_PX4_ScheduledTasksConfig_CreateTaskView(IModelTaskData * taskData, IModelViewstateData * viewstateData)
	: Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TASK_VIEW), _taskData(taskData), _viewstateData(viewstateData) {}

Viewstate_PX4_ScheduledTasksConfig_CreateTaskView::~Viewstate_PX4_ScheduledTasksConfig_CreateTaskView(){}

char * Viewstate_PX4_ScheduledTasksConfig_CreateTaskView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);
	const int * const _circuitIndex  = _taskData->GetCreateSchdTaskTargetIndex();
	const ComponentAssociation * const association = _taskData->GetCreateSchdTaskTarget();
	const bool * const action = _taskData->GetCreateSchdTaskAction();
	const TimeSignature * const taskTime = _taskData->GetCreateSchdTaskTime();

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol, SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_SaveLabel{ 15, 0, ViewstateStringAlias::DEFAULT_SAVE_TEXT, SelectableViewstateElementAlias::SELECTABLE_SAVE_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_TaskTargetLabel{ 22, 0, SCH_TASK_CONFIG_CREATE_TEXT_TASKTARGET, SELECTABLE_SCHEDULED_TASK_TASK_TARGET_ELEMENT };
	Viewstate_Element_Text_StaticText _staticVe_TaskTargetLabelColon{ 28,1, Viewstate_String_Generator::colonSymbol };

	int targetplacement = 30;
	Viewstate_Element_Text_UnsignedTwoSegmentValue _staticVe_CircuitIndex(targetplacement, 1, *_circuitIndex);
	Viewstate_Element_Text_StaticText _staticVe_TaskTargetColon{ targetplacement + 2,1, Viewstate_String_Generator::colonSymbol };

	if (*_circuitIndex >= 0){ targetplacement = 33; }

	Viewstate_Element_Text_RelayTypeShortName _staticVe_RelayShortTypeText(targetplacement, 1, association->typeAssociation);
	Viewstate_Element_Text_RelayGroupShortName _staticVe_RelayGroupShortText(targetplacement + 6, 1, association->groupAssociation);
	
	Viewstate_Element_Text_DynamicText _dynamicTextVE_TaskActionLabel{ 43, 0, SCH_TASK_CONFIG_CREATE_TEXT_TASKACTION, SELECTABLE_SCHEDULED_TASK_TASK_ACTION_ELEMENT };
	Viewstate_Element_Text_StaticText _staticVe_TaskActionLabelColon{ 49,1, Viewstate_String_Generator::colonSymbol };
	Viewstate_Element_Text_BooleanValue _dynamicTextVE_ActionAssignment{ 50, 1, *action, ViewstateStringAlias::COMPONENT_TEXT_STATE_ENABLED,ViewstateStringAlias::COMPONENT_TEXT_STATE_DISABLED };

	Viewstate_Element_Text_DynamicText _dynamicTextVE_StartTimeLabel{ 64, 0, SCH_TASK_CONFIG_CREATE_TEXT_TASKTIME, SELECTABLE_SCHEDULED_TASK_TASK_TIME_ELEMENT };
	Viewstate_Element_Text_StaticText _staticVe_TaskTimeLabelColon{ 68,1, Viewstate_String_Generator::colonSymbol };
	Viewstate_Element_Text_TimeState _dynamicVE_TaskTimeAssignment{ 69, 1, *taskTime };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };

	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_dynamicTextVE_BackLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_SaveLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_TaskTargetLabel);
	_vsDynElements.AddElement(&_staticVe_TaskTargetLabelColon);

	if (*_circuitIndex >= 0)
	{
		_vsDynElements.AddElement(&_staticVe_CircuitIndex);	
		_vsDynElements.AddElement(&_staticVe_TaskTargetColon);
	}
	else{ _vsDynElements.AddElement(&_staticVe_RelayGroupShortText); }

	_vsDynElements.AddElement(&_staticVe_RelayShortTypeText);
	_vsDynElements.AddElement(&_dynamicTextVE_TaskActionLabel);
	_vsDynElements.AddElement(&_staticVe_TaskActionLabelColon);
	_vsDynElements.AddElement(&_dynamicTextVE_ActionAssignment);
	_vsDynElements.AddElement(&_dynamicTextVE_StartTimeLabel);
	_vsDynElements.AddElement(&_staticVe_TaskTimeLabelColon);
	_vsDynElements.AddElement(&_dynamicVE_TaskTimeAssignment);
	_vsDynElements.AddElement(&_ve_LineBreaks);

	const SelectableViewstateElementAlias selectedElementAlias = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;

	if (selectedElementAlias == SELECTABLE_BACK_ELEMENT)
	{
		_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
	}
	else { _staticVE_BackSymbol.emplace(vs_OutBuffer, outBufferSize); }

	Viewstate_Element_Text * v = _vsDynElements.GetTop();
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
