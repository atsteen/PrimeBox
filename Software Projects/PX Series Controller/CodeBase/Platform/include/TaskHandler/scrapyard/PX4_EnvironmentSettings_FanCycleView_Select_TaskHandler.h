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

class PX4_EnvironmentSettings_FanCycleView_Select_TaskHandler
	: public TaskHandler
{
public:
	PX4_EnvironmentSettings_FanCycleView_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_AIR_CIRC_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //handle any viewstate element select
		){};

	~PX4_EnvironmentSettings_FanCycleView_Select_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;	
};

inline bool PX4_EnvironmentSettings_FanCycleView_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline bool PX4_EnvironmentSettings_FanCycleView_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		switch (DataModel_PX4::GetInstance().GetSelectedViewstateElement()) {
		case SELECTABLE_BACK_ELEMENT:
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(SELECTABLE_MENU_SELECT_ENVIRONMENT_AIR_CIRC_ELEMENT, true);
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW);
			this->GetBuzzer()->playBackSelectTone();
			return true;

		case SELECTABLE_ENVIRONMENT_DAY_FAN_DUTY_SET_ELEMENT:
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_INPUT_PROMPT_THREESEGMENT_DAYFANCYCLE);
			break;

		case SELECTABLE_ENVIRONMENT_NIGHT_FAN_DUTY_SET_ELEMENT:
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_INPUT_PROMPT_THREESEGMENT_NIGHTFANCYCLE);
			break;

		case SELECTABLE_ENVIRONMENT_FAN_CYCLE_SET_ELEMENT:
			DataModel_PX4::GetInstance().SetFanCycleDefaultState(!DataModel_PX4::GetInstance().GetFanCycleDefaultState());
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