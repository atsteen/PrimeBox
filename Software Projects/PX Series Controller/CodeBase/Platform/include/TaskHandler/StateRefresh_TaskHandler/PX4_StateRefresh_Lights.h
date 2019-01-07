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
#include "..\..\SharedStructure\SharedInterface\IModelEnvLightData.h"
#include "..\..\SharedStructure\SharedInterface\IRtcLogger.h"

class PX4_StateRefresh_Lights : public ITaskHandler
{
public:
	PX4_StateRefresh_Lights(IPowerRelayArray * powerRelayArray, IModelEnvLightData * lightData, IRtcLogger * rtcLogger)
		: _powerRelayArray(powerRelayArray), _lightData(lightData), _rtcLogger(rtcLogger) {};

	~PX4_StateRefresh_Lights() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IPowerRelayArray * _powerRelayArray;
	IModelEnvLightData * _lightData;
	IRtcLogger * _rtcLogger;
};

inline bool PX4_StateRefresh_Lights::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }
	if (!*_lightData->GetLightCycleDefaultState()) { return true; }  // return if default light mode is disabled (do not process unscheduled light change)

	TimeSignature const * timeNow = &_rtcLogger->CurrentTime();

	if (timeNow->secondsInDay() > _lightData->GetDefaultSunriseTime()->secondsInDay() && timeNow->secondsInDay() < _lightData->GetDefaultSunsetTime()->secondsInDay())
	{
		_powerRelayArray->EnableAllTypesInGroup(ComponentTypeAssociation::LIGHT_PRIMARY, ComponentGroupAssociation::GROUP_A);
	}
	else
	{
		_powerRelayArray->DisableAllTypesInGroup(ComponentTypeAssociation::LIGHT_PRIMARY, ComponentGroupAssociation::GROUP_A);
	}

	return true;
}

inline bool PX4_StateRefresh_Lights::_CanHandleTask(TaskItem * _taskItem)
{
	if (_taskItem->GetTaskAssociation() == TaskAlias::TASKALIAS_REFRESH_STATE_LIGHT) { return true; }
	return false;
}

inline const bool PX4_StateRefresh_Lights::FlagStateChange()
{
	return true;
}