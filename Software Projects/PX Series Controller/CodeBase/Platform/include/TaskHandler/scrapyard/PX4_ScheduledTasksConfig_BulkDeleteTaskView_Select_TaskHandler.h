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

class PX4_ScheduledTasksConfig_BulkDeleteTaskView_Select_TaskHandler
	: public TaskHandler, public Ipersistent
{
public:
	PX4_ScheduledTasksConfig_BulkDeleteTaskView_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_BULK_DELETE_TASK_CONF_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //handle any viewstate element select
		){};

	~PX4_ScheduledTasksConfig_BulkDeleteTaskView_Select_TaskHandler() {};

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

inline bool PX4_ScheduledTasksConfig_BulkDeleteTaskView_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline bool PX4_ScheduledTasksConfig_BulkDeleteTaskView_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		switch (DataModel_PX4::GetInstance().GetSelectedViewstateElement()) {
		case SELECTABLE_BACK_ELEMENT:
		case SELECTABLE_SCHEDULED_TASK_BULK_DELETE_CONFNO_ELEMENT:
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(SELECTABLE_MENU_SELECT_BULK_DELETE_SCHD_TASK_ELEMENT, true);
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW);
			this->GetBuzzer()->playBackSelectTone();
			return true;

		case SELECTABLE_SCHEDULED_TASK_BULK_DELETE_CONFYES_ELEMENT:
			DataModel_PX4::GetInstance().GetScheduledTaskPool()->FreeAllScheduledTaskDetails();
			UpdatePersistentData();
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(SELECTABLE_MENU_SELECT_BULK_DELETE_SCHD_TASK_ELEMENT, true);
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW);
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

inline void PX4_ScheduledTasksConfig_BulkDeleteTaskView_Select_TaskHandler::UpdatePersistentData()
{
	// Update implementation handled here because DataModel has no set logic for ScheduledTaskPool
	NvMemoryManager()->WritePersistentItem(DataModel_PX4::GetInstance().GetScheduledTaskPool(), PersistentDataAlias::SCHEDULED_TASK_POOL);
}