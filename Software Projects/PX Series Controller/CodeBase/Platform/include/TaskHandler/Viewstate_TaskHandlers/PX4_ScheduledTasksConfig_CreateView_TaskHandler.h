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
#include "..\..\SharedStructure\TaskItemPool.h"

class PX4_ScheduledTasksConfig_CreateView_TaskHandler : public ITaskHandler
{
public:
	PX4_ScheduledTasksConfig_CreateView_TaskHandler(IModelViewstateData * viewstateData, IModelTaskData * taskData, IViewstateMapGenerator * mapGenerator, IPowerRelayArray * relayArray, INavigationTones * navTonePlayer)
		: _viewstateData(viewstateData), _taskData(taskData), _mapGenerator(mapGenerator), _relayArray(relayArray), _navTonePlayer(navTonePlayer){};
	~PX4_ScheduledTasksConfig_CreateView_TaskHandler() {};

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
	INavigationTones * _navTonePlayer;
};

inline bool PX4_ScheduledTasksConfig_CreateView_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	ViewstateAlias currentViewstate = _viewstateData->GetNavigationMap()->ViewstateAssociation();
	SelectableViewstateElementAlias selectedElement = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;
	IDynamicData * dynamicDataProxy;

	switch (selectedElement)
	{
	case SELECTABLE_SCHEDULED_TASK_TASK_ACTION_ELEMENT:
		dynamicDataProxy = new T_DynamicDataProxy<IModelTaskData, bool>(
			currentViewstate,
			selectedElement,
			ViewstateStringAlias::INPUT_PROMPT_SET_TASK_ACTION,
			Viewstate_String_Generator::timespanMinuteSymbol,
			&IModelTaskData::GetCreateSchdTaskAction,
			&IModelTaskData::SetCreateSchdTaskAction,
			_taskData
			);

			_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
			_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ENABLE_DISABLE));
			_navTonePlayer->playSelectTone();
			return true;

	case SELECTABLE_SCHEDULED_TASK_TASK_TIME_ELEMENT:
		dynamicDataProxy = new T_DynamicDataProxy<IModelTaskData, TimeSignature>(
			currentViewstate,
			selectedElement,
			ViewstateStringAlias::INPUT_PROMPT_SET_TIME_SIGNATURE,
			Viewstate_String_Generator::timespanMinuteSymbol,
			&IModelTaskData::GetCreateSchdTaskTime,
			&IModelTaskData::SetCreateSchdTaskTime,
			_taskData
			);

			_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
			_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_TIME));
			_navTonePlayer->playSelectTone();
			return true;

	case SELECTABLE_SAVE_ELEMENT:
		
		TaskAlias newTaskAlias = *_taskData->GetCreateSchdTaskAction() ? TaskAlias::TASKALIAS_ENABLE_POWER_RELAY : TaskAlias::TASKALIAS_DISABLE_POWER_RELAY;
		const int newTaskRelayIndex = *_taskData->GetCreateSchdTaskTargetIndex();
		const TimeSignature * const newTaskExecutionTime = _taskData->GetCreateSchdTaskTime();
		const ComponentAssociation * const newTaskRelayAssociation = _taskData->GetCreateSchdTaskTarget();

		TaskDetailData taskDetailData;
		taskDetailData.scheduledTaskAlias = newTaskAlias;
		taskDetailData.isEnabaled = true;
		taskDetailData.relayAssociation = *newTaskRelayAssociation;
		taskDetailData.relayIndex = newTaskRelayIndex;
		taskDetailData.scheduledExecutionTime.SetSignature(newTaskExecutionTime);
		
		const int newTaskDetailIndex = _taskData->AddScheduledTaskDetail(&taskDetailData);

		ISelectableNavigationMap * map = _mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_SET_EXISTING_VIEW);
		map->SetSelection(SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC);
		if (newTaskDetailIndex >= 0) { _viewstateData->SetViewstateSelectableElementIndex(newTaskDetailIndex); }
		_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_SET_EXISTING_VIEW));
		_navTonePlayer->playSelectTone();
		_taskData->ClearCreateSchdTaskValues();
		
		return true;
	}
	
	return true;
}

inline bool PX4_ScheduledTasksConfig_CreateView_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TASK_VIEW) { return false; }

	// This handler only handles menu select tasks
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ScheduledTasksConfig_CreateView_TaskHandler::FlagStateChange()
{
	return true;
}