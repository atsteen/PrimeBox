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
#include "..\..\..\ComponentModule_Imp_RTC.h"
#include "..\..\..\..\..\Platform\include\SharedStructure\TimeSignature.h"

#if defined(TARGET_PLAT_WIN32)

#include <ctime>

class ComponentModule_Imp_RTC_Win32 :
	public ComponentModule_Imp_RTC
{
public:
	ComponentModule_Imp_RTC_Win32();
	virtual ~ComponentModule_Imp_RTC_Win32() override;

	// Inherited via ComponentModule_Imp_RTC
	virtual bool DoSelfDiagnostic_Imp() override;
	virtual void GetCurrentSystemTime(TimeSignature&) override;
};

#endif