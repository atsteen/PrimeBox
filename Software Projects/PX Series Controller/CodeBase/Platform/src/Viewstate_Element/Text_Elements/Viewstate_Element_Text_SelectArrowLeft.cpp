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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowLeft.h"

Viewstate_Element_Text_SelectArrowLeft::Viewstate_Element_Text_SelectArrowLeft(const int start_index, const int imbricationLevel) : Viewstate_Element_Text(start_index, imbricationLevel){}
Viewstate_Element_Text_SelectArrowLeft::~Viewstate_Element_Text_SelectArrowLeft(){}

int Viewstate_Element_Text_SelectArrowLeft::emplace(char * target, const int targetlen)
{
		return _emplace(target, targetlen, Viewstate_String_Generator::selectBackSymbol);
}

int Viewstate_Element_Text_SelectArrowLeft::emplaceOver(char * target, const int targetlen, Viewstate_Element_Text *et)
{
	_startIndex = et->_startIndex;
	et->emplace(target, targetlen);
	return this->emplace(target, targetlen);
}
