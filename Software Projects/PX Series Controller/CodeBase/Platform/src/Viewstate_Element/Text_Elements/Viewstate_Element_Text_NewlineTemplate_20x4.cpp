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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_NewlineTemplate_20x4.h"

Viewstate_Element_Text_NewlineTemplate_20x4::Viewstate_Element_Text_NewlineTemplate_20x4(const int start_index, const int imbricationLevel) : Viewstate_Element_Text(start_index, imbricationLevel){}
Viewstate_Element_Text_NewlineTemplate_20x4::~Viewstate_Element_Text_NewlineTemplate_20x4(){}

int Viewstate_Element_Text_NewlineTemplate_20x4::emplace(char * target, const int targetlen)
{
	_ve_newLine1.emplace(target, targetlen);
	_ve_newLine2.emplace(target, targetlen);
	_ve_newLine3.emplace(target, targetlen);
	
	return -1;
}
