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

class IModelEnvAirData
{
public:
	IModelEnvAirData() {};
	virtual ~IModelEnvAirData();

	virtual const double GetTemperatureFahrenheit() = 0;
	virtual const char * GetTemperatureFahrenheitText() = 0;
	virtual const float GetRelativeHumidity() = 0;
	virtual const char * GetRelativeHumidityText() = 0;

	virtual const int * const GetCirculationFanDutyCycleDay() = 0;
	virtual void SetCirculationFanDutyCycleDay(const int * const circFanDutyValueDay) = 0;
	virtual const int * const GetCirculationFanDutyCycleNight() = 0;
	virtual void SetCirculationFanDutyCycleNight(const int * const circFanDutyValueNight) = 0;
	virtual const int * const GetCirculationFanDutyCycleDuration() = 0;
	virtual void SetCirculationFanDutyCycleDuration(const int * const circFanCycleDurationValue) = 0;
	virtual const bool * const GetCirculationFanCycleDefaultState() = 0;
	virtual void SetCirculationFanCycleDefaultState(const bool * const defaultCircFanCycleStateValue) = 0;

	virtual const int * const GetExhaustFanDutyCycleDay() = 0;
	virtual void SetExhaustFanDutyCycleDay(const int * const exhaustFanDutyValueDay) = 0;
	virtual const int * const GetExhaustFanDutyCycleNight() = 0;
	virtual void SetExhaustFanDutyCycleNight(const int * const exhaustFanDutyValueNight) = 0;
	virtual const int * const GetExhaustFanDutyCycleDuration() = 0;
	virtual void SetExhaustFanDutyCycleDuration(const int * const exhaustFanCycleDurationValue) = 0;
	virtual const bool * const GetExhaustFanCycleDefaultState() = 0;
	virtual void SetExhaustFanCycleDefaultState(const bool * const defaultExhaustFanCycleStateValue) = 0;

	//todo... Transition to dynamic data
	virtual const int * const GetAlarmThresholdOverTempF() = 0;
	virtual void SetAlarmThresholdOverTempF(const int * const alarmThresholdOverTemp) = 0;
	virtual const int * const GetAlarmThresholdOverRH() = 0;
	virtual void SetAlarmThresholdOverRH(const int * const alarmThresholdOverRh) = 0;
};

inline IModelEnvAirData::~IModelEnvAirData() {}