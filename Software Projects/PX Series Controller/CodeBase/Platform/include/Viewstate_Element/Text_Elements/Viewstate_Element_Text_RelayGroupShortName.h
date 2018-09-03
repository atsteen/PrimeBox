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
#include "..\..\SharedStructure\ComponentAssociation.h"

class Viewstate_Element_Text_RelayGroupShortName :
	public Viewstate_Element_Text
{
public:
	Viewstate_Element_Text_RelayGroupShortName(const int, const int, const ComponentGroupAssociation);
	~Viewstate_Element_Text_RelayGroupShortName();

	virtual int emplace(char *, const int) override;

private:
	const ComponentGroupAssociation _groupAssociation;
};