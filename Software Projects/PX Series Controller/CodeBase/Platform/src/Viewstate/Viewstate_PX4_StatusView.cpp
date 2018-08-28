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

#include "..\..\include\Viewstate\Viewstate_PX4_StatusView.h"
#include "..\..\include\SharedStructure\SelectableNavigationMap.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_AirTemperature.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_RelativeHumidity.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SystemMode.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SystemTime.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_EventCollection_3.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_StaticText.h"
#include "..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"
#include "..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"
//#include <string.h>

Viewstate_PX4_StatusView::Viewstate_PX4_StatusView(IAirSensor * airSensor, IModelEnvAirData * airData, IModelSystemData * systemData, EventLog_Item_Collection * eventItems)
	: Viewstate_PX4(ViewstateAlias::VIEWSTATEALIAS_STATUS_VIEW), _airSensor(airSensor), _airData(airData), _systemData(systemData), _eventItems(eventItems){}
Viewstate_PX4_StatusView::~Viewstate_PX4_StatusView(){}

char * Viewstate_PX4_StatusView::RenderText(char * vs_OutBuffer, const int outBufferSize)
{
	_clearBuffer(vs_OutBuffer, outBufferSize);

	//create viewstate elements { start_index, inbrication level }
	Viewstate_Element_Text_AirTemperature _ve_AirTemp{ 1, 2, _airSensor };
	Viewstate_Element_Text_RelativeHumidity _ve_RelHum{ 5, 2, _airSensor };
	Viewstate_Element_Text_SystemMode _ve_SysMode{ 12 , 2, _systemData };
	Viewstate_Element_Text_SystemTime _ve_SysTime{ 15, 2, _systemData };
	Viewstate_Element_Text_EventCollection_3 _ve_ElementCol{ 21 , 2, _eventItems };
	Viewstate_Element_Text_NewlineTemplate_20x4 _ve_LineBreaks{ 0 , 4 };

	Viewstate_Element_Text_StaticText _ve_AirTempSymb{ 0, 0, Viewstate_String_Generator::airTemperatureSymbol };
	Viewstate_Element_Text_StaticText _ve_RelHumSymb{ 4, 0, Viewstate_String_Generator::relativeHumiditySymbol };
	Viewstate_Element_Text_StaticText _ve_MiniPercentSymb{ 7, 0, Viewstate_String_Generator::miniPercentSymbol };
	Viewstate_Element_Text_StaticText _ve_SysModeSymb{ 11, 0, Viewstate_String_Generator::systemModeSymbol };

	VElementList _vsDynElements;
	_vsDynElements.AddElement(&_ve_AirTempSymb);
	_vsDynElements.AddElement(&_ve_AirTemp);
	_vsDynElements.AddElement(&_ve_RelHumSymb);
	_vsDynElements.AddElement(&_ve_RelHum);
	_vsDynElements.AddElement(&_ve_SysModeSymb);
	_vsDynElements.AddElement(&_ve_SysMode);
	_vsDynElements.AddElement(&_ve_SysTime);
	_vsDynElements.AddElement(&_ve_MiniPercentSymb);
	_vsDynElements.AddElement(&_ve_ElementCol);
	_vsDynElements.AddElement(&_ve_LineBreaks);

	Viewstate_Element_Text * v = _vsDynElements.GetTop();

	while (v)
	{
		v->emplace(vs_OutBuffer, outBufferSize);
		v = v->nextElement;
	}

	return vs_OutBuffer;
}