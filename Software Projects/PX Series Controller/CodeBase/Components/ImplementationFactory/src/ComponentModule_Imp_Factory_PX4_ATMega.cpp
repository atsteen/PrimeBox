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

#include "..\include\componentmoduleimp_factory_px4_atmega.h"

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

ComponentModule_Imp_PowerRelay * ComponentModuleImp_Factory_PX4_ATMega::Make_PowerRelay(const PersistentComponentAlias alias)
{
	return new ComponentModule_Imp_PowerRelay_ATMega(getPinAssignmentForComponent(alias));
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

ComponentModule_Imp_NvMemoryManager * ComponentModuleImp_Factory_PX4_ATMega::Make_NvMemoryManager()
{
	return new ComponentModule_Imp_NvMemoryManager_ATMega();
}

const int ComponentModuleImp_Factory_PX4_ATMega::getPinAssignmentForComponent(const PersistentComponentAlias alias)
{
	switch(alias) {
		case PersistentComponentAlias::POWER_RELAY_CHANNEL_A :
		return POWER_RELAY_PIN_1;
		break;

		case PersistentComponentAlias::POWER_RELAY_CHANNEL_B :
		return POWER_RELAY_PIN_2;
		break;

		case PersistentComponentAlias::POWER_RELAY_CHANNEL_C :
		return POWER_RELAY_PIN_3;
		break;

		case PersistentComponentAlias::POWER_RELAY_CHANNEL_D :
		return POWER_RELAY_PIN_4;
		break;

		default :
		return -1;
	}
}

#endif