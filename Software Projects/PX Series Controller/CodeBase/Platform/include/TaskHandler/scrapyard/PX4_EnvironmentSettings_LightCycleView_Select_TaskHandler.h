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

class PX4_EnvironmentSettings_LightCycleView_Select_TaskHandler
	: public TaskHandler
{
public:
	PX4_EnvironmentSettings_LightCycleView_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //handle any viewstate element select
		){};

	~PX4_EnvironmentSettings_LightCycleView_Select_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;	
};

inline bool PX4_EnvironmentSettings_LightCycleView_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline bool PX4_EnvironmentSettings_LightCycleView_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		DataModel_PX4 * dm = &DataModel_PX4::GetInstance();

		switch (DataModel_PX4::GetInstance().GetSelectedViewstateElement()) {
		case SELECTABLE_BACK_ELEMENT:
			dm->SetSelectedViewstateElement(SELECTABLE_MENU_SELECT_ENVIRONMENT_SUNRISE_SUNSET_ELEMENT, true);
			dm->SetActiveViewstate(VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW);
			this->GetBuzzer()->playBackSelectTone();
			return true;

		case SELECTABLE_ENVIRONMENT_SUNRISE_SET_ELEMENT:
			dm->SetActiveViewstate(VIEWSTATEALIAS_INPUT_PROMPT_DEFAULT_SUNRISE_TIME);
			break;

		case SELECTABLE_ENVIRONMENT_SUNSET_SET_ELEMENT:
			dm->SetActiveViewstate(VIEWSTATEALIAS_INPUT_PROMPT_DEFAULT_SUNSET_TIME);
			break;

		case SELECTABLE_ENVIRONMENT_SUN_CYCLE_SET_ELEMENT:
			if (dm->GetLightCycleDefaultState()) { dm->SetLightCycleDefaultState(false); }
			else { dm->SetLightCycleDefaultState(true); }
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