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

#define SELECTABLE_ELEMENT_COUNT 4
class PX4_ScheduledTasksConfig_DeleteTaskView_Navigate_TaskHandler
	: public TaskHandler
{
public:
	PX4_ScheduledTasksConfig_DeleteTaskView_Navigate_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NOT_SET, //Leave TASKALIAS_NOT_SET to handle both navLeft and navRight
			ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //Leave SELECTABLE_ELEMENT_NOT_SET to handle all viewstate selections
		) {};

	~PX4_ScheduledTasksConfig_DeleteTaskView_Navigate_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;
};

inline bool PX4_ScheduledTasksConfig_DeleteTaskView_Navigate_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT) |
		(ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline bool PX4_ScheduledTasksConfig_DeleteTaskView_Navigate_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		DataModel_PX4 * dm = &DataModel_PX4::GetInstance();

		if (dm->GetScheduledTaskPool()->FreeScheduledTaskDetailCount() == SCHEDULED_TASK_DETAIL_COUNT)
		{
			dm->SetSelectedViewstateElement(SELECTABLE_BACK_ELEMENT);
			this->GetBuzzer()->playNavTone();
			return true;
		}

		if (ti->GetTaskAssociation() == TASKALIAS_NAVIGATION_MENU_MOVE_LEFT)
		{
			if (dm->listSelectIndex == 0) { dm->SetSelectedViewstateElement(SELECTABLE_BACK_ELEMENT); }
			else { --dm->listSelectIndex; }
			this->GetBuzzer()->playNavTone();
			return true;
		}
		else
		{
			if(dm->GetSelectedViewstateElement() == SELECTABLE_BACK_ELEMENT)
			{
				dm->SetSelectedViewstateElement(SELECTABLE_SCHEDULED_TASKLIST_EDIT_ELEMENT); 
			}
			else if(dm->listSelectIndex < (SCHEDULED_TASK_DETAIL_COUNT - dm->GetScheduledTaskPool()->FreeScheduledTaskDetailCount() - 1))
			{
				++dm->listSelectIndex;
			}

			this->GetBuzzer()->playNavTone();
			return true;
		}
	}

	return false;
}

