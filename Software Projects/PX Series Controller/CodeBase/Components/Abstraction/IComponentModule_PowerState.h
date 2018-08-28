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
#include "..\..\Platform\include\SharedStructure\ComponentPowerState.h"

class IComponentModule_PowerState
{
public:
	IComponentModule_PowerState() {}
	virtual ~IComponentModule_PowerState() = 0;
	virtual const bool IsEnabled() = 0;
	virtual const bool IsInOverride() = 0;
	virtual const ComponentPowerState GetPowerState() = 0;
};

inline IComponentModule_PowerState::~IComponentModule_PowerState() { }