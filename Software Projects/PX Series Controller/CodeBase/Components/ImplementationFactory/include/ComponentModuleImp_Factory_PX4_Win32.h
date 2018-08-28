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

#if defined(TARGET_PLAT_WIN32)

#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_ASCIIDisplay_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_RTC_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_CombinedTempHumSensor_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_PowerRelay_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_RotaryEncoder_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_DataLogger_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_Buzzer_Win32.h"
#include "..\..\Implementation\Concrete\Win32\include\ComponentModule_Imp_NvMemoryManager_Win32.h"

class ComponentModuleImp_Factory_PX4_Win32 :
	public ComponentModuleImp_Factory_PX4
{
public:
	ComponentModuleImp_Factory_PX4_Win32();
	virtual ~ComponentModuleImp_Factory_PX4_Win32() override;

	// Inherited via ComponentModuleImp_Factory_PX4
	virtual ComponentModule_Imp_ASCIIDisplay* Make_ASCIIDisplay() override;
	virtual ComponentModule_Imp_RTC* Make_RTC() override;
	virtual ComponentModule_Imp_CombinedTempHumSensor* Make_CombinedAirSensor() override;
	virtual ComponentModule_Imp_PowerRelay * Make_PowerRelay(const PersistentComponentAlias) override;
	virtual ComponentModule_Imp_RotaryEncoder* Make_Control_RotaryEncoder() override;
	virtual ComponentModule_Imp_DataLogger* Make_DataLogger() override;
	virtual ComponentModule_Imp_Buzzer* Make_Buzzer() override;
	virtual ComponentModule_Imp_NvMemoryManager* Make_NvMemoryManager() override;
};

#endif

