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

#include "..\include\ComponentModule_Imp_PowerRelay_Win32.h"

#if defined(TARGET_PLAT_WIN32)

ComponentModule_Imp_PowerRelay_Win32::ComponentModule_Imp_PowerRelay_Win32(){}

ComponentModule_Imp_PowerRelay_Win32::~ComponentModule_Imp_PowerRelay_Win32(){}

bool ComponentModule_Imp_PowerRelay_Win32::DoSelfDiagnostic_Imp()
{
	return true;
}

const bool ComponentModule_Imp_PowerRelay_Win32::GetState()
{
	return _relayState;
}

void ComponentModule_Imp_PowerRelay_Win32::SetState(const bool state)
{
	_relayState = state;
}

#endif