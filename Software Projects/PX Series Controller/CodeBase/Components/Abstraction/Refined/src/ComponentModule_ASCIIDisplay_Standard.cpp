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

#include "..\include\ComponentModule_ASCIIDisplay_Standard.h"

ComponentModule_ASCIIDisplay_Standard::ComponentModule_ASCIIDisplay_Standard(ComponentModule_Imp_ASCIIDisplay* imp) : ComponentModule_ASCIIDisplay(imp){}

ComponentModule_ASCIIDisplay_Standard::~ComponentModule_ASCIIDisplay_Standard(){}

bool ComponentModule_ASCIIDisplay_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}

void ComponentModule_ASCIIDisplay_Standard::Enable()
{
	_imp->Enable_Imp();
	_isEnabled = true;
}

void ComponentModule_ASCIIDisplay_Standard::Disable()
{
	_imp->Disable_Imp();
	_isEnabled = false;
}

void ComponentModule_ASCIIDisplay_Standard::UpdateDisplay(const char * cstr)
{
	_imp->UpdateDisplay_Imp(cstr);
}
