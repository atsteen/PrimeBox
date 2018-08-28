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
#include "IViewstate_Element.h"
#include "..\SharedStructure\SelectableViewstateElementAlias.h"
#include <string.h>

class Viewstate_Element_Text :
	public IViewstate_Element
{
public:
	Viewstate_Element_Text(const int sIndex, const int iLevel, const SelectableViewstateElementAlias vAlias = SELECTABLE_ELEMENT_NOT_SET);
	virtual ~Viewstate_Element_Text() override;
	const int imbricationLevel;
	Viewstate_Element_Text * nextElement = nullptr;
	int _startIndex;
	const SelectableViewstateElementAlias alias = SELECTABLE_ELEMENT_NOT_SET;

	virtual void resetStartIndex(const int) override;

	// Inherited via IViewstate_Element
	virtual int emplace(char *, const int) override;

protected:	
	int _emplace(char *, const int, const char *);
	
};

