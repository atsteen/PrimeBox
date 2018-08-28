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

#include "..\..\..\..\Configurations\PX4_Config.h"
#include "..\include\ComponentModule_CombinedTempHumSensor_Standard.h"
#include <stdio.h>

ComponentModule_CombinedTempHumSensor_Standard::ComponentModule_CombinedTempHumSensor_Standard(ComponentModule_Imp_CombinedTempHumSensor* imp) : ComponentModule_CombinedTempHumSensor(imp){}

ComponentModule_CombinedTempHumSensor_Standard::~ComponentModule_CombinedTempHumSensor_Standard(){}

bool ComponentModule_CombinedTempHumSensor_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}

const char * ComponentModule_CombinedTempHumSensor_Standard::GetTempRoundedTextFahrenheit()
{
	char buff[10];
	
	#if defined(TARGET_PLAT_WIN32)
		_itoa_s((int)GetTempFahrenheit(), buff, 10);
	#else
		itoa(GetTempFahrenheit(), buff, 10);
	#endif

	for (int i = 0; i < 3; i++)
	{
		_tempText[i] = buff[i];
	}

	//todo... add padding for small numbers

	_tempText[3] = '\0';
	return _tempText;
}

const char * ComponentModule_CombinedTempHumSensor_Standard::GetTempRoundedTextCelsius()
{
	char buff[10];

	#if defined(TARGET_PLAT_WIN32)
		_itoa_s((int)GetTempCelsius(), buff, 10);
	#else
		itoa(GetTempCelsius(), buff, 10);
	#endif	

	for (int i = 0; i < 3; i++)
	{
		if (buff[i] == 0) { _tempText[i] = '\0'; }
		else { _tempText[i] = buff[i]; }
	}

	_tempText[3] = '\0';
	return _tempText;
}

const double ComponentModule_CombinedTempHumSensor_Standard::GetTempFahrenheit()
{
	return (GetTempCelsius()*(1.8)) + 32;
}

const double ComponentModule_CombinedTempHumSensor_Standard::GetTempCelsius()
{
	float temperatureC = _imp->GetCurrentAirTemp();
	if (temperatureC < -73) { return -73; } //min temp limited to three chars ("-99")
	if (temperatureC > 537) { return 537; } //max temp limited to three chars ("999")
	else { return temperatureC; }
}

const char * ComponentModule_CombinedTempHumSensor_Standard::GetRelativeHumidityText()
{
	char buff[10];

	#if defined(TARGET_PLAT_WIN32)
		_itoa_s((int)GetRelativeHumidity(), buff, 10);
	#else
		itoa(GetRelativeHumidity(), buff, 10);
	#endif	

	for (int i = 0; i < 2; i++)
	{
		_relHumText[i] = buff[i];
	}

	//todo... add padding for small numbers

	_relHumText[2] = '\0';
	return _relHumText;
}

const float ComponentModule_CombinedTempHumSensor_Standard::GetRelativeHumidity()
{
	float relativeHumidity = _imp->GetCurrentRelativeHumidity();
	if (relativeHumidity > 99) { relativeHumidity = 99; } //max relHum limited to 99%
	if (relativeHumidity < 1) { relativeHumidity = 1; } //min relHum limited to 1%
	return relativeHumidity;
}
