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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_DynamicThreeSegmentText.h"

Viewstate_Element_Text_DynamicThreeSegmentText::Viewstate_Element_Text_DynamicThreeSegmentText(
	const int start_index,
	const int imbricationLevel,
	const int threeSegmentValue,
	const char * valueSuffix = nullptr)
	: Viewstate_Element_Text(start_index, imbricationLevel), _threeSegmentValue(threeSegmentValue), _suffixSymbol(valueSuffix){}

Viewstate_Element_Text_DynamicThreeSegmentText::~Viewstate_Element_Text_DynamicThreeSegmentText(){}

int Viewstate_Element_Text_DynamicThreeSegmentText::emplace(char * target, const int targetlen)
{
	char buff[7] = {};
	char dispText[7] = {"["};

	if (_threeSegmentValue > 999) { _threeSegmentValue = 999; } //three segment max
	if (_threeSegmentValue < 100) { strcat(dispText, " "); }

	itoa(_threeSegmentValue, buff, 10);

	strncat(dispText, buff, 3);
	strncat(dispText, !_suffixSymbol ? _defaultSuffixSymbol : _suffixSymbol, 1);
	strncat(dispText, "]", 1);

	return _emplace(target, targetlen, dispText);
}
