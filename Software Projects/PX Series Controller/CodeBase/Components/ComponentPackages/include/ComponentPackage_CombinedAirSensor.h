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

#include "..\..\ImplementationFactory\include\ComponentModuleImp_Factory_PX4.h"
#include "..\..\Abstraction\Refined\include\ComponentModule_CombinedTempHumSensor_Standard.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IAirSensor.h"

class ComponentPackage_CombinedAirSensor : public IAirSensor
{
public:
	ComponentPackage_CombinedAirSensor(ComponentModuleImp_Factory_PX4* componentImpFactory);
	~ComponentPackage_CombinedAirSensor();

	// Inherited via IAirSensor
	virtual const double CurrentTemperatureFahrenheit() override;
	virtual const char * CurrentTemperatureFahrenheitText() override;
	virtual const float CurrentRelativeHumidity() override;	
	virtual const char * CurrentRelativeHumidityText() override;

private:
	ComponentModule_CombinedTempHumSensor_Standard * _airSensor;
};