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
#include "..\Viewstate_Element_Text.h"
#include "..\..\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\..\SharedStructure\TimeSignature.h"

class Viewstate_Element_Text_DynamicThreeSegmentText :
	public Viewstate_Element_Text
{
public:
	Viewstate_Element_Text_DynamicThreeSegmentText(const int start_index, const int imbricationLevel, const int threeSegmentValue, const char * valueSuffix);
	~Viewstate_Element_Text_DynamicThreeSegmentText();

	virtual int emplace(char *, const int) override;

protected:
	int _threeSegmentValue;
	const char * _suffixSymbol;
	const char * _defaultSuffixSymbol = "-";
};