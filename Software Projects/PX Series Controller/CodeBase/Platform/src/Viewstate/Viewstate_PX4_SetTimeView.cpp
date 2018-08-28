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

#include "..\..\include\Viewstate\Viewstate_PX4_SetTimeView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicTimeState.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowDownRow.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\SharedStructure\VElementList.h"
#include "..\..\include\SharedStructure\ViewstateAlias.h"

Viewstate_PX4_SetTimeView::Viewstate_PX4_SetTimeView(IModelViewstateData * viewstateData) :
	Viewstate_PX4(VIEWSTATEALIAS_INPUT_PROMPT_TIME), _viewstateData(viewstateData){}

char * Viewstate_PX4_SetTimeView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	IDynamicData * dynamicDataProxy = _viewstateData->GetDynamicDataProxy();
	const TimeSignature * dynamicTimeValue = dynamicDataProxy->getDynamicTimeValue();

	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_EditLabel{ 8, 0, ViewstateStringAlias::DEFAULT_EDIT_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_SaveLabel{ 15, 0, ViewstateStringAlias::DEFAULT_SAVE_TEXT, SelectableViewstateElementAlias::SELECTABLE_SAVE_ELEMENT };
	Viewstate_Element_Text_StaticText _staticVE_Set_HH_Label{ 27, 0, "HH", SelectableViewstateElementAlias::SELECTABLE_SETTIME_HH_ELEMENT };
	Viewstate_Element_Text_StaticText _staticVE_Set_TimeSeparator_Label{ 30, 0, ":"};
	Viewstate_Element_Text_StaticText _staticVE_Set_MM_Label{ 32, 0, "MM", SelectableViewstateElementAlias::SELECTABLE_SETTIME_MM_ELEMENT };
	Viewstate_Element_Text_DynamicTimeState _dynamicVE_taskTimeDisplayText{ 48, 1, !dynamicTimeValue ? 0 : dynamicTimeValue };
	Viewstate_Element_Text_DynamicText _dynamicVE_PromptTitle{ 67, 0,  dynamicDataProxy->getDynamicPromptTitle() };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	Viewstate_Element_Text_SelectArrowDownRow _selectArrowsOver{ -1, 1 };
	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ 19, 1 };

	//add viewstate elements to element collection
	AddViewstateElement(&_dynamicTextVE_BackLabel);
	AddViewstateElement(&_dynamicTextVE_SaveLabel);
	AddViewstateElement(&_dynamicTextVE_EditLabel);
	AddViewstateElement(&_staticVE_Set_HH_Label);
	AddViewstateElement(&_staticVE_Set_TimeSeparator_Label);
	AddViewstateElement(&_staticVE_Set_MM_Label);
	AddViewstateElement(&_dynamicVE_PromptTitle);
	AddViewstateElement(&_dynamicVE_taskTimeDisplayText);
	AddViewstateElement(&_ve_LineBreaks);

	Viewstate_Element_Text * v = _vsElements.GetTop();

	while (v)
	{
		v->emplace(vs_OutBuffer, outBufferSize);
		v = v->nextElement;
	}

	switch (_viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement) {
	case SelectableViewstateElementAlias::SELECTABLE_SETTIME_HH_ELEMENT:
		if (_viewstateData->GetDynamicViewstateModalState())
		{
			_selectArrowsOver.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_Set_HH_Label);
		}
		else
		{
			_selectArrowsOver.emplaceAround(vs_OutBuffer, outBufferSize, &_staticVE_Set_HH_Label);
		}
		break;

	case SelectableViewstateElementAlias::SELECTABLE_SETTIME_MM_ELEMENT:
		if (_viewstateData->GetDynamicViewstateModalState())
		{
			_selectArrowsOver.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_Set_MM_Label);
		}
		else
		{
			_selectArrowsOver.emplaceAround(vs_OutBuffer, outBufferSize, &_staticVE_Set_MM_Label);
		}
		break;

	case SelectableViewstateElementAlias::SELECTABLE_SAVE_ELEMENT:
		_selectArrowRight.emplace(vs_OutBuffer, outBufferSize);
		break;

	default:
		_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
	}

	return vs_OutBuffer;
}
