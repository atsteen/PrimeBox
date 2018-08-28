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
#include "..\..\include\PreProcDirectives.h"
#include "..\..\include\ComponentModule_imp\ComponentModule_Imp_CombinedTempHumSensor.h"

#if defined(TARGET_PLAT_AVR)

#include "..\..\.\pb\include\libraries\Adafruit_HTU21DF\Adafruit_HTU21DF.h"

class ComponentModule_Imp_CombinedTempHumSensor_HTU21DF :
	public ComponentModule_Imp_CombinedTempHumSensor
{
public:
	ComponentModule_Imp_CombinedTempHumSensor_HTU21DF();
	virtual ~ComponentModule_Imp_CombinedTempHumSensor_HTU21DF() override;

	// Inherited via ComponentModule_Imp_CombinedTempHumSensor
	virtual bool DoSelfDiagnostic_Imp() override;

	// Inherited via ComponentModule_Imp_CombinedTempHumSensor
	virtual const float GetCurrentAirTemp() override;
	virtual const float GetCurrentRelativeHumidity() override;

protected:
	Adafruit_HTU21DF htu;
};

#endif 