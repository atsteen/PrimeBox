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

#include "..\include\ComponentModule_Imp_ASCIIDisplay_Win32.h"

#if defined(TARGET_PLAT_WIN32)

#include <iostream>

ComponentModule_Imp_ASCIIDisplay_Win32::ComponentModule_Imp_ASCIIDisplay_Win32()
{
	SetConsoleTextAttribute(_hConsole, 0x07); // Init to default white foreground

	/* Save current attributes */
	GetConsoleScreenBufferInfo(_hConsole, &_consoleInfo);
	_saved_attributes = _consoleInfo.wAttributes;
}

ComponentModule_Imp_ASCIIDisplay_Win32::~ComponentModule_Imp_ASCIIDisplay_Win32(){}

bool ComponentModule_Imp_ASCIIDisplay_Win32::DoSelfDiagnostic_Imp()
{
	return cout.good();
}

void ComponentModule_Imp_ASCIIDisplay_Win32::Enable_Imp()
{
	_isEnabled = true;
	SetConsoleTextAttribute(_hConsole, FOREGROUND_GREEN);
	UpdateDisplay_Imp(strLastUpdateText.c_str());
}

void ComponentModule_Imp_ASCIIDisplay_Win32::Disable_Imp()
{
	_isEnabled = false;
	SetConsoleTextAttribute(_hConsole, _saved_attributes);
	UpdateDisplay_Imp(strLastUpdateText.c_str());
}

void ComponentModule_Imp_ASCIIDisplay_Win32::UpdateDisplay_Imp(const char * cstr)
{
	strLastUpdateText = cstr;
	std::system("cls");
	std::cout << cstr;
}

#endif
