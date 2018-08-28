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

#pragma once
#include "..\..\Components\Abstraction\IComponentModule.h"
#include "..\..\Components\Implementation\ComponentModule_Imp_CombinedTempHumSensor.h"

class ComponentModule_CombinedTempHumSensor :
	public IComponentModule
{
public:
	ComponentModule_CombinedTempHumSensor(ComponentModule_Imp_CombinedTempHumSensor *imp) : _imp(imp) {}
	virtual ~ComponentModule_CombinedTempHumSensor() override { delete _imp; }

	virtual const char * GetTempRoundedTextFahrenheit() = 0;
	virtual const char * GetTempRoundedTextCelsius() = 0;
	virtual const double GetTempFahrenheit() = 0;
	virtual const double GetTempCelsius() = 0;
	virtual const char * GetRelativeHumidityText() = 0;
	virtual const float GetRelativeHumidity() = 0;

protected:
	ComponentModule_Imp_CombinedTempHumSensor *_imp;
};