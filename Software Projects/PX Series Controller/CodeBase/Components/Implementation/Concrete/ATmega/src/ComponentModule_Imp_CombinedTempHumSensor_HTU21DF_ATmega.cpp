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

#include "..\include\componentmodule_imp_combinedtemphumsensor_htu21df_atmega.h"

#if defined(TARGET_PLAT_AVR)

ComponentModule_Imp_CombinedTempHumSensor_HTU21DF::ComponentModule_Imp_CombinedTempHumSensor_HTU21DF()
{
	htu = Adafruit_HTU21DF();
	htu.begin();
}

ComponentModule_Imp_CombinedTempHumSensor_HTU21DF::~ComponentModule_Imp_CombinedTempHumSensor_HTU21DF(){}

bool ComponentModule_Imp_CombinedTempHumSensor_HTU21DF::DoSelfDiagnostic_Imp()
{
	return htu.begin();
}

const float ComponentModule_Imp_CombinedTempHumSensor_HTU21DF::GetCurrentAirTemp()
{
	return htu.readTemperature();
}

const float ComponentModule_Imp_CombinedTempHumSensor_HTU21DF::GetCurrentRelativeHumidity()
{
	return htu.readHumidity();
}

#endif