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
#include "..\..\ComponentModule_CombinedTempHumSensor.h"
#include "..\..\..\..\Platform\include\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include <stdlib.h>

class ComponentModule_CombinedTempHumSensor_Standard :
	public ComponentModule_CombinedTempHumSensor
{
public:
	ComponentModule_CombinedTempHumSensor_Standard(ComponentModule_Imp_CombinedTempHumSensor *imp);
	virtual ~ComponentModule_CombinedTempHumSensor_Standard() override;

	// Inherited via ComponentModule
	virtual bool DoSelfDiagnostic() override;

	// Inherited via ComponentModule_CombinedTempHumSensor
	virtual const char * GetTempRoundedTextFahrenheit() override;
	virtual const char * GetTempRoundedTextCelsius() override;
	virtual const double GetTempFahrenheit() override;
	virtual const double GetTempCelsius() override;
	virtual const char * GetRelativeHumidityText() override;
	virtual const float GetRelativeHumidity() override;

protected:
	char _tempText[4] = { *Viewstate_String_Generator::defaultAirTempText };
	char _relHumText[3] = { *Viewstate_String_Generator::defaultRelHumText };
};