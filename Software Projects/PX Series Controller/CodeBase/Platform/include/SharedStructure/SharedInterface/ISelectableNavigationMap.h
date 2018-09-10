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
#include "..\NavigationMapSelection.h"


class ISelectableNavigationMap
{
public:
	ISelectableNavigationMap() {};
	virtual ~ISelectableNavigationMap() = 0;

	virtual const ViewstateAlias ViewstateAssociation() = 0;
	virtual const NavigationMapSelection * CurrentSelection() const = 0; //returns the current viewstate selections
	virtual const NavigationMapSelection * NavigateNextElement() = 0; //set and return the next selected viewstate element
	virtual const NavigationMapSelection * PeekNextElement() = 0; //return the next element to be selected
	virtual const NavigationMapSelection * NavigatePreviousElement() = 0; //set and return the previous selected viewstate element
	virtual const NavigationMapSelection * PeekPreviousElement() = 0; //return the next element to be selected
	virtual NavigationMapSelection * NavigateElementSelect(NavigationMapSelection *) = 0; //returns viewstate selection if currently selected element is selected
	virtual bool SetSelection(const SelectableViewstateElementAlias) = 0; //sets selection, returns false if selection isnt available
	virtual void AddSelection(const SelectableViewstateElementAlias) = 0; //adds a new selection to the map
	virtual void AddSelectionWithRedirect(const SelectableViewstateElementAlias, const ViewstateAlias, const SelectableViewstateElementAlias) = 0; //adds a new selection to the map with redirect hint
};

inline ISelectableNavigationMap::~ISelectableNavigationMap() {}