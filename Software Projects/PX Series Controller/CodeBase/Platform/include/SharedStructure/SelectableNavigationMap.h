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
#include "SharedInterface\ISelectableNavigationMap.h"
#include "T_CircularList.h"

class SelectableNavigationMap : public ISelectableNavigationMap
{
public:
	SelectableNavigationMap(ViewstateAlias alias) : _alias(alias){};
	~SelectableNavigationMap() {};

	// Inherited via ISelectableNavigationMap
	virtual const ViewstateAlias ViewstateAssociation() override;
	virtual const NavigationMapSelection * CurrentSelection() const override;
	virtual const NavigationMapSelection * NavigateNextElement() override;
	virtual const NavigationMapSelection * NavigatePreviousElement() override;
	virtual NavigationMapSelection * NavigateElementSelect(NavigationMapSelection *) override;
	virtual bool SetSelection(const SelectableViewstateElementAlias) override;
	virtual void AddSelection(const SelectableViewstateElementAlias) override;
	virtual void AddSelectionWithRedirect(const SelectableViewstateElementAlias selectableAlias, const ViewstateAlias redirectViewstate, const SelectableViewstateElementAlias redirectSelectableElementAlias) override;

private:
	const ViewstateAlias _alias;
	const T_CircularListNode<NavigationMapSelection> * _currentlySelected = nullptr;
	int _dynamicElementSelectionIndex = 0;
	T_CircularList<NavigationMapSelection> _selectableElements;

	// Inherited via ISelectableNavigationMap
	virtual const NavigationMapSelection * PeekNextElement() override;
	virtual const NavigationMapSelection * PeekPreviousElement() override;
};