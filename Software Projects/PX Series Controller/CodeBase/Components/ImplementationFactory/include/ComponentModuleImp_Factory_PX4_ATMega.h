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
#include "..\..\..\Configurations\PX4_Config.h"
#include "..\include\ComponentModuleImp_Factory_PX4.h"

#if defined(TARGET_PLAT_AVR)

#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_ASCIIDisplay_HD44780_Parallel_ATMega.h"
#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_RTC_ATMega.h"
#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_CombinedTempHumSensor_HTU21DF.h"
#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_PowerRelay_ATMega.h"
#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_RotaryEncoder_ATMega.h"
#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_DataLogger_ATMega.h"
#include "..\..\Implementation\Concrete\ATmega\include\ComponentModule_Imp_Buzzer_ATMega.h"

class ComponentModuleImp_Factory_PX4_ATMega :
	public ComponentModuleImp_Factory_PX4
{
public:
	ComponentModuleImp_Factory_PX4_ATMega();
	virtual ~ComponentModuleImp_Factory_PX4_ATMega() override; 

	//TODO Replace with PersistentComponentAlias->pin mapper
	//const int PowerRelay_Trigger_Pin_Pump = 4;
	//const int PowerRelay_Trigger_Pin_Fan = 5;
	//const int PowerRelay_Trigger_Pin_LightA = 6;
	//const int PowerRelay_Trigger_Pin_LightB = 7;

	// Inherited via ComponentModuleImp_Factory_PX4
	virtual ComponentModule_Imp_ASCIIDisplay* Make_ASCIIDisplay() override;
	virtual ComponentModule_Imp_RTC* Make_RTC() override;
	virtual ComponentModule_Imp_CombinedTempHumSensor* Make_CombinedAirSensor() override;
	virtual ComponentModule_Imp_PowerRelay * Make_PowerRelay_Pump() override;
	virtual ComponentModule_Imp_PowerRelay * Make_PowerRelay_Fan() override;
	virtual ComponentModule_Imp_PowerRelay * Make_PowerRelay_LightA() override;
	virtual ComponentModule_Imp_PowerRelay * Make_PowerRelay_LightB() override;
	virtual ComponentModule_Imp_RotaryEncoder * Make_Control_RotaryEncoder() override;
	virtual ComponentModule_Imp_DataLogger * Make_DataLogger() override;
	virtual ComponentModule_Imp_Buzzer* Make_Buzzer() override;
};

#endif

