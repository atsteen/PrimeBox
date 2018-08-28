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
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"

class PX4_PowerRelay_TaskHandler : public ITaskHandler
{
public:
	PX4_PowerRelay_TaskHandler(IPowerRelayArray * relayArray) : _relayArray(relayArray) {};
	~PX4_PowerRelay_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IPowerRelayArray * _relayArray;
};

inline bool PX4_PowerRelay_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (ti->GetTaskAssociation() == TaskAlias::TASKALIAS_DISABLE_POWER_RELAY || ti->GetTaskAssociation() == TaskAlias::TASKALIAS_ENABLE_POWER_RELAY)
	{
		return true;
	}

	return false;
}

inline bool PX4_PowerRelay_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }
	if (!_taskItem->GetScheduledTaskDetailContext()) { return false; }

	const int relayTargetIndex = *_taskItem->GetScheduledTaskDetailContext()->GetScheduledTaskrelayIndex();
	const ComponentAssociation association = *_taskItem->GetScheduledTaskDetailContext()->GetScheduledTaskrelayAssociation();

	if (_taskItem->GetTaskAssociation() == TASKALIAS_ENABLE_POWER_RELAY)
	{
		if(relayTargetIndex > -1){ _relayArray->EnableByIndex(relayTargetIndex); }
		else{ _relayArray->EnableAllTypesInGroup(association.typeAssociation, association.groupAssociation); }
	}
	else
	{
		if (relayTargetIndex > -1) { _relayArray->DisableByIndex(relayTargetIndex); }
		else { _relayArray->DisableAllTypesInGroup(association.typeAssociation, association.groupAssociation); }
	}

	return true;
}
