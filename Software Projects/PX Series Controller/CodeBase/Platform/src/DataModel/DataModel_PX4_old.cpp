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

#include "..\..\include\DataModel\DataModel_PX4.h"

volatile TaskAlias FlaggedTask;

void DataModel_PX4::SetLightCycleDefaultState(bool state)
{
	_lightCycleDefaultState = state;
	UpdatePersistentData();
}

void DataModel_PX4::SetFanCycleDefaultState(bool state)
{
	_fanCycleDefaultState = state;
	UpdatePersistentData();
}

void DataModel_PX4::SetLogAlarmDefaultState(bool state)
{
	_logAlarmDefaultState = state;
	UpdatePersistentData();
}

void DataModel_PX4::AdjustDefaultSunriseTimeHH(int hh)
{
	_defaultSunriseTime.AdjustHH(hh);
	UpdatePersistentData();
}

void DataModel_PX4::AdjustDefaultSunriseTimeMM(int mm)
{
	_defaultSunriseTime.AdjustMM(mm);
	UpdatePersistentData();
}

void DataModel_PX4::AdjustDefaultSunsetTimeHH(int hh)
{
	_defaultSunsetTime.AdjustHH(hh);
	UpdatePersistentData();
}

void DataModel_PX4::AdjustDefaultSunsetTimeMM(int mm)
{
	_defaultSunsetTime.AdjustMM(mm);
	UpdatePersistentData();
}

void DataModel_PX4::AdjustFanDutyCycleDay(int fdc)
{
	if ((fdc + _fanDutyCycleDay) <= _fanDutyCycle_MIN) { _fanDutyCycleDay = _fanDutyCycle_MIN; return; }
	if ((fdc + _fanDutyCycleDay) >= _fanDutyCycle_MAX) { _fanDutyCycleDay = _fanDutyCycle_MAX; return; }

	_fanDutyCycleDay += fdc;
	UpdatePersistentData();
}

void DataModel_PX4::AdjustFanDutyCycleNight(int fdc)
{
	if ((fdc + _fanDutyCycleNight) <= _fanDutyCycle_MIN) { _fanDutyCycleNight = _fanDutyCycle_MIN; return; }
	if ((fdc + _fanDutyCycleNight) >= _fanDutyCycle_MAX) { _fanDutyCycleNight = _fanDutyCycle_MAX; return; }

	_fanDutyCycleNight += fdc;
	UpdatePersistentData();
}

void DataModel_PX4::AdjustAlarmThresholdOverTempF(int temp)
{
	if ((temp + _alarmThreshold_OverTempF) <= _alarmThreshold_OverTempF_MIN) { _alarmThreshold_OverTempF = _alarmThreshold_OverTempF_MIN; }
	if ((temp + _alarmThreshold_OverTempF) >= _alarmThreshold_OverTempF_MAX) { _alarmThreshold_OverTempF = _alarmThreshold_OverTempF_MAX; }

	_alarmThreshold_OverTempF += temp;
	UpdatePersistentData();
}

void DataModel_PX4::AdjustAlarmThresholdOverRH(int rh)
{
	if ((rh + _alarmThreshold_OverRH) <= _alarmThreshold_OverRH_MIN) { _alarmThreshold_OverRH = _alarmThreshold_OverRH_MIN; }
	if ((rh + _alarmThreshold_OverRH) >= _alarmThreshold_OverRH_MAX) { _alarmThreshold_OverRH = _alarmThreshold_OverRH_MAX; }

	_alarmThreshold_OverRH += rh;
	UpdatePersistentData();
}

const ViewstateAlias DataModel_PX4::GetActiveViewstate()
{
	return _activeView;
}

void DataModel_PX4::SetActiveViewstate(ViewstateAlias va)
{
	_activeView = va;
	notifyObservers();
}

const SelectableViewstateElementAlias DataModel_PX4::GetSelectedViewstateElement()
{
	return _selectedViewstateElement;
}

void DataModel_PX4::SetSelectedViewstateElement(SelectableViewstateElementAlias sve, const bool suppressNotify)
{
	_selectedViewstateElement = sve;
	if (!suppressNotify) { notifyObservers(); }
}

void DataModel_PX4::RestorePersistentData()
{
	if (!_nvMemoryManager)
	{
		return;
	}

	int restoreVal = INT32_MIN;

	_nvMemoryManager->ReadPersistentItem(&_lightCycleDefaultState, PersistentDataAlias::LIGHTS_STATE_AUTO_CYCLE);
	_nvMemoryManager->ReadPersistentItem(&_fanCycleDefaultState, PersistentDataAlias::FANS_STATE_AUTO_CYCLE);
	_nvMemoryManager->ReadPersistentItem(&_logAlarmDefaultState, PersistentDataAlias::ALARM_LOGFULL_STATE);

	_nvMemoryManager->ReadPersistentItem(&restoreVal, PersistentDataAlias::FANS_STATE_DUTY_CYCLE_DAY);
	if(restoreVal > _fanDutyCycle_MIN && restoreVal < _fanDutyCycle_MAX){_fanDutyCycleDay = restoreVal;}
	restoreVal = INT32_MIN;

	_nvMemoryManager->ReadPersistentItem(&restoreVal, PersistentDataAlias::FANS_STATE_DUTY_CYCLE_NIGHT);
	if(restoreVal > _fanDutyCycle_MIN && restoreVal < _fanDutyCycle_MAX){_fanDutyCycleNight = restoreVal;}
	restoreVal = INT32_MIN;

	_nvMemoryManager->ReadPersistentItem(&restoreVal, PersistentDataAlias::ALARM_THRESHOLD_OVER_TEMP);
	if(restoreVal > _alarmThreshold_OverTempF_MIN && restoreVal < _alarmThreshold_OverTempF_MAX){_alarmThreshold_OverTempF = restoreVal;}
	restoreVal = INT32_MIN;

	_nvMemoryManager->ReadPersistentItem(&restoreVal, PersistentDataAlias::ALARM_THRESHOLD_OVER_RH);
	if(restoreVal > _alarmThreshold_OverRH_MIN && restoreVal < _alarmThreshold_OverRH_MAX){_alarmThreshold_OverRH = restoreVal;}
	restoreVal = INT32_MIN;

	_nvMemoryManager->ReadPersistentItem(&_defaultSunriseTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNRISE);
	_nvMemoryManager->ReadPersistentItem(&_defaultSunsetTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNSET);
	_nvMemoryManager->ReadPersistentItem(&_sysSKU, PersistentDataAlias::SYSTEM_SKU);
	_nvMemoryManager->ReadPersistentItem(&_scheduledTasks, PersistentDataAlias::SCHEDULED_TASK_POOL);

	_nvMemoryManager->ReadPersistentItem(&_callstackLastObjID, PersistentDataAlias::LOGGER_LAST_CALLSTACK_PUSH_ID);
}

void DataModel_PX4::UpdatePersistentData()
{
	if (!_nvMemoryManager)
	{
		return;
	}

	_nvMemoryManager->WritePersistentItem(&_lightCycleDefaultState, PersistentDataAlias::LIGHTS_STATE_AUTO_CYCLE);
	_nvMemoryManager->WritePersistentItem(&_fanCycleDefaultState, PersistentDataAlias::FANS_STATE_AUTO_CYCLE);
	_nvMemoryManager->WritePersistentItem(&_logAlarmDefaultState, PersistentDataAlias::ALARM_LOGFULL_STATE);
	_nvMemoryManager->WritePersistentItem(&_fanDutyCycleDay, PersistentDataAlias::FANS_STATE_DUTY_CYCLE_DAY);
	_nvMemoryManager->WritePersistentItem(&_fanDutyCycleNight, PersistentDataAlias::FANS_STATE_DUTY_CYCLE_NIGHT);
	_nvMemoryManager->WritePersistentItem(&_alarmThreshold_OverTempF, PersistentDataAlias::ALARM_THRESHOLD_OVER_TEMP);
	_nvMemoryManager->WritePersistentItem(&_alarmThreshold_OverRH, PersistentDataAlias::ALARM_THRESHOLD_OVER_RH);
	_nvMemoryManager->WritePersistentItem(&_defaultSunriseTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNRISE);
	_nvMemoryManager->WritePersistentItem(&_defaultSunsetTime, PersistentDataAlias::LIGHTS_STATE_AUTO_SUNSET);
	_nvMemoryManager->WritePersistentItem(&_sysSKU, PersistentDataAlias::SYSTEM_SKU);
}

void DataModel_PX4::AttachNvMemoryManager(ComponentModule_NvMemoryManager * nvMemoryManager)
{
	_nvMemoryManager = nvMemoryManager;
}

DataModel_PX4& DataModel_PX4::GetInstance()
{
	static DataModel_PX4 px4;
	return px4;
}

const SystemSKU* DataModel_PX4::GetSystemSKU()
{
	return &_sysSKU;
}
