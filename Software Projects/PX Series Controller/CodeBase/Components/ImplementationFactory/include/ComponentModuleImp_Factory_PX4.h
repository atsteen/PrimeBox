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
#include "..\..\..\Platform\include\SharedStructure\PersistentDataAlias.h"
#include "..\..\Implementation\ComponentModule_Imp_ASCIIDisplay.h"
#include "..\..\Implementation\ComponentModule_Imp_RTC.h"
#include "..\..\Implementation\ComponentModule_Imp_CombinedTempHumSensor.h"
#include "..\..\Implementation\ComponentModule_Imp_PowerRelay.h"
#include "..\..\Implementation\ComponentModule_Imp_RotaryEncoder.h"
#include "..\..\Implementation\ComponentModule_Imp_DataLogger.h"
#include "..\..\Implementation\ComponentModule_Imp_Buzzer.h"
#include "..\..\Implementation\ComponentModule_Imp_NvMemoryManager.h"

class ComponentModuleImp_Factory_PX4
{
public:
	ComponentModuleImp_Factory_PX4(){}
	virtual ~ComponentModuleImp_Factory_PX4() = 0;
	virtual ComponentModule_Imp_ASCIIDisplay* Make_ASCIIDisplay() = 0;
	virtual ComponentModule_Imp_RTC* Make_RTC() = 0;
	virtual ComponentModule_Imp_CombinedTempHumSensor* Make_CombinedAirSensor() = 0;
	virtual ComponentModule_Imp_PowerRelay* Make_PowerRelay(const PersistentComponentAlias) = 0;
	virtual ComponentModule_Imp_RotaryEncoder* Make_Control_RotaryEncoder() = 0;
	virtual ComponentModule_Imp_DataLogger* Make_DataLogger() = 0;
	virtual ComponentModule_Imp_Buzzer* Make_Buzzer() = 0;
	virtual ComponentModule_Imp_NvMemoryManager* Make_NvMemoryManager() = 0;
};

inline ComponentModuleImp_Factory_PX4::~ComponentModuleImp_Factory_PX4() {};