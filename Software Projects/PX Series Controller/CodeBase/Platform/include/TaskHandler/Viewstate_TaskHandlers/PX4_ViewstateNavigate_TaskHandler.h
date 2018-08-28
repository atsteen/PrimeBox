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

#include "..\..\SharedStructure\SharedInterface\ITaskHandler.h"
#include "..\..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\..\SharedStructure\TaskItem.h"
#include "..\..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\..\SharedStructure\SharedInterface\INavigationTones.h"

class PX4_ViewstateNavigate_TaskHandler	: public ITaskHandler
{
public:
	PX4_ViewstateNavigate_TaskHandler(IModelViewstateData * viewstateData, IViewstateMapGenerator * mapGenerator, INavigationTones * navTonePlayer)
		: _viewstateData(viewstateData), _mapGenerator(mapGenerator), _navTonePlayer(navTonePlayer){};
	~PX4_ViewstateNavigate_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IViewstateMapGenerator * _mapGenerator;
	INavigationTones * _navTonePlayer;
};

inline bool PX4_ViewstateNavigate_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	const NavigationMapSelection * currentMapSelection = _viewstateData->GetNavigationMap()->CurrentSelection();
	ISelectableNavigationMap * nextMap;
	enum selectType { NAV, BACK_SELECT, FWD_SELECT };
	selectType _selectType = NAV;

	// Handle basic menu select with viewstate auto-redirect
	if (currentTaskAssociation == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{		
		if (currentMapSelection->selectedElement == SELECTABLE_BACK_ELEMENT) { _selectType = BACK_SELECT; }
		else { _selectType = FWD_SELECT; }

		nextMap = _mapGenerator->GenerateMap(currentMapSelection->onSelectViewstateRedirect);
		nextMap->SetSelection(currentMapSelection->onSelectSelectedElementRedirect);
	}
	else // Handle menu navigation
	{
		const NavigationMapSelection * nextMapSelection;

		if (currentTaskAssociation == TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)
		{
			nextMapSelection = _viewstateData->GetNavigationMap()->NavigateNextElement();			
		}
		else
		{
			nextMapSelection = _viewstateData->GetNavigationMap()->NavigatePreviousElement();
		}

		if(nextMapSelection->selectedElement == SELECTABLE_ELEMENT_AUTO_REDIR)
		{
			nextMap = _mapGenerator->GenerateMap(nextMapSelection->onSelectViewstateRedirect);
			nextMap->SetSelection(nextMapSelection->onSelectSelectedElementRedirect);
		}
		else
		{
			nextMap = _viewstateData->GetNavigationMap();
			nextMap->SetSelection(nextMapSelection->selectedElement);
		}
	}

	_viewstateData->SetNavigationMap(nextMap);

	switch (_selectType) {
	case BACK_SELECT:
		_navTonePlayer->playBackSelectTone();
		break;
	case FWD_SELECT:
		_navTonePlayer->playSelectTone();
		break;
	default:
		_navTonePlayer->playNavTone();
	}

	return true;
}

inline bool PX4_ViewstateNavigate_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	const ViewstateAlias onSelectViewstateRedirectAlias = _viewstateData->GetNavigationMap()->CurrentSelection()->onSelectViewstateRedirect;

	// This handler only handles menu select or menu navigation tasks
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT &&
		currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT &&
		currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)
	{
		return false;
	}

	// This handler does not handle requests when the viewstate is in modal select
	if (_viewstateData->GetDynamicViewstateModalState()) { return false; }

	// This handler does not handle MENU NAVIGATIONS when the currently selected element is dynamically generated
	if (_viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement == SELECTABLE_ELEMENT_DYNAMIC) { return false; }

	// This handler does not handle MENU NAVIGATIONS when the next selected element is is dynamically generated
	if (currentTaskAssociation != TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		const NavigationMapSelection * nextMapSelection;

		if (currentTaskAssociation == TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)
		{
			nextMapSelection = _viewstateData->GetNavigationMap()->PeekNextElement();
		}
		else
		{
			nextMapSelection = _viewstateData->GetNavigationMap()->PeekPreviousElement();
		}

		//if (nextMapSelection->selectedElement != SELECTABLE_ELEMENT_AUTO_REDIR) { return false; }
		if (nextMapSelection->selectedElement == SELECTABLE_ELEMENT_DYNAMIC) { return false; }
	}

	// This handler does not handle SELECT NAVIGATIONS if the selected menu element does not have a valid viewstate redirect	
	if (currentTaskAssociation == TASKALIAS_NAVIGATION_MENU_SELECT && onSelectViewstateRedirectAlias == ViewstateAlias::VIEWSTATEALIAS_NOT_SET)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ViewstateNavigate_TaskHandler::FlagStateChange()
{
	return true;
}