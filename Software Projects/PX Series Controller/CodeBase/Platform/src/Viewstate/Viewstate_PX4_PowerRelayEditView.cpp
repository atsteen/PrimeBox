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

#include "..\..\include\Viewstate\Viewstate_PX4_PowerRelayEditView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayTypeShortName.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelayGroupShortName.h"
#include "..\..\include\SharedStructure\VElementList.h"

Viewstate_PX4_PowerRelayEditView::Viewstate_PX4_PowerRelayEditView(IModelViewstateData * viewstateData, IPowerRelayArray * relayArray) :
	_viewstateData(viewstateData), _relayArray(relayArray), Viewstate_PX4(VIEWSTATEALIAS_POWER_RELAY_EDIT_VIEW){}

char * Viewstate_PX4_PowerRelayEditView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);
	int selectedRelayIndex = _viewstateData->GetViewstateSelectableElementIndex();
	const ComponentAssociation * currentlySelectedRelayAssociation = _relayArray->GetRelayComponentAssociationByIndex(selectedRelayIndex);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, ViewstateStringAlias::DEFAULT_BACK_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicVE_PromptTitle1{ 22, 0, ViewstateStringAlias::COMPONENT_TEXT_SHORT_OUTLET};
	Viewstate_Element_Text_DynamicText _dynamicVE_PromptTitle2{ 29, 0, ViewstateStringAlias::DEFAULT_CONFIG_TEXT };
	Viewstate_Element_Text_DynamicText _dynamicVE_TypeLabel{ 43, 0, ViewstateStringAlias::COMPONENT_TEXT_TYPE_LABEL, SelectableViewstateElementAlias::SELECTABLE_EDIT_RELAY_TYPE };
	Viewstate_Element_Text_StaticText _staticVe_TypeColon(49, 1, ":");
	Viewstate_Element_Text_RelayTypeShortName _dynamicVE_RelayType(51,1, currentlySelectedRelayAssociation->typeAssociation);
	Viewstate_Element_Text_DynamicText _dynamicVE_GroupLabel{ 64, 0, ViewstateStringAlias::COMPONENT_TEXT_GROUP_LABEL, SelectableViewstateElementAlias::SELECTABLE_EDIT_RELAY_GROUP };
	Viewstate_Element_Text_StaticText _staticVe_GroupColon(70, 1, ":");
	Viewstate_Element_Text_RelayGroupShortName _dynamicVE_RelayGroup(72, 1, currentlySelectedRelayAssociation->groupAssociation);

	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };
	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ 19, 1 };

	//add viewstate elements to element collection
	AddViewstateElement(&_staticVE_BackSymbol);
	AddViewstateElement(&_dynamicTextVE_BackLabel);
	AddViewstateElement(&_dynamicVE_PromptTitle1);
	AddViewstateElement(&_dynamicVE_PromptTitle2);
	AddViewstateElement(&_dynamicVE_TypeLabel);
	AddViewstateElement(&_staticVe_TypeColon);
	AddViewstateElement(&_dynamicVE_RelayType);
	AddViewstateElement(&_dynamicVE_GroupLabel);
	AddViewstateElement(&_staticVe_GroupColon);
	AddViewstateElement(&_dynamicVE_RelayGroup);
	AddViewstateElement(&_ve_LineBreaks);

	Viewstate_Element_Text * v = _vsElements.GetTop();
	const SelectableViewstateElementAlias selectedElementAlias = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;

	while (v)
	{
		v->emplace(vs_OutBuffer, outBufferSize);
		v = v->nextElement;
	}

	switch(selectedElementAlias) {
		case SELECTABLE_EDIT_RELAY_TYPE:
			_selectArrowRight.emplaceLeft(vs_OutBuffer, outBufferSize, &_dynamicVE_TypeLabel);
			break;
		case SELECTABLE_EDIT_RELAY_GROUP:
			_selectArrowRight.emplaceLeft(vs_OutBuffer, outBufferSize, &_dynamicVE_GroupLabel);
			break;
		default :
			_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
			break;
	};

	return vs_OutBuffer;
}
