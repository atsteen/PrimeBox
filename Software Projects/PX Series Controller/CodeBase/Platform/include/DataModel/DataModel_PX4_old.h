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
#include "IDataModel.h"
#include "..\SharedStructure\EventLog_Item_Collection.h"
#include "..\SharedStructure\ViewstateAlias.h"
#include "..\SharedStructure\SelectableViewstateElementAlias.h"
#include "..\SharedStructure\Subject.h"
#include "..\SharedStructure\TaskAlias.h"
#include "..\SharedStructure\ScheduledTaskDetailPool.h"
#include "..\SharedStructure\SharedInterface\Ipersistent.h"

enum PowerState {
	PWR_ON,
	PWR_OFF,
	PWR_AUTO
};

class DataModel_PX4 :
	public IDataModel,
	public Subject,
	public Ipersistent
{
public:
	static DataModel_PX4& GetInstance();
	virtual ~DataModel_PX4() {};

	TimeSignature lastStatusPublish = { 2000,1,1 };
	uint8_t listSelectIndex = 0;


	//////////////////////////////////////////////IModelSystemData
	bool signalControllerRestart = false;
	virtual SystemSKU const* GetSystemSKU() override;
	ViewstateStringAlias GetSystemMode() { return _systemMode; }
	void SetSystemMode(const ViewstateStringAlias vsa) { _systemMode = vsa; } // Ephemeral Data set
	const bool GetLogAlarmDefaultState() { return _logAlarmDefaultState; }
	void SetLogAlarmDefaultState(bool state); // Persistent Data Set

	//////////////////////////////////////////////IModelEnvAirData
	const int GetFanDutyCycleDay() { return _fanDutyCycleDay; }
	const int GetFanDutyCycleNight() { return _fanDutyCycleNight; }
	const bool GetFanCycleDefaultState() { return _fanCycleDefaultState; }
	const int GetAlarmThresholdOverTempF() { return _alarmThreshold_OverTempF; }
	const int GetAlarmThresholdOverRH() { return _alarmThreshold_OverRH; }
	void SetFanCycleDefaultState(bool state); // Persistent Data Set
	void AdjustFanDutyCycleDay(int fdc); // Persistent Data modifiers
	void AdjustFanDutyCycleNight(int fdc); // Persistent Data modifiers
	void AdjustAlarmThresholdOverTempF(int temp); // Persistent Data modifiers
	void AdjustAlarmThresholdOverRH(int rh); // Persistent Data modifiers

	//////////////////////////////////////////////IModelEnvLightData
	const bool GetLightCycleDefaultState() { return _lightCycleDefaultState; }
	const TimeSignature GetDefaultSunriseTime() { return _defaultSunriseTime; }
	const TimeSignature GetDefaultSunsetTime() { return _defaultSunsetTime; }
	void SetLightCycleDefaultState(bool state); // Persistent Data Set
	void AdjustDefaultSunriseTimeHH(int hh); // Persistent Data modifiers
	void AdjustDefaultSunriseTimeMM(int mm); // Persistent Data modifiers
	void AdjustDefaultSunsetTimeHH(int hh); // Persistent Data modifiers
	void AdjustDefaultSunsetTimeMM(int mm); // Persistent Data modifiers

	//////////////////////////////////////////////IModelInterfaceData
	const bool GetPromptInputModalState() { return _promptInputModalState; }
	const TimeSignature * LastInputActionTime() { return &_lastInputActionTime; }
	void RegisterUserInputAction(TimeSignature ts) { _lastInputActionTime = ts; } // Ephemeral Data set
	void SetPromptInputModalState(bool state) { _promptInputModalState = state; } // Ephemeral Data set

	//////////////////////////////////////////////IModelTaskData
	const TimeSignature GetCreateSchdTaskTime() { return _createSchdTaskTime; }
	const TaskAlias GetCreateSchdTaskType() { return _createSchdTaskType; }
	ScheduledTaskDetailPool * GetScheduledTaskPool() { return &_scheduledTasks; }
	const TimeSignature GetScheduledTaskTime() { return _scheduledTasks.GetScheduledTaskDetail(listSelectIndex)->_scheduledExecutionTime; }
	const int GetFreeScheduledTaskCount() { return _scheduledTasks.FreeScheduledTaskDetailCount(); }
	void SetCreateSchdTaskType(TaskAlias taskType) { _createSchdTaskType = taskType; } // Ephemeral Data set
	void AdjustCreateSchdTaskTimeHH(int hh) { _createSchdTaskTime.AdjustHH(hh); } // Ephemeral data modifiers
	void AdjustCreateSchdTaskTimeMM(int mm) { _createSchdTaskTime.AdjustMM(mm); } // Ephemeral data modifiers
	void AdjustEditSchdTaskTimeHH(int hh) { _scheduledTasks.GetScheduledTaskDetail(listSelectIndex)->_scheduledExecutionTime.AdjustHH(hh); } // Ephemeral data modifiers
	void AdjustEditSchdTaskTimeMM(int mm) { _scheduledTasks.GetScheduledTaskDetail(listSelectIndex)->_scheduledExecutionTime.AdjustMM(mm); } // Ephemeral data modifiers

	//////////////////////////////////////////////IModelViewstateData

protected:
	TimeSignature _lastInputActionTime = { 0,0,0 };
	TimeSignature _lastViewstateUpdateTime = { 0,0,0 };
	SystemSKU _sysSKU = { '0', '0', '3' };

private:
	DataModel_PX4() : Ipersistent_Component(_persistentAlias) { RestorePersistentData(); }
	DataModel_PX4(DataModel_PX4 const&);
	void operator=(DataModel_PX4 const&);
	const PersistentComponentAlias _persistentAlias = PersistentComponentAlias::DATA_MODEL;
	const char * _defaultWaterTemperature = "##";
	ViewstateStringAlias _systemMode = EVENT_TEXT_SYSTEMSTATUS_INIT;

	ViewstateAlias _activeView = VIEWSTATEALIAS_STATUS_VIEW;
	SelectableViewstateElementAlias _selectedViewstateElement = SELECTABLE_ELEMENT_NOT_SET;
	
	PowerState _pumpDefaultPWRState = PowerState::PWR_AUTO;
	PowerState _fansDefaultPWRState = PowerState::PWR_AUTO;
	PowerState _lightsDefaultPWRState = PowerState::PWR_AUTO;

	bool _lightCycleDefaultState = true;
	bool _fanCycleDefaultState = true;
	bool _logAlarmDefaultState = true;
	bool _promptInputModalState = false;

	int _fanDutyCycleDay = 80;	
	int _fanDutyCycleNight = 20;
	const int _fanDutyCycle_MAX = 100;
	const int _fanDutyCycle_MIN = 0;

	TimeSignature _defaultSunriseTime = { 0,0,0,6 };
	TimeSignature _defaultSunsetTime = { 0,0,0,22 };
	TimeSignature _createSchdTaskTime = { 0,0,0 };

	int _alarmThreshold_OverTempF = 85;
	int _alarmThreshold_OverTempF_MIN = 32;
	int _alarmThreshold_OverTempF_MAX = 120;

	int _alarmThreshold_OverRH = 70;
	int _alarmThreshold_OverRH_MIN = 0;
	int _alarmThreshold_OverRH_MAX = 100;

	TaskAlias _createSchdTaskType = TaskAlias::TASKALIAS_NOT_SET;
	ScheduledTaskDetailPool _scheduledTasks;
};