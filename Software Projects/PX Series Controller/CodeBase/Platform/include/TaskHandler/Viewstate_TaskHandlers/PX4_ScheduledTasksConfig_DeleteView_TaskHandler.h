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

class PX4_ScheduledTasksConfig_DeleteView_TaskHandler : public ITaskHandler
{
public:
	PX4_ScheduledTasksConfig_DeleteView_TaskHandler(IModelViewstateData * viewstateData, IModelTaskData * taskData, IViewstateMapGenerator * mapGenerator)
		: _viewstateData(viewstateData), _taskData(taskData), _mapGenerator(mapGenerator){};
	~PX4_ScheduledTasksConfig_DeleteView_TaskHandler() {};

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
};

inline bool PX4_ScheduledTasksConfig_DeleteView_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	int selectedElementIndex = _viewstateData->GetViewstateSelectableElementIndex();
	SelectableViewstateElementAlias selectedElement = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;
	ViewstateAlias selectedViewstate = _viewstateData->GetNavigationMap()->ViewstateAssociation();

	switch (_taskItem->GetTaskAssociation()) {
	case TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT:
		if (selectedElement == SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT && selectedElementIndex == 0)
		{
			selectedElement = SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC;
			selectedElementIndex = 0;
		}
		else if (selectedElementIndex < SCHEDULED_TASK_DETAIL_COUNT - _taskData->GetFreeScheduledTaskDetailCount() - 1) { ++selectedElementIndex; }

		break;

	case TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT:
		if (selectedElement == SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC && selectedElementIndex == 0)
		{
			selectedElement = SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT;
		}
		else if (selectedElement != SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT && selectedElementIndex > 0)
		{
			--selectedElementIndex;
		}

		break;

	case TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT:
		if (selectedElement == SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC)
		{
			selectedViewstate = ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_CONF_VIEW;
			selectedElement = SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT;
		}
		break;
	}

	ISelectableNavigationMap * const map = selectedViewstate != _viewstateData->GetNavigationMap()->ViewstateAssociation() ?
		_mapGenerator->GenerateMap(selectedViewstate) : _viewstateData->GetNavigationMap();

	map->SetSelection(selectedElement);
	_viewstateData->SetNavigationMap(map, selectedElementIndex); //SetNavigationMap call required to trigger viewstate refresh callback

	return true;
}

inline bool PX4_ScheduledTasksConfig_DeleteView_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_VIEW) { return false; }

	// This handler only handles menu select or menu navigation tasks
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT &&
		currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT &&
		currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ScheduledTasksConfig_DeleteView_TaskHandler::FlagStateChange()
{
	return true;
}