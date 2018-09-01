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
#include "..\..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"

class PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler: public ITaskHandler
{
public:
	PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler(IModelViewstateData * viewstateData, IModelTaskData * taskData, IViewstateMapGenerator * mapGenerator, IPowerRelayArray * relayArray, INavigationTones * navTonePlayer)
		: _viewstateData(viewstateData), _mapGenerator(mapGenerator), _taskData(taskData), _relayArray(relayArray), _navTonePlayer(navTonePlayer){};
	~PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IViewstateMapGenerator * _mapGenerator;
	IModelTaskData * _taskData;
	IPowerRelayArray * _relayArray;
	INavigationTones * _navTonePlayer;;
};

inline bool PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	ISelectableNavigationMap * map = _viewstateData->GetNavigationMap(); 
	const SelectableViewstateElementAlias currentlySelectedElement = map->CurrentSelection()->selectedElement;
	int currentlySelectedRelayIndex = *_taskData->GetCreateSchdTaskTargetIndex();
	ComponentAssociation taskAssociation(*_taskData->GetCreateSchdTaskTarget());

	switch (currentlySelectedElement) {

	case SELECTABLE_SCHEDULED_TASK_CREATE_RELAY_TASK_ELEMENT:
		if (*_taskData->GetCreateSchdTaskTargetIndex() >= _relayArray->CircuitCount() - 1) { currentlySelectedRelayIndex = 0; }
		else { ++currentlySelectedRelayIndex; }
		
		_taskData->SetCreateSchdTaskTargetIndex(&currentlySelectedRelayIndex);
		_taskData->SetCreateSchdTaskTarget(_relayArray->GetRelayComponentAssociationByIndex(currentlySelectedRelayIndex));

		break;

	case SELECTABLE_SCHEDULED_TASK_CREATE_TYPE_TASK_ELEMENT:

		switch (taskAssociation.typeAssociation) {
		case ComponentTypeAssociation::FAN_CIRCULATION:
			taskAssociation.typeAssociation = ComponentTypeAssociation::FAN_EXHAUST;
			break;
		case ComponentTypeAssociation::FAN_EXHAUST:
			taskAssociation.typeAssociation = ComponentTypeAssociation::LIGHT_PRIMARY;
			break;
		case ComponentTypeAssociation::LIGHT_PRIMARY:
			taskAssociation.typeAssociation = ComponentTypeAssociation::PUMP_WATER;
			break;
		default:
			taskAssociation.typeAssociation = ComponentTypeAssociation::FAN_CIRCULATION;
		}

		_taskData->SetCreateSchdTaskTarget(&taskAssociation);

		break;

	case SELECTABLE_SCHEDULED_TASK_CREATE_GROUP_TASK_ELEMENT:

		switch (taskAssociation.groupAssociation) {
		case ComponentGroupAssociation::GROUP_A:
			taskAssociation.groupAssociation = ComponentGroupAssociation::GROUP_B;
			break;
		case ComponentGroupAssociation::GROUP_B:
			taskAssociation.groupAssociation = ComponentGroupAssociation::GROUP_C;
			break;
		case ComponentGroupAssociation::GROUP_C:
			taskAssociation.groupAssociation = ComponentGroupAssociation::GROUP_D;
			break;
		default:
			taskAssociation.groupAssociation = ComponentGroupAssociation::GROUP_A;
		}

		_taskData->SetCreateSchdTaskTarget(&taskAssociation);
		break;
	}
	_navTonePlayer->playSelectTone();
	return true;
}

inline bool PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{	
	// This handler only handles tasks for VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TYPECONF_VIEW
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_ASSOCIATION_VIEW
		&& _viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_RELAY_VIEW)
	{
		return false;
	}
	
	// This handler only handles TASKALIAS_NAVIGATION_MENU_SELECT tasks when selected element is not the back element
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler::FlagStateChange()
{
	return true;
}