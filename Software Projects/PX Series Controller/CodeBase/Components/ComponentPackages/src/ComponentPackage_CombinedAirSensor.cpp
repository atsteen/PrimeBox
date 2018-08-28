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

#include "..\include\ComponentPackage_UI_PX4.h"
#include "..\include\ComponentPackage_CombinedAirSensor.h"

ComponentPackage_CombinedAirSensor::ComponentPackage_CombinedAirSensor(ComponentModuleImp_Factory_PX4 * componentImpFactory)
{
	_airSensor = new ComponentModule_CombinedTempHumSensor_Standard(componentImpFactory->Make_CombinedAirSensor());
}

ComponentPackage_CombinedAirSensor::~ComponentPackage_CombinedAirSensor()
{
	delete _airSensor;
}

const char * ComponentPackage_CombinedAirSensor::CurrentRelativeHumidityText()
{
	return _airSensor->GetRelativeHumidityText();
}

const double ComponentPackage_CombinedAirSensor::CurrentTemperatureFahrenheit()
{
	return _airSensor->GetTempFahrenheit();
}

const float ComponentPackage_CombinedAirSensor::CurrentRelativeHumidity()
{
	return _airSensor->GetRelativeHumidity();
}

const char * ComponentPackage_CombinedAirSensor::CurrentTemperatureFahrenheitText()
{
	return _airSensor->GetTempRoundedTextFahrenheit();
}
