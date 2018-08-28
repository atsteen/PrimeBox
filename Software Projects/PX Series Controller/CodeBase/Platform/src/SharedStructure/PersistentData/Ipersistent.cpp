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

#include "..\..\..\include\SharedStructure\PersistentData\Ipersistent.h"
#include "..\..\..\..\Components\Implementation\Concrete\Win32\include\ComponentModule_Imp_NvMemoryManager_Win32.h"


ComponentModule_NvMemoryManager_PX4 * Ipersistent::_NvMemoryManager = nullptr;
ComponentModule_Imp_NvMemoryManager * Ipersistent::_NvMemoryManager_Imp = nullptr;

Ipersistent::Ipersistent()
{
	if(!_NvMemoryManager_Imp)
	{
		#if defined(TARGET_PLAT_AVR)
		_NvMemoryManager_Imp = new ComponentModule_Imp_NvMemoryManager_ATMega;
		#else
		_NvMemoryManager_Imp = new ComponentModule_Imp_NvMemoryManager_Win32;
		#endif
	}
}

ComponentModule_NvMemoryManager_PX4 * Ipersistent::NvMemoryManager()
{
	if (!_NvMemoryManager) { _NvMemoryManager = new ComponentModule_NvMemoryManager_PX4(_NvMemoryManager_Imp); }
	return _NvMemoryManager;
}
