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

#include "..\..\ImplementationFactory\include\ComponentModuleImp_Factory_PX4_Win32.h"

#if defined(TARGET_PLAT_WIN32)

ComponentModuleImp_Factory_PX4_Win32::ComponentModuleImp_Factory_PX4_Win32(){}

ComponentModuleImp_Factory_PX4_Win32::~ComponentModuleImp_Factory_PX4_Win32(){}

ComponentModule_Imp_ASCIIDisplay* ComponentModuleImp_Factory_PX4_Win32::Make_ASCIIDisplay()
{
	return new ComponentModule_Imp_ASCIIDisplay_Win32();
}

ComponentModule_Imp_RTC* ComponentModuleImp_Factory_PX4_Win32::Make_RTC()
{
	return new ComponentModule_Imp_RTC_Win32();
}

ComponentModule_Imp_CombinedTempHumSensor * ComponentModuleImp_Factory_PX4_Win32::Make_CombinedAirSensor()
{
	return new ComponentModule_Imp_CombinedTempHumSensor_Win32();
}

ComponentModule_Imp_PowerRelay * ComponentModuleImp_Factory_PX4_Win32::Make_PowerRelay(const PersistentComponentAlias alias)
{
	// PersistentComponentAlias not required in emulated implementation 
	return new ComponentModule_Imp_PowerRelay_Win32();
}

ComponentModule_Imp_RotaryEncoder * ComponentModuleImp_Factory_PX4_Win32::Make_Control_RotaryEncoder()
{
	return new ComponentModule_Imp_RotaryEncoder_Win32();
}

ComponentModule_Imp_DataLogger * ComponentModuleImp_Factory_PX4_Win32::Make_DataLogger()
{
	return new ComponentModule_Imp_DataLogger_Win32();
}

ComponentModule_Imp_Buzzer * ComponentModuleImp_Factory_PX4_Win32::Make_Buzzer()
{
	return new ComponentModule_Imp_Buzzer_Win32();
}

ComponentModule_Imp_NvMemoryManager * ComponentModuleImp_Factory_PX4_Win32::Make_NvMemoryManager()
{
	return new ComponentModule_Imp_NvMemoryManager_Win32();
}

#endif