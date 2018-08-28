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
#include "..\..\..\..\..\Configurations\PX4_Config.h"
#include "..\..\..\ComponentModule_Imp_RotaryEncoder.h"

#if defined(TARGET_PLAT_WIN32)

#include <iostream>
#include <thread>
#include "conio.h"

class ComponentModule_Imp_RotaryEncoder_Win32 :
	public ComponentModule_Imp_RotaryEncoder
{
public:
	ComponentModule_Imp_RotaryEncoder_Win32();
	virtual ~ComponentModule_Imp_RotaryEncoder_Win32() override;

	// Inherited via ComponentModule_Imp
	virtual bool DoSelfDiagnostic_Imp() override;

protected:
	bool _enableScan = false;	
	TaskAlias _flaggedTask = TASKALIAS_NOT_SET;
	static constexpr int _jogLeftCharVal = 75;
	static constexpr int _jogRightCharVal = 77;
	static constexpr int _jogPressCharVal = 80;

	void ScanForInput();

	// Inherited via ComponentModule_Imp_RotaryEncoder
	virtual TaskAlias GetFlaggedTask() override;
};

#endif