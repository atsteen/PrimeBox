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
#include "..\..\Components\Abstraction\IComponentModule.h"
#include "..\..\Platform\include\SharedStructure\SharedInterface\IPersistentDataCoordinator.h"
#include "..\..\Components\Implementation\ComponentModule_Imp_NvMemoryManager.h"

class ComponentModule_NvMemoryManager :
	public IComponentModule, public IPersistentDataCoordinator
{
public:
	ComponentModule_NvMemoryManager(ComponentModule_Imp_NvMemoryManager *imp) : _imp(imp) {}
	virtual ~ComponentModule_NvMemoryManager() override { delete _imp; }

protected:
	ComponentModule_Imp_NvMemoryManager *_imp;
};