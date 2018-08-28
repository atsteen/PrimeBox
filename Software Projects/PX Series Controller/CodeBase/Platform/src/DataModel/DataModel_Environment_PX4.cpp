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

#include "..\..\include\DataModel\DataModel_Environment_PX4.h"

DataModel_Environment_PX4::DataModel_Environment_PX4(const PersistentComponentAlias ca, IPersistentDataCoordinator * pdc, IAirSensor * airSensor) :
	Ipersistent(ca, pdc), _airSensor(airSensor) { this->RestorePersistentData(_persistentDataCoordinator); }

const int * const DataModel_Environment_PX4::GetExhaustFanDutyCycleDay()
{
	return &_exhaustFanDutyCycleDay;
}

void DataModel_Environment_PX4::SetExhaustFanDutyCycleDay(const int * const exFanDutyValueDayValue)
{
	_exhaustFanDutyCycleDay = *exFanDutyValueDayValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const int * const DataModel_Environment_PX4::GetExhaustFanDutyCycleNight()
{
	return &_exhaustFanDutyCycleNight;
}

void DataModel_Environment_PX4::SetExhaustFanDutyCycleNight(const int * const exFanDutyValueNightValue)
{
	_exhaustFanDutyCycleNight = *exFanDutyValueNightValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const int * const DataModel_Environment_PX4::GetExhaustFanDutyCycleDuration()
{
	return &_exhaustFanDutyCycleDuration;
}

void DataModel_Environment_PX4::SetExhaustFanDutyCycleDuration(const int * const exFanDutyDurationValue)
{
	_exhaustFanDutyCycleDuration = *exFanDutyDurationValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const bool * const DataModel_Environment_PX4::GetExhaustFanCycleDefaultState()
{
	return &_exhaustFanCycleDefaultState;
}

void DataModel_Environment_PX4::SetExhaustFanCycleDefaultState(const bool * const defaultStateValue)
{
	_exhaustFanCycleDefaultState = *defaultStateValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const int * const DataModel_Environment_PX4::GetCirculationFanDutyCycleDay()
{
	return &_circulationFanDutyCycleDay;
}

void DataModel_Environment_PX4::SetCirculationFanDutyCycleDay(const int * const circFanDutyValueDayValue)
{
	_circulationFanDutyCycleDay = *circFanDutyValueDayValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const int * const DataModel_Environment_PX4::GetCirculationFanDutyCycleNight()
{
	return &_circulationFanDutyCycleNight;
}

void DataModel_Environment_PX4::SetCirculationFanDutyCycleNight(const int * const circFanDutyValueNightValue)
{
	_circulationFanDutyCycleNight = *circFanDutyValueNightValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const int * const DataModel_Environment_PX4::GetCirculationFanDutyCycleDuration()
{
	return &_circulationFanDutyCycleDuration;
}

void DataModel_Environment_PX4::SetCirculationFanDutyCycleDuration(const int * const circFanDutyDurationValue)
{
	_circulationFanDutyCycleDuration = *circFanDutyDurationValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const bool * const DataModel_Environment_PX4::GetCirculationFanCycleDefaultState()
{
	return &_circulationFanCycleDefaultState;
}

void DataModel_Environment_PX4::SetCirculationFanCycleDefaultState(const bool * const defaultStateValue)
{
	_circulationFanCycleDefaultState = *defaultStateValue;
	this->UpdatePersistentData(_persistentDataCoordinator);
}

void DataModel_Environment_PX4::SetAlarmThresholdOverTempF(const int * const alarmThresholdOverTemp)
{
	_alarmThreshold_OverTempF = *alarmThresholdOverTemp;
	this->UpdatePersistentData(_persistentDataCoordinator);
	//this->notifyObservers();
}

void DataModel_Environment_PX4::SetAlarmThresholdOverRH(const int * const alarmThresholdOverRh)
{
	_alarmThreshold_OverRH = *alarmThresholdOverRh;
	this->UpdatePersistentData(_persistentDataCoordinator);
	//this->notifyObservers();
}

const double DataModel_Environment_PX4::GetTemperatureFahrenheit()
{
	return _airSensor->CurrentTemperatureFahrenheit();
}

const char * DataModel_Environment_PX4::GetTemperatureFahrenheitText()
{
	return _airSensor->CurrentTemperatureFahrenheitText();
}

const float DataModel_Environment_PX4::GetRelativeHumidity()
{
	return _airSensor->CurrentRelativeHumidity();
}

const char * DataModel_Environment_PX4::GetRelativeHumidityText()
{
	return _airSensor->CurrentRelativeHumidityText();
}

void DataModel_Environment_PX4::SetLightCycleDefaultState(const bool * const lightCycleDefaultState)
{
	_lightCycleDefaultState = *lightCycleDefaultState;
	//this->notifyObservers();
	this->UpdatePersistentData(_persistentDataCoordinator);
}

void DataModel_Environment_PX4::SetDefaultSunriseTime(const TimeSignature * const defaultSunriseTime)
{
	_defaultSunriseTime.SetSignature(
		defaultSunriseTime->year(),
		defaultSunriseTime->month(),
		defaultSunriseTime->day(),
		defaultSunriseTime->hour(),
		defaultSunriseTime->minute(),
		defaultSunriseTime->second()
	);

	//this->notifyObservers();
	this->UpdatePersistentData(_persistentDataCoordinator);
}

void DataModel_Environment_PX4::SetDefaultSunsetTime(const TimeSignature * const defaultSunsetTime)
{
	_defaultSunsetTime.SetSignature(
		defaultSunsetTime->year(),
		defaultSunsetTime->month(),
		defaultSunsetTime->day(),
		defaultSunsetTime->hour(),
		defaultSunsetTime->minute(),
		defaultSunsetTime->second()
	);

	//this->notifyObservers();
	this->UpdatePersistentData(_persistentDataCoordinator);
}

// Inherited via Ipersistent
const PersistentComponentAlias DataModel_Environment_PX4::GetComponentAlias()
{
	return this->_componentAlias;
}

void DataModel_Environment_PX4::RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent)
{
	if (!persistentDataAgent)
	{
		return; //TODO add exception handling for null ref
	}

	int restoreVal = INT32_MIN;

	
	persistentDataAgent->ReadPersistentItem(&_exhaustFanCycleDefaultState, PersistentDataAlias::EXHAUST_FANS_STATE_AUTO_CYCLE);
	
	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DURATION);
	if (restoreVal >= 1 && restoreVal <= DEFAULT_EXHAUST_FAN_DUTY_CYCLE_DURATION_MAX) { _exhaustFanDutyCycleDuration = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DAY);
	if (restoreVal > _fanDutyCycle_MIN && restoreVal < _fanDutyCycle_MAX) { _exhaustFanDutyCycleDay = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_NIGHT);
	if (restoreVal > _fanDutyCycle_MIN && restoreVal < _fanDutyCycle_MAX) { _exhaustFanDutyCycleNight = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&_circulationFanCycleDefaultState, PersistentDataAlias::CIRCULATION_FANS_STATE_AUTO_CYCLE);

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DURATION);
	if (restoreVal >= 1 && restoreVal <= DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_DURATION_MAX) { _circulationFanDutyCycleDuration = restoreVal; }	
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DAY);
	if (restoreVal > _fanDutyCycle_MIN && restoreVal < _fanDutyCycle_MAX) { _circulationFanDutyCycleDay = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_NIGHT);
	if (restoreVal > _fanDutyCycle_MIN && restoreVal < _fanDutyCycle_MAX) { _circulationFanDutyCycleNight = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::ALARM_THRESHOLD_OVER_TEMP);
	if (restoreVal > _alarmThreshold_OverTempF_MIN && restoreVal < _alarmThreshold_OverTempF_MAX) { _alarmThreshold_OverTempF = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&restoreVal, PersistentDataAlias::ALARM_THRESHOLD_OVER_RH);
	if (restoreVal > _alarmThreshold_OverRH_MIN && restoreVal < _alarmThreshold_OverRH_MAX) { _alarmThreshold_OverRH = restoreVal; }
	restoreVal = INT32_MIN;

	persistentDataAgent->ReadPersistentItem(&_lightCycleDefaultState, PersistentDataAlias::LIGHTS_STATE_AUTO_CYCLE);
	persistentDataAgent->ReadPersistentItem(&_defaultSunriseTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNRISE);
	persistentDataAgent->ReadPersistentItem(&_defaultSunsetTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNSET);
}

void DataModel_Environment_PX4::UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent)
{
	if (!persistentDataAgent)
	{
		return;
	}
	
	persistentDataAgent->WritePersistentItem(&_exhaustFanCycleDefaultState, PersistentDataAlias::EXHAUST_FANS_STATE_AUTO_CYCLE);
	persistentDataAgent->WritePersistentItem(&_exhaustFanDutyCycleDay, PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DAY);
	persistentDataAgent->WritePersistentItem(&_exhaustFanDutyCycleNight, PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_NIGHT);
	persistentDataAgent->WritePersistentItem(&_exhaustFanDutyCycleDuration, PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DURATION);

	persistentDataAgent->WritePersistentItem(&_circulationFanCycleDefaultState, PersistentDataAlias::CIRCULATION_FANS_STATE_AUTO_CYCLE);
	persistentDataAgent->WritePersistentItem(&_circulationFanDutyCycleDay, PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DAY);
	persistentDataAgent->WritePersistentItem(&_circulationFanDutyCycleNight, PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_NIGHT);
	persistentDataAgent->WritePersistentItem(&_circulationFanDutyCycleDuration, PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DURATION);

	persistentDataAgent->WritePersistentItem(&_alarmThreshold_OverTempF, PersistentDataAlias::ALARM_THRESHOLD_OVER_TEMP);
	persistentDataAgent->WritePersistentItem(&_alarmThreshold_OverRH, PersistentDataAlias::ALARM_THRESHOLD_OVER_RH);
	persistentDataAgent->WritePersistentItem(&_lightCycleDefaultState, PersistentDataAlias::LIGHTS_STATE_AUTO_CYCLE);
	persistentDataAgent->WritePersistentItem(&_defaultSunriseTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNRISE);
	persistentDataAgent->WritePersistentItem(&_defaultSunsetTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNSET);
}

