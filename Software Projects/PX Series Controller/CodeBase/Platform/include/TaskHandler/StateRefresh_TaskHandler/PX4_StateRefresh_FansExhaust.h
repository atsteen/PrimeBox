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

#include "..\..\..\..\Configurations\PX4_Config.h"
#include "..\..\SharedStructure\SharedInterface\ITaskHandler.h"
#include "..\..\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\..\SharedStructure\SharedInterface\IModelSystemData.h"
#include "..\..\SharedStructure\SharedInterface\IModelEnvLightData.h"
#include "..\..\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"

class PX4_StateRefresh_FansExhaust : public ITaskHandler
{
public:
	PX4_StateRefresh_FansExhaust(IModelSystemData * systemData, IModelEnvAirData * environmentData, IModelEnvLightData * lightData, IRtcLogger * rtcLogger, IPowerRelayArray * powerRelayArray)
		: _systemData(systemData), _environmentData(environmentData), _lightData(lightData), _rtcLogger(rtcLogger), _powerRelayArray(powerRelayArray){};

	~PX4_StateRefresh_FansExhaust() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelSystemData * _systemData;
	IModelEnvAirData * _environmentData;
	IModelEnvLightData * _lightData;
	IRtcLogger * _rtcLogger;
	IPowerRelayArray * _powerRelayArray;
};

inline bool PX4_StateRefresh_FansExhaust::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	if (_environmentData->GetAlarmState(EnvAirDataAlarmTypes::TEMP_OVER_THRESH)) {
		_powerRelayArray->EnableAllTypesInGroup(ComponentTypeAssociation::FAN_EXHAUST, ComponentGroupAssociation::GROUP_A);
		return true;
	}
	else if (!*_environmentData->GetExhaustFanCycleDefaultState()) {
		// todo... no restore capability requires GROUP_A to function as alarm event items only, no way to restore non-default state
		_powerRelayArray->DisableAllTypesInGroup(ComponentTypeAssociation::FAN_EXHAUST, ComponentGroupAssociation::GROUP_A); 
		return true;
	}

	TimeSignature const * timeNow = &_rtcLogger->CurrentTime();
	int currentDutyCycleDepthMins = (timeNow->secondsInDay() / 60) % *_environmentData->GetExhaustFanDutyCycleDuration();
	int activeDutyCycleDepthMins = 0;	
	
	if (timeNow->secondsInDay() > _lightData->GetDefaultSunriseTime()->secondsInDay() && timeNow->secondsInDay() < _lightData->GetDefaultSunsetTime()->secondsInDay())
	{
		activeDutyCycleDepthMins = (*_environmentData->GetExhaustFanDutyCycleDuration() * *_environmentData->GetExhaustFanDutyCycleDay()) / 100;
	}
	else // use night duty cycle
	{
		activeDutyCycleDepthMins = (*_environmentData->GetExhaustFanDutyCycleDuration() * *_environmentData->GetExhaustFanDutyCycleNight()) / 100;
	}

	if (currentDutyCycleDepthMins < activeDutyCycleDepthMins)
	{
		_powerRelayArray->EnableAllTypesInGroup(ComponentTypeAssociation::FAN_EXHAUST, ComponentGroupAssociation::GROUP_A);
	}
	else { _powerRelayArray->DisableAllTypesInGroup(ComponentTypeAssociation::FAN_EXHAUST, ComponentGroupAssociation::GROUP_A); }

	return true;
}

inline bool PX4_StateRefresh_FansExhaust::_CanHandleTask(TaskItem * _taskItem)
{
	if (_taskItem->GetTaskAssociation() == TaskAlias::TASKALIAS_REFRESH_STATE_EXHAUST_FANS) { return true; }
	return false;
}

inline const bool PX4_StateRefresh_FansExhaust::FlagStateChange()
{
	return true;
}