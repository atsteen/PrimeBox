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

class PX4_TLMV_Select_TaskHandler 
	: public TaskHandler
{
public:
	PX4_TLMV_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_NOT_SET, //handle any TLMV selection
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET
		){};

	~PX4_TLMV_Select_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return false; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;
};

inline bool PX4_TLMV_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		switch (DataModel_PX4::GetInstance().GetActiveViewstate()) {
		case VIEWSTATEALIAS_STATUS_VIEW:
			DataModel_PX4::GetInstance().SetActiveViewstate(ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW);
			break;
		case VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW_TLMV:
			DataModel_PX4::GetInstance().SetActiveViewstate(ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW);
			break;
		case VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW_TLMV:
			DataModel_PX4::GetInstance().SetActiveViewstate(ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW);
			break;
		case VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW_TLMV:
			DataModel_PX4::GetInstance().SetActiveViewstate(ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW);
			break;
		default:
			return false;
		}

		this->GetBuzzer()->playSelectTone();
		return true;
	}

	return false;
}

inline bool PX4_TLMV_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (ti->GetTaskAssociation() == _HtaskAssociation && 
		(ti->GetViewStateAssociation() == ViewstateAlias::VIEWSTATEALIAS_STATUS_VIEW) |
		//(ti->GetViewStateAssociation() == ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW_TLMV) |
		(ti->GetViewStateAssociation() == ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW_TLMV) |
		(ti->GetViewStateAssociation() == ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW_TLMV) |
		(ti->GetViewStateAssociation() == ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW_TLMV)
	) { return true; }

	return false;
}
