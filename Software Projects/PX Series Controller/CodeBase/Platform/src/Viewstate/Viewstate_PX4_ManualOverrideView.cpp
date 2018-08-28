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

#include "..\..\include\Viewstate\Viewstate_PX4_ManualOverrideView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_PowerRelayStateList.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

Viewstate_PX4_ManualOverrideView::Viewstate_PX4_ManualOverrideView(IModelViewstateData * viewstateData, IPowerRelayArray * relayArray) :
	Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW), _viewstateData(viewstateData), _relayArray(relayArray){}

Viewstate_PX4_ManualOverrideView::~Viewstate_PX4_ManualOverrideView(){}

char * Viewstate_PX4_ManualOverrideView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create static viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };	
	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };
	int listStartIndex = 0;

	const SelectableViewstateElementAlias selectedElementAlias = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;

	if (_viewstateData->GetViewstateSelectableElementIndex() < 3)
	{
		_staticVE_BackSymbol.emplace(vs_OutBuffer, outBufferSize);
		_dynamicTextVE_BackLabel.emplace(vs_OutBuffer, outBufferSize);

		if (selectedElementAlias == SELECTABLE_BACK_ELEMENT)
		{
			_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
		}
		else { _staticVE_BackSymbol.emplace(vs_OutBuffer, outBufferSize); }

		listStartIndex = 21;
	}

	Viewstate_Element_Text_PowerRelayStateList powerRelayList(listStartIndex, 1, _viewstateData, _relayArray);
	powerRelayList.emplace(vs_OutBuffer, outBufferSize);

	Viewstate_Element_Text_NewlineTemplate_20x4 newlines(0, 0);
	newlines.emplace(vs_OutBuffer, outBufferSize);

	return vs_OutBuffer;
}
