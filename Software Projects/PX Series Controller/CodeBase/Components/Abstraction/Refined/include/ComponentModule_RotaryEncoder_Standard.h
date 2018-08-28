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
#include "..\..\ComponentModule_RotaryEncoder.h"

class ComponentModule_RotaryEncoder_Standard :
	public ComponentModule_RotaryEncoder
{
public:
	ComponentModule_RotaryEncoder_Standard(ComponentModule_Imp_RotaryEncoder *imp);
	virtual ~ComponentModule_RotaryEncoder_Standard() override;

	// Inherited via ComponentModule
	virtual bool DoSelfDiagnostic() override;

	// Inherited via ComponentModule_RotaryEncoder
	virtual TaskAlias GetFlaggedTask() override;
};

