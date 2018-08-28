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

#include "..\..\include\ComponentModule_Imp_Factory\ComponentModuleImp_Factory_PX4_ATMega.h"

#if defined(TARGET_PLAT_AVR)

ComponentModuleImp_Factory_PX4_ATMega::ComponentModuleImp_Factory_PX4_ATMega(){}

ComponentModuleImp_Factory_PX4_ATMega::~ComponentModuleImp_Factory_PX4_ATMega(){}

ComponentModule_Imp_ASCIIDisplay * ComponentModuleImp_Factory_PX4_ATMega::Make_ASCIIDisplay()
{
	return new ComponentModule_Imp_ASCIIDisplay_ATMega_Direct();
}

ComponentModule_Imp_RTC * ComponentModuleImp_Factory_PX4_ATMega::Make_RTC()
{
	return new ComponentModule_Imp_RTC_ATMega();
}

ComponentModule_Imp_CombinedTempHumSensor * ComponentModuleImp_Factory_PX4_ATMega::Make_CombinedAirSensor()
{
	return new ComponentModule_Imp_CombinedTempHumSensor_HTU21DF();
}

ComponentModule_Imp_PowerRelay * ComponentModuleImp_Factory_PX4_ATMega::Make_PowerRelay_Pump()
{
	return new ComponentModule_Imp_PowerRelay_ATMega(PowerRelay_Trigger_Pin_Pump);
}

ComponentModule_Imp_PowerRelay * ComponentModuleImp_Factory_PX4_ATMega::Make_PowerRelay_Fan()
{
	return new ComponentModule_Imp_PowerRelay_ATMega(PowerRelay_Trigger_Pin_Fan);
}

ComponentModule_Imp_PowerRelay * ComponentModuleImp_Factory_PX4_ATMega::Make_PowerRelay_LightA()
{
	return new ComponentModule_Imp_PowerRelay_ATMega(PowerRelay_Trigger_Pin_LightA);
}

ComponentModule_Imp_PowerRelay * ComponentModuleImp_Factory_PX4_ATMega::Make_PowerRelay_LightB()
{
	return new ComponentModule_Imp_PowerRelay_ATMega(PowerRelay_Trigger_Pin_LightB);
}

ComponentModule_Imp_RotaryEncoder * ComponentModuleImp_Factory_PX4_ATMega::Make_Control_RotaryEncoder()
{
	return new ComponentModule_Imp_RotaryEncoder_ATMega();
}

ComponentModule_Imp_DataLogger * ComponentModuleImp_Factory_PX4_ATMega::Make_DataLogger()
{
	return new ComponentModule_Imp_DataLogger_ATMega();
}

ComponentModule_Imp_Buzzer * ComponentModuleImp_Factory_PX4_ATMega::Make_Buzzer()
{
	return new ComponentModule_Imp_Buzzer_ATMega();
}

#endif