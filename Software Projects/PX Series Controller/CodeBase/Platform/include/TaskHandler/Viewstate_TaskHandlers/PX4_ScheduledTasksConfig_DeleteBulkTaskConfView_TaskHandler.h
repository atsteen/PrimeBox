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

class PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler : public ITaskHandler
{
public:
	PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler(IModelViewstateData * viewstateData, IModelTaskData * taskData, IViewstateMapGenerator * mapGenerator)
		: _viewstateData(viewstateData), _mapGenerator(mapGenerator), _taskData(taskData){};
	~PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler() {};

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
};

inline bool PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	ISelectableNavigationMap * map = _viewstateData->GetNavigationMap(); 
	const SelectableViewstateElementAlias currentlySelectedElement = map->CurrentSelection()->selectedElement;

	if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SCHEDULED_TASK_BULK_DELETE_CONFYES_ELEMENT)
	{
		int i = SCHEDULED_TASK_DETAIL_COUNT-1;
		while(i >= 0)
		{
			_taskData->FreeScheduledTaskDetailByIndex(i--);
		}
	}
	
	map = _mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW);
	map->SetSelection(SelectableViewstateElementAlias::SELECTABLE_MENU_SELECT_DELETE_SCHD_TASK_ELEMENT);
	_viewstateData->SetNavigationMap(map);

	return true;
}

inline bool PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{	
	// This handler only handles tasks for VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TYPECONF_VIEW
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_BULK_DELETE_TASK_CONF_VIEW)
	{
		return false;
	}
	
	// This handler only handles TASKALIAS_NAVIGATION_MENU_SELECT
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler::FlagStateChange()
{
	return true;
}