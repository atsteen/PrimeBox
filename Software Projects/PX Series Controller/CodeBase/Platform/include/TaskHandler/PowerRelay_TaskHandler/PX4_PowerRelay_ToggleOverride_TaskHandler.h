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

#include "PX4_PowerRelay_TaskHandler.h"
#include "..\..\SharedStructure\PersistentData\Ipersistent.h"
#include "..\..\ComponentModuleGroup\ComponentModuleGroup_PX4.h"

class PX4_PowerRelay_ToggleOverride_TaskHandler
	: public PX4_PowerRelay_TaskHandler, public Ipersistent
{
public:
	PX4_PowerRelay_ToggleOverride_TaskHandler()
		: PX4_PowerRelay_TaskHandler(
			TaskAlias::TASKALIAS_NOT_SET,
			ViewstateAlias::VIEWSTATEALIAS_NOT_SET,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET
		){};

	~PX4_PowerRelay_ToggleOverride_TaskHandler() {};

	// Inherited via PX4_PowerRelay_TaskHandler
	virtual bool HandleTask(TaskItem *) override;

protected:

	ComponentModuleGroup_PX4 _moduleGroup;

	// Inherited via PX4_PowerRelay_TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;

	// Inherited via Ipersistent
	virtual void RestorePersistentData() override {};
	virtual void UpdatePersistentData() override;
};

inline bool PX4_PowerRelay_ToggleOverride_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		switch (ti->GetTaskAssociation()) {
		case TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_PUMP :
			_moduleGroup.PumpRelay()->isInOverride = !_moduleGroup.PumpRelay()->isInOverride;
			break;
		case TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_FAN :
			_moduleGroup.FanRelay()->isInOverride = !_moduleGroup.FanRelay()->isInOverride;
			break;
		case TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_LIGHTS :
			_moduleGroup.LightRelayA()->isInOverride = !_moduleGroup.LightRelayA()->isInOverride;
			_moduleGroup.LightRelayB()->isInOverride = !_moduleGroup.LightRelayB()->isInOverride;
			break;
		default:
			break;
		}

		UpdatePersistentData();
		return true;
	}

	return false;
}

inline bool PX4_PowerRelay_ToggleOverride_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (ti->GetTaskAssociation() == TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_PUMP ||
		ti->GetTaskAssociation() == TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_FAN ||
		ti->GetTaskAssociation() == TASKALIAS_TOGGLE_OVERRIDE_POWER_RELAY_LIGHTS
	) { return true; }

	return false;
}

inline void PX4_PowerRelay_ToggleOverride_TaskHandler::UpdatePersistentData()
{
		NvMemoryManager()->WritePersistentItem(&_moduleGroup.PumpRelay()->isInOverride, PersistentDataAlias::POWER_RELAY_OVERRIDE_STATE_CHANNEL_A);
		NvMemoryManager()->WritePersistentItem(&_moduleGroup.FanRelay()->isInOverride, PersistentDataAlias::POWER_RELAY_OVERRIDE_STATE_CHANNEL_B);
		NvMemoryManager()->WritePersistentItem(&_moduleGroup.LightRelayA()->isInOverride, PersistentDataAlias::POWER_RELAY_OVERRIDE_STATE_CHANNEL_C);
		NvMemoryManager()->WritePersistentItem(&_moduleGroup.LightRelayB()->isInOverride, PersistentDataAlias::POWER_RELAY_OVERRIDE_STATE_CHANNEL_D);
}
