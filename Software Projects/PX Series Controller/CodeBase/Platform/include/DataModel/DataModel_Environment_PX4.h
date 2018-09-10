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
#include "..\SharedStructure\Subject.h"
#include "..\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\SharedStructure\SharedInterface\IModelEnvLightData.h"
#include "..\SharedStructure\SharedInterface\Ipersistent.h"
#include "..\SharedStructure\SharedInterface\IAirSensor.h"

class DataModel_Environment_PX4 :
	public Subject,
	public Ipersistent,
	public IModelEnvAirData, 
	public IModelEnvLightData
{
public:
	DataModel_Environment_PX4(const PersistentComponentAlias, IPersistentDataCoordinator *, IAirSensor *);
	~DataModel_Environment_PX4() {};

	// Inherited via IModelEnvAirData
	virtual const int * const GetExhaustFanDutyCycleDay() override;
	virtual void SetExhaustFanDutyCycleDay(const int * const exFanDutyValueDayValue) override;
	virtual const int * const GetExhaustFanDutyCycleNight() override;
	virtual void SetExhaustFanDutyCycleNight(const int * const exFanDutyValueNightValue) override;
	virtual const int * const GetExhaustFanDutyCycleDuration() override;
	virtual void SetExhaustFanDutyCycleDuration(const int * const exFanDutyDurationValue) override;
	virtual const bool * const GetExhaustFanCycleDefaultState() override;
	virtual void SetExhaustFanCycleDefaultState(const bool * const defaultStateValue) override;

	virtual const int * const GetCirculationFanDutyCycleDay() override;
	virtual void SetCirculationFanDutyCycleDay(const int * const circFanDutyValueDayValue) override;
	virtual const int * const GetCirculationFanDutyCycleNight() override;
	virtual void SetCirculationFanDutyCycleNight(const int * const circFanDutyValueNightValue) override;
	virtual const int * const GetCirculationFanDutyCycleDuration() override;
	virtual void SetCirculationFanDutyCycleDuration(const int * const circFanDutyDurationValue) override;
	virtual const bool * const GetCirculationFanCycleDefaultState() override;
	virtual void SetCirculationFanCycleDefaultState(const bool * const defaultStateValue) override;

	virtual const int * const GetAlarmThresholdOverTempF() { return &_alarmThreshold_OverTempF; }
	virtual void SetAlarmThresholdOverTempF(const int * const alarmThresholdOverTemp) override;
	virtual const int * const GetAlarmThresholdOverRH() { return &_alarmThreshold_OverRH; }
	virtual void SetAlarmThresholdOverRH(const int * const alarmThresholdOverRh) override;

	virtual const double GetTemperatureFahrenheit() override;
	virtual const char * GetTemperatureFahrenheitText() override;
	virtual const float GetRelativeHumidity() override;
	virtual const char * GetRelativeHumidityText() override;

	// Inherited via IModelEnvLightData
	virtual const bool * const GetLightCycleDefaultState() override { return &_lightCycleDefaultState; }
	virtual void SetLightCycleDefaultState(const bool * const lightCycleDefaultState) override;
	virtual const TimeSignature * const GetDefaultSunriseTime() override { return &_defaultSunriseTime; }
	virtual void SetDefaultSunriseTime(const TimeSignature * const defaultSunriseTime) override;
	virtual const TimeSignature * const GetDefaultSunsetTime() override { return &_defaultSunsetTime; }
	virtual void SetDefaultSunsetTime(const TimeSignature * const defaultSunsetTime) override;

protected:
	// Inherited via Ipersistent
	virtual const PersistentComponentAlias GetComponentAlias() override;
	virtual void RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;
	virtual void UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;	

private:
	IAirSensor * _airSensor = {};

	int _exhaustFanDutyCycleDuration = DEFAULT_EXHAUST_FAN_DUTY_CYCLE_DURATION;
	int _exhaustFanDutyCycleDay = DEFAULT_EXHAUST_FAN_DUTY_CYCLE_DAY;
	int _exhaustFanDutyCycleNight = DEFAULT_EXHAUST_FAN_DUTY_CYCLE_NIGHT;
	bool _exhaustFanCycleDefaultState = DEFAULT_EXHAUST_FAN_DUTY_CYCLE_STATE;

	int _circulationFanDutyCycleDuration = DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_DURATION;
	int _circulationFanDutyCycleDay = DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_DAY;
	int _circulationFanDutyCycleNight = DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_NIGHT;
	bool _circulationFanCycleDefaultState = DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_STATE;
	
	bool _lightCycleDefaultState = true;
	
	int _alarmThreshold_OverTempF = 85;
	int _alarmThreshold_OverTempF_MIN = 32;
	int _alarmThreshold_OverTempF_MAX = 120;
	int _alarmThreshold_OverRH = 70;
	int _alarmThreshold_OverRH_MIN = 0;
	int _alarmThreshold_OverRH_MAX = 100;
	const int _fanDutyCycle_MAX = 100;
	const int _fanDutyCycle_MIN = 1;
	TimeSignature _defaultSunriseTime = { 0,0,0,6 };
	TimeSignature _defaultSunsetTime = { 0,0,0,22 };
};