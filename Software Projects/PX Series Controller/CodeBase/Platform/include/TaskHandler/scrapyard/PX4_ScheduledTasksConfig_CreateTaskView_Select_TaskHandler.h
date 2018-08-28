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

#include "..\TaskHandler.h"
#include "..\..\DataModel\DataModel_PX4.h"
#include "..\..\SharedStructure\PersistentData\Ipersistent.h"

class PX4_ScheduledTasksConfig_CreateTaskView_Select_TaskHandler
	: public TaskHandler, public Ipersistent
{
public:
	PX4_ScheduledTasksConfig_CreateTaskView_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_NEW_TASK_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //handle any viewstate element select
		){};

	~PX4_ScheduledTasksConfig_CreateTaskView_Select_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;	

	// Inherited via Ipersistent
	virtual void RestorePersistentData() override {}; // restore handled by DataModel
	virtual void UpdatePersistentData() override;
};

inline bool PX4_ScheduledTasksConfig_CreateTaskView_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline bool PX4_ScheduledTasksConfig_CreateTaskView_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	TaskAlias _selectableTasks[] = {
		TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_PUMP,
		TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_FAN,
		TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_LIGHTS,
		TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_PUMP,
		TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_FAN,
		TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_LIGHTS
	};

	if (_CanHandleTask(ti))
	{
		DataModel_PX4 * dm = &DataModel_PX4::GetInstance();
		uint8_t newTaskIndex = 0;

		switch (DataModel_PX4::GetInstance().GetSelectedViewstateElement()) {
		case SELECTABLE_BACK_ELEMENT:
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(SELECTABLE_MENU_SELECT_NEW_SCHD_TASK_ELEMENT, true);
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW);
			this->GetBuzzer()->playBackSelectTone();
			return true;

		case SELECTABLE_SCHEDULED_TASK_TASK_TYPE_ELEMENT:
			for (int i = 0; i < (sizeof(_selectableTasks) / sizeof(_selectableTasks[0])) - 1; ++i)
			{
				if (DataModel_PX4::GetInstance().GetCreateSchdTaskType() == _selectableTasks[i])
				{
					DataModel_PX4::GetInstance().SetCreateSchdTaskType(_selectableTasks[i+1]);
					return true;
				}
			}

			DataModel_PX4::GetInstance().SetCreateSchdTaskType(_selectableTasks[0]);
			break;

		case SELECTABLE_SCHEDULED_TASK_TASK_TIME_ELEMENT:
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_INPUT_PROMPT_NEW_TASK_TIME);
			break;

		case SELECTABLE_SCHEDULED_TASK_TASK_SAVE_ELEMENT:
			newTaskIndex = DataModel_PX4::GetInstance().GetScheduledTaskPool()->AddNewScheduledTask(
				DataModel_PX4::GetInstance().GetCreateSchdTaskType(),
				DataModel_PX4::GetInstance().GetCreateSchdTaskTime()
			);

			UpdatePersistentData();
			
			dm->SetSelectedViewstateElement(SELECTABLE_SCHEDULED_TASKLIST_SET_ELEMENT, true);
			dm->listSelectIndex = newTaskIndex;
			dm->SetActiveViewstate(VIEWSTATEALIAS_SCHEDULED_TASK_SET_EXISTING_VIEW);

			break;

		default:
			//todo... report invalid selecteditem value
			return false;
		}

		this->GetBuzzer()->playSelectTone();
		return true;
	}

	return false;
}

inline void PX4_ScheduledTasksConfig_CreateTaskView_Select_TaskHandler::UpdatePersistentData()
{
	// Update implementation handled here because DataModel has no set logic for ScheduledTaskPool
	NvMemoryManager()->WritePersistentItem(DataModel_PX4::GetInstance().GetScheduledTaskPool(), PersistentDataAlias::SCHEDULED_TASK_POOL);
}