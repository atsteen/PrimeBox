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

#include "..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettings_LightCycleView.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowRight.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicState.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_TimeState.h"

Viewstate_PX4_EnvironmentSettings_LightCycleView::Viewstate_PX4_EnvironmentSettings_LightCycleView(IModelEnvLightData * lightData, IModelViewstateData * viewstateData) :
	Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW),
	_lightData(lightData), _viewstateData(viewstateData) {}

Viewstate_PX4_EnvironmentSettings_LightCycleView::~Viewstate_PX4_EnvironmentSettings_LightCycleView(){}

char * Viewstate_PX4_EnvironmentSettings_LightCycleView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_StaticText _staticVE_BackSymbol{ 0, 1, Viewstate_String_Generator::backSymbol , SELECTABLE_BACK_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_BackLabel{ 1, 0, DEFAULT_BACK_TEXT };

	Viewstate_Element_Text_DynamicText _dynamicTextVE_SetSunriseLabel{ 22, 0, ENV_SETTINGS_LIGHTCYCLE_TEXT_SETSUNRISE, SELECTABLE_ENVIRONMENT_SUNRISE_SET_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_SetSunsetLabel{ 43, 0, ENV_SETTINGS_LIGHTCYCLE_TEXT_SETSUNSET, SELECTABLE_ENVIRONMENT_SUNSET_SET_ELEMENT };
	Viewstate_Element_Text_DynamicText _dynamicTextVE_SetLightCycleModeLabel{ 64, 0, ENV_SETTINGS_LIGHTCYCLE_TEXT_SETLIGHTCYCLEMODE, SELECTABLE_ENVIRONMENT_SUN_CYCLE_SET_ELEMENT };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	//ComponentState viewstate elements require 'pointer-to-member function' for remote state retrieval
	//For a good explanation of this design see https://web.archive.org/web/20120723071248/http://www.dulcineatech.com/tips/code/c++/member-pointers.html
	Viewstate_Element_Text_TimeState _sunriseTimeVe{ 34, 1, *_lightData->GetDefaultSunriseTime() };
	Viewstate_Element_Text_TimeState _sunsetTimeVe{ 55, 1, *_lightData->GetDefaultSunsetTime() };

	Viewstate_Element_Text_DynamicState _stateVe_LightCycleDefault{ 78, 1, *_lightData->GetLightCycleDefaultState() };

	Viewstate_Element_Text_SelectArrowLeft _selectArrowLeft{ -1, 1 };
	Viewstate_Element_Text_SelectArrowRight _selectArrowRight{ -1, 1 };

	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_dynamicTextVE_BackLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_SetSunriseLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_SetSunsetLabel);
	_vsDynElements.AddElement(&_dynamicTextVE_SetLightCycleModeLabel);
	_vsDynElements.AddElement(&_ve_LineBreaks);
	_vsDynElements.AddElement(&_sunriseTimeVe);
	_vsDynElements.AddElement(&_sunsetTimeVe);
	_vsDynElements.AddElement(&_stateVe_LightCycleDefault);

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
