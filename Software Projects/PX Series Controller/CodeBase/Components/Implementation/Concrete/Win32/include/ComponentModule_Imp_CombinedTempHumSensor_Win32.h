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
#include "..\..\..\..\..\Configurations\PX4_Config.h"
#include "..\..\..\ComponentModule_Imp_CombinedTempHumSensor.h"

#if defined(TARGET_PLAT_WIN32)

class ComponentModule_Imp_CombinedTempHumSensor_Win32 :
	public ComponentModule_Imp_CombinedTempHumSensor
{
public:
	ComponentModule_Imp_CombinedTempHumSensor_Win32();
	virtual ~ComponentModule_Imp_CombinedTempHumSensor_Win32() override;

	// Inherited via ComponentModule_Imp_CombinedTempHumSensor
	virtual bool DoSelfDiagnostic_Imp() override;

	// Inherited via ComponentModule_Imp_CombinedTempHumSensor
	virtual const float GetCurrentAirTemp() override;
	virtual const float GetCurrentRelativeHumidity() override;

private:

	// Win32 component probe values assigned for simplicity
	const float _temp = 15.15F;
	const float _relH = 42.12F;
};

#endif