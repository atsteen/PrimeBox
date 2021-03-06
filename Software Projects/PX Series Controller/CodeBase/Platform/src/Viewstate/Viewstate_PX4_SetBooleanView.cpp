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

#include "..\..\include\Viewstate\Viewstate_PX4_SetBooleanView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicThreeSegmentText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowDownRow.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_BooleanValue.h"
#include "..\..\include\SharedStructure\VElementList.h"

Viewstate_PX4_SetBooleanView::Viewstate_PX4_SetBooleanView(IModelViewstateData * viewstateData, const ViewstateAlias alias) :
	_viewstateData(viewstateData), Viewstate_PX4(alias){}

char * Viewstate_PX4_SetBooleanView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	IDynamicData * dynamicDataProxy = _viewstateData->GetDynamicDataProxy();
	const bool * dynamicBoolValue = dynamicDataProxy->getDynamicBoolValue();

	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, ViewstateStringAlias::DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_SaveLabel{ 15, 0, ViewstateStringAlias::DEFAULT_SAVE_TEXT, SelectableViewstateElementAlias::SELECTABLE_SAVE_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_EditLabel{ 28, 0, ViewstateStringAlias::DEFAULT_EDIT_TEXT, SelectableViewstateElementAlias::SELECTABLE_SETBOOLEANVALUE_ELEMENT };
	Viewstate_Element_Text_BooleanValue _dynamicTextVE_BooleanEnableValue{ 46, 0, *dynamicBoolValue, ViewstateStringAlias::COMPONENT_TEXT_STATE_ENABLED, ViewstateStringAlias::COMPONENT_TEXT_STATE_DISABLED };
	Viewstate_Element_Text_BooleanValue _dynamicTextVE_BooleanOnValue{ 46, 0, *dynamicBoolValue, ViewstateStringAlias::COMPONENT_TEXT_STATE_ON, ViewstateStringAlias::COMPONENT_TEXT_STATE_OFF };
	Viewstate_Element_Text_DynamicText _dynamicVE_PromptTitle{ 67, 0, dynamicDataProxy->getDynamicPromptTitle() };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };
	Viewstate_Element_Text_SelectArrowDownRow _selectArrowsOver{ -1, 1 };
	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ 19, 1 };

	//add viewstate elements to element collection
	AddViewstateElement(&_staticVE_BackSymbol);
	AddViewstateElement(&_dynamicTextVE_SaveLabel);
	AddViewstateElement(&_dynamicTextVE_BackLabel);
	AddViewstateElement(&_dynamicTextVE_EditLabel);
	AddViewstateElement(&_dynamicVE_PromptTitle);

	if (this->_viewstateAlias == ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ON_OFF){ AddViewstateElement(&_dynamicTextVE_BooleanOnValue); }
	else { AddViewstateElement(&_dynamicTextVE_BooleanEnableValue); }

	AddViewstateElement(&_ve_LineBreaks);

	Viewstate_Element_Text * v = _vsElements.GetTop();
	const SelectableViewstateElementAlias selectedElementAlias = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;

	while (v)
	{
		v->emplace(vs_OutBuffer, outBufferSize);
		v = v->nextElement;
	}

	switch(selectedElementAlias) {
		case SELECTABLE_SAVE_ELEMENT :
			_selectArrowRight.emplace(vs_OutBuffer, outBufferSize);
			break;
		case SELECTABLE_SETBOOLEANVALUE_ELEMENT :
			if (_viewstateData->GetDynamicViewstateModalState())
			{
				_selectArrowsOver.emplaceOver(vs_OutBuffer, outBufferSize, &_dynamicTextVE_EditLabel);
			}
			else
			{
				_selectArrowsOver.emplaceAround(vs_OutBuffer, outBufferSize, &_dynamicTextVE_EditLabel);
			}			
			break;
		default :
			_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
			break;
	};

	return vs_OutBuffer;
}
