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
#include "..\..\..\ComponentModule_Imp_ASCIIDisplay.h"

#if defined(TARGET_PLAT_WIN32)

#include <windows.h>
#include <stdio.h>
#include <string>

class ComponentModule_Imp_ASCIIDisplay_Win32 :
	public ComponentModule_Imp_ASCIIDisplay
{
public:
	ComponentModule_Imp_ASCIIDisplay_Win32();
	virtual ~ComponentModule_Imp_ASCIIDisplay_Win32() override;

	// Inherited via ComponentModule_Imp_ASCIIDisplay
	virtual bool DoSelfDiagnostic_Imp() override;
	virtual void Enable_Imp() override;
	virtual void Disable_Imp() override;
	virtual void UpdateDisplay_Imp(const char*) override;

protected:
	bool _isEnabled = false;
	std::string strLastUpdateText;
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO _consoleInfo;
	WORD _saved_attributes;
};

#endif

