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
#include "..\..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

class Viewstate_Element_Text_StaticText :
	public Viewstate_Element_Text
{
public:
	Viewstate_Element_Text_StaticText(const int, const int, const char *, SelectableViewstateElementAlias sa = SELECTABLE_ELEMENT_NOT_SET);
	~Viewstate_Element_Text_StaticText();

	virtual int emplace(char *, const int) override;

protected:
	const char * _text;
};