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

#include "..\..\include\ComponentModuleGroup\ComponentModuleGroup_PX4.h"
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4_Win32.h"

ComponentModule_RTC_Standard * ComponentModuleGroup_PX4::_realTimeClock = nullptr;
ComponentModule_ASCIIDisplay_Standard * ComponentModuleGroup_PX4::_ASCIIDisplay;
ComponentModule_CombinedTempHumSensor_Standard * ComponentModuleGroup_PX4::_CombinedTempHumSensor = nullptr;
ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::_powerRelay_Pump = nullptr;
ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::_powerRelay_Fan = nullptr;
ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::_powerRelay_LightA = nullptr;
ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::_powerRelay_LightB = nullptr;
ComponentModule_RotaryEncoder_Standard * ComponentModuleGroup_PX4::_rotaryEncoder = nullptr;
ComponentModule_Buzzer_Standard * ComponentModuleGroup_PX4::_buzzer = nullptr;
ComponentModule_NvMemoryManager_Standard * ComponentModuleGroup_PX4::_nvMemoryManager = nullptr;
ComponentModule_DataLogger_Standard * ComponentModuleGroup_PX4::_dataLogger = nullptr;

ComponentModuleImp_Factory_PX4 * ComponentModuleGroup_PX4::_componentImpFactory = nullptr;

ComponentModuleGroup_PX4::ComponentModuleGroup_PX4()
{
	if(!_componentImpFactory)
	{
		// Initialize factory
		#if defined(TARGET_PLAT_AVR)
		_componentImpFactory = new ComponentModuleImp_Factory_PX4_ATMega;
		#else
		_componentImpFactory = new ComponentModuleImp_Factory_PX4_Win32;
		#endif
	}

	//force init user input components because they may not be called by the controller
	RotaryEncoder();

	//force init power relay components to restore state
	PumpRelay();
	FanRelay();
	LightRelayA();
	LightRelayB();
}

ComponentModuleGroup_PX4::~ComponentModuleGroup_PX4(){}

ComponentModule_RTC_Standard * ComponentModuleGroup_PX4::RTC()
{
	if (!_realTimeClock) { _realTimeClock = new ComponentModule_RTC_Standard(_componentImpFactory->Make_RTC()); }
	return _realTimeClock;
}

ComponentModule_ASCIIDisplay_Standard * ComponentModuleGroup_PX4::Display()
{
	if (!_ASCIIDisplay) { _ASCIIDisplay = new ComponentModule_ASCIIDisplay_Standard(_componentImpFactory->Make_ASCIIDisplay()); }
	return _ASCIIDisplay;
}

ComponentModule_CombinedTempHumSensor_Standard * ComponentModuleGroup_PX4::AirSensor()
{
	if (!_CombinedTempHumSensor) { _CombinedTempHumSensor = new ComponentModule_CombinedTempHumSensor_Standard(_componentImpFactory->Make_CombinedAirSensor()); }
	return _CombinedTempHumSensor;
}

ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::PumpRelay()
{
	if (!_powerRelay_Pump) { _powerRelay_Pump = new ComponentModule_PowerRelay_Standard(_componentImpFactory->Make_PowerRelay_Pump(), PersistentComponentAlias::POWER_RELAY_CHANNEL_A); }
	return _powerRelay_Pump;
}

ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::FanRelay()
{
	if (!_powerRelay_Fan) { _powerRelay_Fan = new ComponentModule_PowerRelay_Standard(_componentImpFactory->Make_PowerRelay_Fan(), PersistentComponentAlias::POWER_RELAY_CHANNEL_B); }
	return _powerRelay_Fan;
}

ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::LightRelayA()
{
	if (!_powerRelay_LightA) { _powerRelay_LightA = new ComponentModule_PowerRelay_Standard(_componentImpFactory->Make_PowerRelay_LightA(), PersistentComponentAlias::POWER_RELAY_CHANNEL_C); }
	return _powerRelay_LightA;
}

ComponentModule_PowerRelay_Standard * ComponentModuleGroup_PX4::LightRelayB()
{
	if (!_powerRelay_LightB) { _powerRelay_LightB = new ComponentModule_PowerRelay_Standard(_componentImpFactory->Make_PowerRelay_LightB(), PersistentComponentAlias::POWER_RELAY_CHANNEL_D); }
	return _powerRelay_LightB;
}

ComponentModule_RotaryEncoder_Standard * ComponentModuleGroup_PX4::RotaryEncoder()
{
	if (!_rotaryEncoder) { _rotaryEncoder = new ComponentModule_RotaryEncoder_Standard(_componentImpFactory->Make_Control_RotaryEncoder()); }
	return _rotaryEncoder;
}

ComponentModule_Buzzer_Standard * ComponentModuleGroup_PX4::Buzzer()
{
	if (!_buzzer) { _buzzer = new ComponentModule_Buzzer_Standard( _componentImpFactory->Make_Buzzer()); }
	return _buzzer;
}

ComponentModule_NvMemoryManager_Standard * ComponentModuleGroup_PX4::NvMemoryManager()
{
	if (!_nvMemoryManager) { _nvMemoryManager = new ComponentModule_NvMemoryManager_Standard(_componentImpFactory->Make_NvMemoryManager()); }
	return _nvMemoryManager;
}

ComponentModule_DataLogger_Standard * ComponentModuleGroup_PX4::DataLogger()
{
	if (!_dataLogger) { _dataLogger = new ComponentModule_DataLogger_Standard(_componentImpFactory->Make_DataLogger(), this->RTC()); }
	return _dataLogger;
}
