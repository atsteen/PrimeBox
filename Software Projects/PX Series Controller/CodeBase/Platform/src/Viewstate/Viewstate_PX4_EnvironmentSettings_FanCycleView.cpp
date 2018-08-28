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

#include "..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettings_FanCycleView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_BooleanValue.h"
//#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicState.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ThreeSegmentValue.h"

Viewstate_PX4_EnvironmentSettings_FanCycleView::Viewstate_PX4_EnvironmentSettings_FanCycleView(IModelEnvAirData * airData, IModelViewstateData * viewstateData) :
	Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_AIR_CIRC_VIEW), _airData(airData), _viewstateData(viewstateData){}

Viewstate_PX4_EnvironmentSettings_FanCycleView::~Viewstate_PX4_EnvironmentSettings_FanCycleView(){}

char * Viewstate_PX4_EnvironmentSettings_FanCycleView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	int rowPosStart = 1;
	_clearBuffer(vs_OutBuffer, outBufferSize);
	const SelectableViewstateElementAlias currentSelectedElement = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;
	VElementList _vsDynElements;
	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };

	if (currentSelectedElement == SELECTABLE_BACK_ELEMENT ||
		currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_CIRC_DAY_DUTY_SET_ELEMENT ||
		currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_CIRC_NIGHT_DUTY_SET_ELEMENT ||
		currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_CIRC_CYCLE_DURATION_SET_ELEMENT
		) // Page 1
	{
		Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SELECTABLE_BACK_ELEMENT };

		if (currentSelectedElement == SELECTABLE_BACK_ELEMENT)
		{
			_selectArrowLeft.emplaceOver(vs_OutBuffer, outBufferSize, &_staticVE_BackSymbol);
		}
		else { _staticVE_BackSymbol.emplace(vs_OutBuffer, outBufferSize); }

		Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ rowPosStart, 0, DEFAULT_BACK_TEXT };
		_vsDynElements.AddElement(&_dynamicTextVE_BackLabel);

		Viewstate_Element_Text_DynamicText _dynamicTextVE_DayCircFanCycLabel{ rowPosStart += 21, 0, ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_DAY, SELECTABLE_ENVIRONMENT_FAN_CIRC_DAY_DUTY_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_DayCircFanCycLabel);

		Viewstate_Element_Text_ThreeSegmentValue _DayCircFanCycVal{ rowPosStart + 13, 1, *_airData->GetCirculationFanDutyCycleDay(), Viewstate_String_Generator::percentSymbol };
		_vsDynElements.AddElement(&_DayCircFanCycVal);

		Viewstate_Element_Text_DynamicText _dynamicTextVE_NightCircFanCycLabel{ rowPosStart += 21, 0, ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_NIGHT, SELECTABLE_ENVIRONMENT_FAN_CIRC_NIGHT_DUTY_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_NightCircFanCycLabel);

		Viewstate_Element_Text_ThreeSegmentValue _NightCircFanCycVal{ rowPosStart + 13, 1, *_airData->GetCirculationFanDutyCycleNight(), Viewstate_String_Generator::percentSymbol };
		_vsDynElements.AddElement(&_NightCircFanCycVal);

		Viewstate_Element_Text_DynamicText _dynamicTextVE_CircFanCycDuration{ rowPosStart += 21, 0, ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_DURATION, SELECTABLE_ENVIRONMENT_FAN_CIRC_CYCLE_DURATION_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_CircFanCycDuration);

		Viewstate_Element_Text_ThreeSegmentValue _CircFanCycDurationVal{ rowPosStart + 13, 1, *_airData->GetCirculationFanDutyCycleDuration(), Viewstate_String_Generator::timespanMinuteSymbol };
		_vsDynElements.AddElement(&_CircFanCycDurationVal);

		return RenderElementListText(vs_OutBuffer, outBufferSize, _vsDynElements, currentSelectedElement);
	}
	else if(currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_CIRC_CYCLE_MODE_SET_ELEMENT ||
		currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_EX_DAY_DUTY_SET_ELEMENT ||
		currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_EX_NIGHT_DUTY_SET_ELEMENT ||
		currentSelectedElement == SELECTABLE_ENVIRONMENT_FAN_EX_CYCLE_DURATION_SET_ELEMENT
		) // Page 2
	{
		Viewstate_Element_Text_DynamicText _dynamicTextVE_CircFanCycMode{ rowPosStart, 0, ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_MODE, SELECTABLE_ENVIRONMENT_FAN_CIRC_CYCLE_MODE_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_CircFanCycMode);

		Viewstate_Element_Text_BooleanValue _stateVe_CircFanCycleMode{ rowPosStart + 14, 1, *_airData->GetCirculationFanCycleDefaultState(), ViewstateStringAlias::COMPONENT_TEXT_STATE_ENABLED_ABRV, ViewstateStringAlias::COMPONENT_TEXT_STATE_DISABLED_ABRV};
		_vsDynElements.AddElement(&_stateVe_CircFanCycleMode);

		Viewstate_Element_Text_DynamicText _dynamicTextVE_DayExFanCycLabel{ rowPosStart += 21, 0, ENV_SETTINGS_FAN_EX_CYCLE_TEXT_DAY, SELECTABLE_ENVIRONMENT_FAN_EX_DAY_DUTY_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_DayExFanCycLabel);

		Viewstate_Element_Text_ThreeSegmentValue _DayExFanCycVal{ rowPosStart + 13, 1, *_airData->GetExhaustFanDutyCycleDay(), Viewstate_String_Generator::percentSymbol };
		_vsDynElements.AddElement(&_DayExFanCycVal);

		Viewstate_Element_Text_DynamicText _dynamicTextVE_NightExFanCycLabel{ rowPosStart += 21, 0, ENV_SETTINGS_FAN_EX_CYCLE_TEXT_NIGHT, SELECTABLE_ENVIRONMENT_FAN_EX_NIGHT_DUTY_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_NightExFanCycLabel);

		Viewstate_Element_Text_ThreeSegmentValue _NightExFanCycVal{ rowPosStart + 13, 1, *_airData->GetExhaustFanDutyCycleNight(), Viewstate_String_Generator::percentSymbol };
		_vsDynElements.AddElement(&_NightExFanCycVal);

		Viewstate_Element_Text_DynamicText _dynamicTextVE_ExFanCycDuration{ rowPosStart += 21, 0, ENV_SETTINGS_FAN_EX_CYCLE_TEXT_DURATION, SELECTABLE_ENVIRONMENT_FAN_EX_CYCLE_DURATION_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_ExFanCycDuration);

		Viewstate_Element_Text_ThreeSegmentValue _ExFanCycDurationVal{ rowPosStart + 13, 1, *_airData->GetExhaustFanDutyCycleDuration(), Viewstate_String_Generator::timespanMinuteSymbol };
		_vsDynElements.AddElement(&_ExFanCycDurationVal);

		return RenderElementListText(vs_OutBuffer, outBufferSize, _vsDynElements, currentSelectedElement);
	}
	else // Page 3
	{
		Viewstate_Element_Text_DynamicText _dynamicTextVE_ExFanCycMode{ rowPosStart, 0, ENV_SETTINGS_FAN_EX_CYCLE_TEXT_MODE, SELECTABLE_ENVIRONMENT_FAN_EX_CYCLE_MODE_SET_ELEMENT };
		_vsDynElements.AddElement(&_dynamicTextVE_ExFanCycMode);

		Viewstate_Element_Text_BooleanValue _stateVe_ExFanCycleMode{ rowPosStart + 14, 1, *_airData->GetExhaustFanCycleDefaultState(), ViewstateStringAlias::COMPONENT_TEXT_STATE_ENABLED_ABRV, ViewstateStringAlias::COMPONENT_TEXT_STATE_DISABLED_ABRV };
		_vsDynElements.AddElement(&_stateVe_ExFanCycleMode);

		return RenderElementListText(vs_OutBuffer, outBufferSize, _vsDynElements, currentSelectedElement);
	}
}

char * Viewstate_PX4_EnvironmentSettings_FanCycleView::RenderElementListText(char * outBuff, const int outBuffSize, VElementList elementList, SelectableViewstateElementAlias selected)
{
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };
	elementList.AddElement(&_ve_LineBreaks);

	Viewstate_Element_Text * v = elementList.GetTop();
	while (v)
	{
		if (v->alias == selected)
		{
			Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };
			_selectArrowRight.emplaceLeft(outBuff, outBuffSize, v);
		}

		v->emplace(outBuff, outBuffSize);
		v = v->nextElement;
	}

	return outBuff;
}
