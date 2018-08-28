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

#include "..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SignedTwoSegmentValue.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"

Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView::Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView(IModelTaskData * taskData, IModelViewstateData * viewstateData)
	: Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW), _taskData(taskData), _viewstateData(viewstateData){}

Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView::~Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView(){}

char * Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_CreateTaskLabel{ 22, 0, SCH_TASK_CONFIG_MENU_TEXT_CREATE, SELECTABLE_MENU_SELECT_NEW_SCHD_TASK_ELEMENT };
	Viewstate_Element_Text_SignedTwoSegmentValue _signedValueVE_freeTaskLabel{ 36, 1, _taskData->GetFreeScheduledTaskDetailCount() };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_DeleteTaskLabel{ 43, 0, SCH_TASK_CONFIG_MENU_TEXT_DELETE, SELECTABLE_MENU_SELECT_DELETE_SCHD_TASK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BulkDeleteLabel{ 64, 0, SCH_TASK_CONFIG_MENU_TEXT_BULKDELETE, SELECTABLE_MENU_SELECT_BULK_DELETE_SCHD_TASK_ELEMENT };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };

	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_dynamicTextVE_BackLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_CreateTaskLabel);
	_vsDynElements.AddElement(&_signedValueVE_freeTaskLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_DeleteTaskLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_BulkDeleteLabel);
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
