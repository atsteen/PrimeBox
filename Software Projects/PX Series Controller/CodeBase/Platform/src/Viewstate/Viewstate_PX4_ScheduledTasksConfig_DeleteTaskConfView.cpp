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

#include "..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"

Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView::Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView(IModelViewstateData * viewstateData)
	: Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_CONF_VIEW), _viewstateData(viewstateData){}

Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView::~Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView(){}

char * Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextV_ConfLabel{ 22, 0, SCH_TASK_CONFIG_DELETE_TEXT_CONF };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_YesLabel{ 44, 0, DEFAULT_YES_TEXT, SELECTABLE_SCHEDULED_TASK_DELETE_CONFYES_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_NoLabel{ 65, 0, DEFAULT_NO_TEXT, SELECTABLE_SCHEDULED_TASK_DELETE_CONFNO_ELEMENT };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };

	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_dynamicTextVE_BackLabel);
	_vsDynElements.AddElement(&_dynamicTextV_ConfLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_YesLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_NoLabel);
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
