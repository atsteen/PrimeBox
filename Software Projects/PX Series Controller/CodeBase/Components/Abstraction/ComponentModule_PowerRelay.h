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
#include "..\..\Components\Implementation\ComponentModule_Imp_PowerRelay.h"

class ComponentModule_PowerRelay :
	public IComponentModule
{
public:
	ComponentModule_PowerRelay(ComponentModule_Imp_PowerRelay *imp) : _imp(imp) {}
	virtual ~ComponentModule_PowerRelay() override { delete _imp; }

	virtual void Enable() = 0;
	virtual void Disable() = 0;

protected:
	ComponentModule_Imp_PowerRelay *_imp;
};