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
#include "IComponentModuleGroup.h"
#include "..\..\include\SharedStructure\SharedInterface\IHasNavigationTones.h"
#include "..\..\include\SharedStructure\SharedInterface\IHasPostTones.h"
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_ASCIIDisplay_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_RTC_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_CombinedTempHumSensor_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_PowerRelay_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_RotaryEncoder_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_Buzzer_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_NvMemoryManager_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_DataLogger_Standard.h"

class ComponentModuleGroup_PX4 : public IHasNavigationTones, public IHasPostTones
{
public:
	ComponentModuleGroup_PX4();
	~ComponentModuleGroup_PX4();

	//ComponentModule_RTC_Standard * RTC();
	//ComponentModule_DataLogger_Standard * DataLogger();

	//ComponentModule_ASCIIDisplay_Standard * Display();
	//ComponentModule_RotaryEncoder_Standard * RotaryEncoder();

	//ComponentModule_CombinedTempHumSensor_Standard * AirSensor();


	//ComponentModule_Buzzer_Standard * Buzzer();

	ComponentModule_NvMemoryManager_Standard * NvMemoryManager();
	

	ComponentModule_PowerRelay_Standard * PumpRelay();
	ComponentModule_PowerRelay_Standard * FanRelay();
	ComponentModule_PowerRelay_Standard * LightRelayA();
	ComponentModule_PowerRelay_Standard * LightRelayB();

private:
	static ComponentModule_RTC_Standard * _realTimeClock;
	static ComponentModule_ASCIIDisplay_Standard * _ASCIIDisplay;
	static ComponentModule_CombinedTempHumSensor_Standard * _CombinedTempHumSensor;
	static ComponentModule_PowerRelay_Standard * _powerRelay_Pump;
	static ComponentModule_PowerRelay_Standard * _powerRelay_Fan;
	static ComponentModule_PowerRelay_Standard * _powerRelay_LightA;
	static ComponentModule_PowerRelay_Standard * _powerRelay_LightB;
	static ComponentModule_RotaryEncoder_Standard * _rotaryEncoder;
	static ComponentModule_Buzzer_Standard * _buzzer;
	static ComponentModule_NvMemoryManager_Standard * _nvMemoryManager;
	static ComponentModule_DataLogger_Standard * _dataLogger;
	static ComponentModuleImp_Factory_PX4 * _componentImpFactory;
};