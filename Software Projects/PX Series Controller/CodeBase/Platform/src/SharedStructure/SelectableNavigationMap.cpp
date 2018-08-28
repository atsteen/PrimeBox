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

#include "..\..\include\SharedStructure\SelectableNavigationMap.h"

const ViewstateAlias SelectableNavigationMap::ViewstateAssociation()
{
	return _alias;
}

const NavigationMapSelection * SelectableNavigationMap::CurrentSelection() const
{
	return _currentlySelected->element;
}

const NavigationMapSelection * SelectableNavigationMap::NavigateNextElement()
{
	_currentlySelected = _currentlySelected->next;
	return _currentlySelected->element;
}

const NavigationMapSelection * SelectableNavigationMap::NavigatePreviousElement()
{
	_currentlySelected = _currentlySelected->last;
	return _currentlySelected->element;
}

NavigationMapSelection * SelectableNavigationMap::NavigateElementSelect(NavigationMapSelection * selection)
{
	if (_currentlySelected->element->onSelectViewstateRedirect != ViewstateAlias::VIEWSTATEALIAS_NOT_SET)
	{
		selection->onSelectViewstateRedirect = _currentlySelected->element->onSelectViewstateRedirect;
		selection->onSelectSelectedElementRedirect = _currentlySelected->element->onSelectSelectedElementRedirect;
	}

	return selection;
}

bool SelectableNavigationMap::SetSelection(const SelectableViewstateElementAlias selection)
{
	if (_selectableElements.empty()) { return false; }

	const T_CircularListNode<NavigationMapSelection> * node = _selectableElements.front();

	do
	{
		if (node->element->selectedElement == selection)
		{
			_currentlySelected = node;
			return true;
		}
		node = node->next;
	} while (node != _selectableElements.front());

	return false;
}

void SelectableNavigationMap::AddSelection(const SelectableViewstateElementAlias selectableAlias)
{
	NavigationMapSelection * mapSelection = new NavigationMapSelection;
	
	mapSelection->viewstate = this->_alias;
	mapSelection->selectedElement = selectableAlias;
	_selectableElements.addBack(*mapSelection);

	if (!_currentlySelected) { _currentlySelected = _selectableElements.front(); }
}

void SelectableNavigationMap::AddSelectionWithRedirect(
	const SelectableViewstateElementAlias selectableAlias,
	const ViewstateAlias redirectViewstate,
	const SelectableViewstateElementAlias redirectSelectableElementAlias
)
{
	NavigationMapSelection * mapSelection = new NavigationMapSelection;

	mapSelection->viewstate = this->_alias;
	mapSelection->selectedElement = selectableAlias;
	mapSelection->onSelectViewstateRedirect = redirectViewstate;
	mapSelection->onSelectSelectedElementRedirect = redirectSelectableElementAlias;
	_selectableElements.addBack(*mapSelection);

	if (!_currentlySelected) { _currentlySelected = _selectableElements.front(); }
}

const NavigationMapSelection * SelectableNavigationMap::PeekNextElement()
{
	return _currentlySelected->next->element;
}

const NavigationMapSelection * SelectableNavigationMap::PeekPreviousElement()
{
	return _currentlySelected->last->element;
}
