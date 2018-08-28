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

class PX4_InputPrompt_DefaultSunsetView_Select_TaskHandler
	: public TaskHandler
{
public:
	PX4_InputPrompt_DefaultSunsetView_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_DEFAULT_SUNSET_TIME,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //Leave SELECTABLE_ELEMENT_NOT_SET to handle all viewstate selections
		){};

	~PX4_InputPrompt_DefaultSunsetView_Select_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;	
};

inline bool PX4_InputPrompt_DefaultSunsetView_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline bool PX4_InputPrompt_DefaultSunsetView_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		switch (DataModel_PX4::GetInstance().GetSelectedViewstateElement()) {
		case SELECTABLE_BACK_ELEMENT:
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(SELECTABLE_ENVIRONMENT_SUNSET_SET_ELEMENT, true);
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW);
			this->GetBuzzer()->playBackSelectTone();
			return true;

		case SELECTABLE_SETTIME_HH_ELEMENT:
		case SELECTABLE_SETTIME_MM_ELEMENT:
			DataModel_PX4::GetInstance().SetPromptInputModalState(!DataModel_PX4::GetInstance().GetPromptInputModalState());
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