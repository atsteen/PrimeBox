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
#include "..\..\Components\Implementation\ComponentModule_Imp_RTC.h"
#include "..\..\Platform\include\SharedStructure\TimeSignature.h"

class ComponentModule_RTC :
	public IComponentModule
{
public:
	ComponentModule_RTC(ComponentModule_Imp_RTC *imp) : _imp(imp) {}
	virtual ~ComponentModule_RTC() override { delete _imp; }

	virtual const char* GetCurrentTimeText() = 0;
	virtual const TimeSignature& GetCurrentSystemTime() = 0;

protected:
	ComponentModule_Imp_RTC *_imp;
};