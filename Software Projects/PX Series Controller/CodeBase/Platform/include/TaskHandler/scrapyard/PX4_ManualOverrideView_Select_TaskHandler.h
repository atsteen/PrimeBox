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
#include "..\..\SharedStructure\TaskItemPool.h"
#include "..\..\ComponentModuleGroup\ComponentModuleGroup_PX4.h"

#define SELECTABLE_ELEMENT_COUNT 4

class PX4_ManualOverrideView_Select_TaskHandler
	: public TaskHandler
{
public:
	PX4_ManualOverrideView_Select_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT,
			ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET
		) {};

	~PX4_ManualOverrideView_Select_TaskHandler() {};

	void QueueOverrideTaskItem(const TaskAlias);

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:
	SelectableViewstateElementAlias _selectableOrder[SELECTABLE_ELEMENT_COUNT]{
		SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT,
		SelectableViewstateElementAlias::SELECTABLE_PUMP_OVERRIDE_ELEMENT,
		SelectableViewstateElementAlias::SELECTABLE_FAN_OVERRIDE_ELEMENT,
		SelectableViewstateElementAlias::SELECTABLE_LIGHTS_OVERRIDE_ELEMENT
	};

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;
};

inline bool PX4_ManualOverrideView_Select_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{
		return true;
	}

	return false;
}

inline void PX4_ManualOverrideView_Select_TaskHandler::QueueOverrideTaskItem(const TaskAlias ta)
{
	TaskItem *overrideTaskItem = TaskItemPool::GetInstance().GetNewTaskItem();
	overrideTaskItem->SetTaskAlias(ta);
	TaskItemPool::GetInstance().QueueTaskItem(overrideTaskItem);
}

inline bool PX4_ManualOverrideView_Select_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		ComponentModuleGroup_PX4 _moduleGroup;
		bool toggleOverrideStateFirst;

		switch (DataModel_PX4::GetInstance().GetSelectedViewstateElement()) {
		case SELECTABLE_BACK_ELEMENT:
			DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_STATUS_VIEW);
			this->GetBuzzer()->playBackSelectTone();
			return true;
			
		case SELECTABLE_PUMP_OVERRIDE_ELEMENT:
			toggleOverrideStateFirst = _moduleGroup.PumpRelay()->IsInOverride();
			if(toggleOverrideStateFirst) { QueueOverrideTaskItem(TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_PUMP); }

			if(_moduleGroup.PumpRelay()->IsEnabled()){ QueueOverrideTaskItem(TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_PUMP); }
			else{ QueueOverrideTaskItem(TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_PUMP); }

			if(!toggleOverrideStateFirst) { QueueOverrideTaskItem(TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_PUMP); }
			break;

		case SELECTABLE_FAN_OVERRIDE_ELEMENT :
			toggleOverrideStateFirst = _moduleGroup.FanRelay()->IsInOverride();
			if (toggleOverrideStateFirst) { QueueOverrideTaskItem(TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_FAN); }

			if (_moduleGroup.FanRelay()->IsEnabled()) { QueueOverrideTaskItem(TASKALIAS_DISABLE_POWER_RELAY_FAN); }
			else { QueueOverrideTaskItem(TASKALIAS_ENABLE_POWER_RELAY_FAN); }

			if (!toggleOverrideStateFirst) { QueueOverrideTaskItem(TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_FAN); }
			break;

		case SELECTABLE_LIGHTS_OVERRIDE_ELEMENT :
			toggleOverrideStateFirst = _moduleGroup.LightRelayA()->IsInOverride();
			if (toggleOverrideStateFirst) { QueueOverrideTaskItem(TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_LIGHTS); }

			if (_moduleGroup.LightRelayA()->IsEnabled()) { QueueOverrideTaskItem(TASKALIAS_DISABLE_POWER_RELAY_LIGHTS); }
			else { QueueOverrideTaskItem(TASKALIAS_ENABLE_POWER_RELAY_LIGHTS); }

			if (!toggleOverrideStateFirst) { QueueOverrideTaskItem(TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_LIGHTS); }
			break;

		default :
			//todo... report invalid selecteditem value
			return false;
		}

		this->GetBuzzer()->playSelectTone();
		return true;
	}

	return false;
}