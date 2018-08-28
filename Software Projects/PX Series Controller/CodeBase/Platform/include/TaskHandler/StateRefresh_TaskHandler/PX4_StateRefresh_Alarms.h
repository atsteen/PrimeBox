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
#include "..\..\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\..\SharedStructure\SharedInterface\IModelSystemData.h"
#include "..\..\SharedStructure\SharedInterface\IRtcLogger.h"

class PX4_StateRefresh_Alarms : public ITaskHandler
{
public:
	PX4_StateRefresh_Alarms(IModelSystemData * systemData, IModelEnvAirData * environmentData, IRtcLogger * rtcLogger)
		: _systemData(systemData), _environmentData(environmentData), _rtcLogger(rtcLogger){};

	~PX4_StateRefresh_Alarms() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelSystemData * _systemData;
	IModelEnvAirData * _environmentData;
	IRtcLogger * _rtcLogger;
};

inline bool PX4_StateRefresh_Alarms::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	if (_systemData->GetLogAlarmDefaultState())
	{
		if (_environmentData->GetTemperatureFahrenheit() >= *_environmentData->GetAlarmThresholdOverTempF())
		{
			_rtcLogger->LogEvent(EVENT_TEXT_ALARM_OVERTEMP);
		}

		if (_environmentData->GetRelativeHumidity() >= *_environmentData->GetAlarmThresholdOverRH())
		{
			_rtcLogger->LogEvent(EVENT_TEXT_ALARM_OVERRH);
		}
	}

	return true;
}

inline bool PX4_StateRefresh_Alarms::_CanHandleTask(TaskItem * _taskItem)
{
	if (_taskItem->GetTaskAssociation() == TaskAlias::TASKALIAS_REFRESH_STATE_SYSTEM_ALARMS) { return true; }
	return false;
}

inline const bool PX4_StateRefresh_Alarms::FlagStateChange()
{
	return true;
}