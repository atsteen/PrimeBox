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
#include "..\..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"

class PX4_PowerRelayEditViewstate_TaskHandler : public ITaskHandler
{
public:
	PX4_PowerRelayEditViewstate_TaskHandler(IModelViewstateData * viewstateData, IViewstateMapGenerator * mapGenerator, IPowerRelayArray * relayArray, INavigationTones * navTonePlayer)
		: _viewstateData(viewstateData), _mapGenerator(mapGenerator), _relayArray(relayArray), _navTonePlayer(navTonePlayer){};
	~PX4_PowerRelayEditViewstate_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IViewstateMapGenerator * _mapGenerator;
	IPowerRelayArray * _relayArray;
	INavigationTones * _navTonePlayer;
};

inline bool PX4_PowerRelayEditViewstate_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	ISelectableNavigationMap * map = _viewstateData->GetNavigationMap(); 
	const SelectableViewstateElementAlias currentlySelectedElement = map->CurrentSelection()->selectedElement;
	const int currentlySelectedRelayIndex = _viewstateData->GetViewstateSelectableElementIndex();
	ComponentAssociation relayConfig(*_relayArray->GetRelayComponentAssociationByIndex(currentlySelectedRelayIndex));

	if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT)
	{
		ISelectableNavigationMap * newMap = _mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW);
		newMap->SetSelection(SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC);
		_viewstateData->SetNavigationMap(newMap);
		_navTonePlayer->playBackSelectTone();
		return true;
	}

	if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_EDIT_RELAY_TYPE)
	{
		switch (relayConfig.typeAssociation) {
		case ComponentTypeAssociation::LIGHT_PRIMARY:
			relayConfig.typeAssociation = PUMP_WATER;			
			break; 
		case ComponentTypeAssociation::PUMP_WATER:
			relayConfig.typeAssociation = FAN_CIRCULATION;
			break;
		case ComponentTypeAssociation::FAN_CIRCULATION :
			relayConfig.typeAssociation = FAN_EXHAUST;
			break;
		default:
			relayConfig.typeAssociation = LIGHT_PRIMARY;
		}

		_navTonePlayer->playSelectTone();
	}

	if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_EDIT_RELAY_GROUP)
	{
		switch (relayConfig.groupAssociation) {
		case ComponentGroupAssociation::GROUP_A :
			relayConfig.groupAssociation = GROUP_B;
			break;
		case ComponentGroupAssociation::GROUP_B:
			relayConfig.groupAssociation = GROUP_C;
			break;
		case ComponentGroupAssociation::GROUP_C:
			relayConfig.groupAssociation = GROUP_D;
			break;
		default:
			relayConfig.groupAssociation = GROUP_A;
		}
		_navTonePlayer->playSelectTone();
	}

	_relayArray->SetRelayComponentAssociationByIndex(currentlySelectedRelayIndex, &relayConfig);
	_viewstateData->ForceModelUpdateNotify();
	return true;
}

inline bool PX4_PowerRelayEditViewstate_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{	
	// This handler only handles tasks for VIEWSTATEALIAS_POWER_RELAY_EDIT_VIEW
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_EDIT_VIEW){ return false; }
	
	// This handler only handles TASKALIAS_NAVIGATION_MENU_SELECT tasks when selected element is not the back element
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_PowerRelayEditViewstate_TaskHandler::FlagStateChange()
{
	return true;
}