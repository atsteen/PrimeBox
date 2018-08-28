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
#include "..\..\ComponentModule_ASCIIDisplay.h"
#include "..\..\..\Implementation\ComponentModule_Imp_ASCIIDisplay.h"

class ComponentModule_ASCIIDisplay_Standard :
	public ComponentModule_ASCIIDisplay
{
public:
	ComponentModule_ASCIIDisplay_Standard(ComponentModule_Imp_ASCIIDisplay* imp);
	virtual ~ComponentModule_ASCIIDisplay_Standard() override;

	const bool isEnabled() { return _isEnabled; }

	// Inherited via ComponentModule_ASCIIDisplay
	virtual bool DoSelfDiagnostic() override;
	virtual void Enable() override;
	virtual void Disable() override;
	virtual void UpdateDisplay(const char*) override;

protected:
	bool _isEnabled = false;
};

