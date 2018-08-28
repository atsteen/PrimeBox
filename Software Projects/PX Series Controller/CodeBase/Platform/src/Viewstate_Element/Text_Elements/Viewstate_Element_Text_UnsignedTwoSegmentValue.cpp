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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_UnsignedTwoSegmentValue.h"
#include <stdlib.h>

Viewstate_Element_Text_UnsignedTwoSegmentValue::Viewstate_Element_Text_UnsignedTwoSegmentValue(const int start_index, const int imbricationLevel, const int twoSegmentValue) :
	Viewstate_Element_Text(start_index, imbricationLevel), _twoSegmentValue(twoSegmentValue){}

Viewstate_Element_Text_UnsignedTwoSegmentValue::~Viewstate_Element_Text_UnsignedTwoSegmentValue(){}

int Viewstate_Element_Text_UnsignedTwoSegmentValue::emplace(char * target, const int targetlen)
{	
	char buff[3];
	int i = _twoSegmentValue;

	if (i > 99) { i = 99; } //two segment max
	if (i < -99) { i = -99; } //two segment min

	_itoa(i, buff, 10);

	if(-10 < i && i < 10)
	{
		buff[1] = buff[0];
		buff[0] = '0';
		buff[2] = '\0';
	}

	return _emplace(target, targetlen, buff);
}
