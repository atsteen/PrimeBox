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
#include "ITextViewstate.h"
#include "..\Viewstate_Element\Viewstate_Element_Text.h"
#include "..\SharedStructure\VElementList.h"
#include "..\SharedStructure\ViewstateAlias.h"
 
class Viewstate_PX4 : public ITextViewstate
{
public:
	Viewstate_PX4(ViewstateAlias alias) : ITextViewstate(alias) {};
	virtual ~Viewstate_PX4() {};

	void AddViewstateElement(Viewstate_Element_Text *);

	virtual char * RenderText(char * vs_OutBuffer, const int bufferSize) override { return vs_OutBuffer; }

protected:
	VElementList _vsElements;
	void _clearBuffer(char *, int);
};
