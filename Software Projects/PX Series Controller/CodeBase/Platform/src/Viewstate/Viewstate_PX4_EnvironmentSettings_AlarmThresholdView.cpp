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

#include "..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettings_AlarmThresholdView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicState.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ThreeSegmentValue.h"

Viewstate_PX4_EnvironmentSettings_AlarmThresholdView::Viewstate_PX4_EnvironmentSettings_AlarmThresholdView(IModelEnvAirData * airData, IModelSystemData * systemData, IModelViewstateData * viewstateData) :
	Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_ALARM_THRESHOLDS_VIEW),
	_airData(airData),
	_systemData(systemData),
	_viewstateData(viewstateData){}

Viewstate_PX4_EnvironmentSettings_AlarmThresholdView::~Viewstate_PX4_EnvironmentSettings_AlarmThresholdView(){}

char * Viewstate_PX4_EnvironmentSettings_AlarmThresholdView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };

	Viewstate_Element_Text_DynamicText _dynamicTextVE_OverTempAlarmLabel{ 22, 0, ENV_SETTINGS_ALARM_THRESHOLD_TEXT_OVER_TEMP, SELECTABLE_ENVIRONMENT_OVERTEMP_ALARM_SET_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_OverRhAlarmLabel{ 43, 0, ENV_SETTINGS_ALARM_THRESHOLD_TEXT_OVER_RH, SELECTABLE_ENVIRONMENT_OVERHUM_ALARM_SET_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_LogFullAlarmLabel{ 64, 0, ENV_SETTINGS_ALARM_THRESHOLD_TEXT_LOGFULL, SELECTABLE_ENVIRONMENT_LOGFULL_ALARM_SET_ELEMENT };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	//ComponentState viewstate elements require 'pointer-to-member function' for remote state retrieval
	//For a good explanation of this design see https://web.archive.org/web/20120723071248/http://www.dulcineatech.com/tips/code/c++/member-pointers.html
	Viewstate_Element_Text_ThreeSegmentValue _overTempAlarmVal{ 35, 1, *_airData->GetAlarmThresholdOverTempF(), Viewstate_String_Generator::degreeSymbol };
	Viewstate_Element_Text_ThreeSegmentValue _overRhAlarmVal{ 56, 1, *_airData->GetAlarmThresholdOverRH(), Viewstate_String_Generator::percentSymbol };
	Viewstate_Element_Text_DynamicState _stateVe_logFullAlarmDefaultState{ 78, 1, *_systemData->GetLogAlarmDefaultState() };

	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };

	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_dynamicTextVE_BackLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_OverTempAlarmLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_OverRhAlarmLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_LogFullAlarmLabel);
	_vsDynElements.AddElement(&_ve_LineBreaks);
	_vsDynElements.AddElement(&_overTempAlarmVal);
	_vsDynElements.AddElement(&_overRhAlarmVal);
	_vsDynElements.AddElement(&_stateVe_logFullAlarmDefaultState);

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
