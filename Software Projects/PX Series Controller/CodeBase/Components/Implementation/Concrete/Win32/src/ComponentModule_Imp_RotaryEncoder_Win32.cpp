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

#include "..\include\ComponentModule_Imp_RotaryEncoder_Win32.h"

#if defined(TARGET_PLAT_WIN32)

ComponentModule_Imp_RotaryEncoder_Win32::ComponentModule_Imp_RotaryEncoder_Win32()
{
	//launch thread to monitor cin for keystrokes
	_enableScan = true;
	thread (&ComponentModule_Imp_RotaryEncoder_Win32::ScanForInput, this).detach();
}

ComponentModule_Imp_RotaryEncoder_Win32::~ComponentModule_Imp_RotaryEncoder_Win32()
{
	_enableScan = false;
}

bool ComponentModule_Imp_RotaryEncoder_Win32::DoSelfDiagnostic_Imp()
{
	return true;
}

void ComponentModule_Imp_RotaryEncoder_Win32::ScanForInput()
{
	while (_enableScan)
	{
		int keypress;
		keypress = _getch();
		switch (keypress)
		{
		case _jogLeftCharVal:
			_flaggedTask = TASKALIAS_NAVIGATION_MENU_MOVE_LEFT;
			break;
		case _jogRightCharVal:
			_flaggedTask = TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT;
			break;
		case _jogPressCharVal:
			_flaggedTask = TASKALIAS_NAVIGATION_MENU_SELECT;
			break;
		default:
			//todo... notify unhandled keypress
			break;
		}
	}
}

TaskAlias ComponentModule_Imp_RotaryEncoder_Win32::GetFlaggedTask()
{
	const TaskAlias flaggedTask = _flaggedTask;
	_flaggedTask = TASKALIAS_NOT_SET; // Clear flagged task
	return flaggedTask;
}

#endif