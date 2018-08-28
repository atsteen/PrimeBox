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

#include "..\..\include\Viewstate_Element\Viewstate_Element_Text.h"

Viewstate_Element_Text::Viewstate_Element_Text(const int sIndex, const int iLevel, const SelectableViewstateElementAlias veAlias) 
	: _startIndex(sIndex), imbricationLevel(iLevel), alias(veAlias){}
Viewstate_Element_Text::~Viewstate_Element_Text() {}

void Viewstate_Element_Text::resetStartIndex(const int newIndex)
{
	_startIndex = newIndex;
}

int Viewstate_Element_Text::emplace(char * targetStr, const int){ return 0;}

int Viewstate_Element_Text::_emplace(char * targetStr, const int targetStrSize, const char * originStr)
{
	int emplacedLen = _startIndex + strlen(originStr);
	int charCount = 0;

	if (_startIndex >= targetStrSize - 1) { return 0; }
	else
	{
		charCount = emplacedLen >= targetStrSize ? targetStrSize - (_startIndex + 1) : strlen(originStr);

		for (int i = 0, t = _startIndex; i < charCount; i++, t++)
		{
			targetStr[t] = originStr[i];
		}
	}

	return charCount;
}
