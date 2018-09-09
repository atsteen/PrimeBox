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
#pragma warning (disable : 4996) //disable VS compiler error on itoa use

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ThreeSegmentValue.h"
#include <string.h>
#include <stdlib.h>

Viewstate_Element_Text_ThreeSegmentValue::Viewstate_Element_Text_ThreeSegmentValue(const int start_index, const int imbricationLevel, const int threeSegVal, const char * suffixSymbol) : 
	Viewstate_Element_Text(start_index, imbricationLevel),
	_threeSegmentValue(threeSegVal)
{
	_suffixSymbol = suffixSymbol;
}

Viewstate_Element_Text_ThreeSegmentValue::~Viewstate_Element_Text_ThreeSegmentValue(){}

int Viewstate_Element_Text_ThreeSegmentValue::emplace(char * target, const int targetlen)
{	
	char buff[4];
	char valText[7] = "[";
	int i = _threeSegmentValue;

	if (i > 999) { i = 999; } //three segment max
	if (i < 100) { strcat(valText, " "); }

	itoa(_threeSegmentValue, buff, 10);

	strncat(valText, buff, 3);
	strncat(valText, _suffixSymbol, 1);
	strncat(valText, "]", 1);

 	return _emplace(target, targetlen, valText);
}
