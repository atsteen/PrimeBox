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
#include "..\Implementation\ComponentModule_Imp.h"

class ComponentModule_Imp_ASCIIDisplay :
	public ComponentModule_Imp
{
public:

	ComponentModule_Imp_ASCIIDisplay(){}
	virtual ~ComponentModule_Imp_ASCIIDisplay() = 0;

	virtual void Enable_Imp() = 0;
	virtual void Disable_Imp() = 0;
	virtual void UpdateDisplay_Imp(const char*) = 0;
};

inline ComponentModule_Imp_ASCIIDisplay::~ComponentModule_Imp_ASCIIDisplay() {}