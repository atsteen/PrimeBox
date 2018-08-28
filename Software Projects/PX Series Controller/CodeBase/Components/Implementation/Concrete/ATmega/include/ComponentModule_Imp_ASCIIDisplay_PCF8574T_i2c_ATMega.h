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
#include "..\..\include\PreProcDirectives.h"
#include "..\..\include\ComponentModule_Imp\ComponentModule_Imp_ASCIIDisplay.h"

#if defined(TARGET_PLAT_AVR)

// Using F Malpartida's NewLiquidCrystal library: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Example usage for V1 backpack: http://arduino-info.wikispaces.com/LCD-Blue-I2C#v1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class ComponentModule_Imp_ASCIIDisplay_ATMega :
	public ComponentModule_Imp_ASCIIDisplay
{
public:
	ComponentModule_Imp_ASCIIDisplay_ATMega();
	~ComponentModule_Imp_ASCIIDisplay_ATMega();

	// Inherited via ComponentModule_Imp_ASCIIDisplay
	virtual bool DoSelfDiagnostic_Imp() override;
	virtual void Enable_Imp() override;
	virtual void Disable_Imp() override;
	virtual void UpdateDisplay_Imp(const char*) override;

private:
	LiquidCrystal_I2C *_lcd;
	void _processSymbol(const int, char *, const char*, int);
	bool _specialChars = true;
};

#endif

