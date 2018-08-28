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
#include "..\..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"

class PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler : public ITaskHandler
{
public:
	PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler(IModelViewstateData * viewstateData, IModelTaskData * taskData, IViewstateMapGenerator * mapGenerator, IPowerRelayArray * relayArray)
		: _viewstateData(viewstateData), _taskData(taskData), _mapGenerator(mapGenerator), _relayArray(relayArray){};
	~PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IModelTaskData * _taskData;
	IViewstateMapGenerator * _mapGenerator;
	IPowerRelayArray * _relayArray;
};

inline bool PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	SelectableViewstateElementAlias selectedElement = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;
	ViewstateAlias nextViewstate;
	int index = -1;

	if (selectedElement == SelectableViewstateElementAlias::SELECTABLE_SCHEDULED_TASK_CREATE_SELECT_BYRELAY_ELEMENT)
	{
		index = 0;
		ComponentAssociation association(*_relayArray->GetRelayComponentAssociationByIndex(index));
		nextViewstate = VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_RELAY_VIEW;
		_taskData->SetCreateSchdTaskTarget(&association);
	}
	else { nextViewstate =  VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_ASSOCIATION_VIEW; }
	
	_taskData->SetCreateSchdTaskTargetIndex(&index);
	_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(nextViewstate)); //SetNavigationMap call required to trigger viewstate refresh callback
	
	return true;
}

inline bool PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_SELECT_VIEW) { return false; }

	// This handler only handles menu select tasks
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler::FlagStateChange()
{
	return true;
}