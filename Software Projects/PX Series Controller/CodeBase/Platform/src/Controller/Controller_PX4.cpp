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

#include "..\..\include\Controller\Controller_PX4.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_NvMemoryManager_Standard.h"
#include "..\..\include\CommandInterpreter\CommandInterpreter_PX4.h"
#include "..\..\include\Viewstate_Map_Generator\Viewstate_Map_Generator_PX4.h"

//Host specific includes
#if defined(TARGET_PLAT_AVR)
#include "..\SharedStructure\MemoryProbe.h"
#include "..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4_ATMega.h"
#else
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4_Win32.h"
#endif

Controller_PX4::Controller_PX4()
{
	//Host specific module factory
	#if defined(TARGET_PLAT_AVR)
		ComponentModuleImp_Factory_PX4_ATMega impFactory;
	#else
		ComponentModuleImp_Factory_PX4_Win32 impFactory;
	#endif

	//create standalone components & component packages
	_rtcLogger = new ComponentPackage_RtcLogger(&impFactory);
	_userInterface = new ComponentPackage_UI_PX4(&impFactory);
	_airSensor = new ComponentPackage_CombinedAirSensor(&impFactory);
	_persistentDataCoordinator = new ComponentModule_NvMemoryManager_Standard(impFactory.Make_NvMemoryManager());

	_powerRelays = new ComponentPackage_PowerRelayArray(&impFactory, _persistentDataCoordinator, _rtcLogger);
	_powerRelays->AddPowerRelay(PersistentComponentAlias::POWER_RELAY_CHANNEL_A, PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_A, ComponentTypeAssociation::PUMP_WATER, ComponentGroupAssociation::GROUP_A);
	_powerRelays->AddPowerRelay(PersistentComponentAlias::POWER_RELAY_CHANNEL_B, PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_B, ComponentTypeAssociation::LIGHT_PRIMARY, ComponentGroupAssociation::GROUP_A);
	_powerRelays->AddPowerRelay(PersistentComponentAlias::POWER_RELAY_CHANNEL_C, PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_C, ComponentTypeAssociation::FAN_CIRCULATION, ComponentGroupAssociation::GROUP_A);
	_powerRelays->AddPowerRelay(PersistentComponentAlias::POWER_RELAY_CHANNEL_D, PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_D, ComponentTypeAssociation::FAN_EXHAUST, ComponentGroupAssociation::GROUP_A);

	//create datamodels, register proxy methods
	dataModel_System = new DataModel_System_PX4(PersistentComponentAlias::DATA_MODEL_SYSTEM, _persistentDataCoordinator, _rtcLogger);
	dataModel_Interface = new DataModel_Interface_PX4();
	dataModel_Environment = new DataModel_Environment_PX4(PersistentComponentAlias::DATA_MODEL_ENVIRONMENT, _persistentDataCoordinator, _airSensor);
	dataModel_Task = new DataModel_Task_PX4(PersistentComponentAlias::DATA_MODEL_TASK, _persistentDataCoordinator);
	dataModel_Viewstate = new DataModel_Viewstate_PX4();

	//create viewstate group, create viewstate manager using viewstate group, subscribe viewstate manager to distributed datamodel notification callbacks
	_vsg = new Viewstate_Group_PX4(dataModel_System, dataModel_Task, dataModel_Environment, dataModel_Environment, _airSensor, _rtcLogger->GetEventLogItems(), dataModel_Viewstate, _powerRelays);
	_vsm = new Viewstate_Manager(_vsg, dataModel_Viewstate, _userInterface, _rtcLogger);
	
	dataModel_System->attachObserver(_vsm);
	dataModel_Interface->attachObserver(_vsm);
	dataModel_Environment->attachObserver(_vsm);
	dataModel_Task->attachObserver(_vsm);
	dataModel_Viewstate->attachObserver(_vsm);

	//create viewstate map generator
	_viewstateMapGenerator = new Viewstate_Map_Generator_PX4();

	//create Task scheduler
	_scheduler = new TaskScheduler(dataModel_Task, _rtcLogger);

	//Create a task handler factory, use it to create a task executor
	_taskHandlerFactory = new TaskHandlerFactory_PX4(dataModel_Viewstate, _viewstateMapGenerator, dataModel_Environment, dataModel_Environment, dataModel_System, dataModel_Task, _rtcLogger, _powerRelays, _userInterface, _userInterface);
	_taskExecutor = new TaskExecutor(_rtcLogger, _taskHandlerFactory);

	//Create the command interpreter, add polled interfaces that my produce tasks
	_commandInterpreter = new CommandInterpreter_PX4(dataModel_Interface, _rtcLogger);
	_commandInterpreter->AddPolledInterface(*_userInterface);
	_commandInterpreter->InvokePolledInterfaceScan();
}

Controller_PX4::~Controller_PX4()
{
	delete _persistentDataCoordinator;
	delete _rtcLogger;
	delete _userInterface;
	delete _powerRelays;
	delete _airSensor;
	delete dataModel_System;
	delete dataModel_Interface;
	delete dataModel_Environment;
	delete dataModel_Task;
	delete dataModel_Viewstate;
	delete _vsm;
	delete _vsg;
	delete _taskHandlers;
	delete _taskHandlerFactory;
	delete _commandInterpreter;
}

bool Controller_PX4::Initialize()
{
	//restore persistent state to persistent components
	_rtcLogger->LogEvent(EVENT_TEXT_SYSTEM_INIT_COMPLETE);
	_userInterface->playSuccessPostTone();
	_rtcLogger->LogEvent(EVENT_TEXT_SYSTEM_STARTUP_COMPLETE);
	dataModel_Viewstate->SetNavigationMap(_viewstateMapGenerator->GenerateMap(VIEWSTATEALIAS_STATUS_VIEW));
	dataModel_Interface->RegisterUserInputAction(_rtcLogger->CurrentTime());
	_userInterface->EnableBacklight();
	this->LogControllerStatus();
	return true;
}

bool Controller_PX4::Run()
{
	if (dataModel_System->GetControllerRestartSignal()) { return false; }

	UpdateState();		
	ManageTasks();
	ProcessTasks();

	return true;
}

void Controller_PX4::UpdateState()
{
	// General non-scheduled state updates
	if (_rtcLogger->CurrentTime().secondstime() >= (lastRelayUpdate + MAX_POWER_RELAY_STATE_REFRESH_INTERVAL_SEC))
	{
		_commandInterpreter->InvokeTaskRequest(TASKALIAS_REFRESH_STATE_SYSTEM_ALARMS);

		if (dataModel_Viewstate->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW)
		{
			_commandInterpreter->InvokeTaskRequest(TASKALIAS_REFRESH_STATE_LIGHT);
			_commandInterpreter->InvokeTaskRequest(TASKALIAS_REFRESH_STATE_CIRCULATION_FANS);
			_commandInterpreter->InvokeTaskRequest(TASKALIAS_REFRESH_STATE_EXHAUST_FANS);
		}

		lastRelayUpdate = _rtcLogger->CurrentTime().secondstime();
	}

	// DISPLAY TIMEOUT
	if (_userInterface->BacklightEnabled() && _rtcLogger->CurrentTime().secondstime() >= (dataModel_Interface->LastInputActionTime()->secondstime() + DISPLAY_SLEEP_TIMEOUT_SEC))
	{
		_commandInterpreter->InvokeTaskRequest(TASKALIAS_DISABLE_DISPLAY);
	}

	// VIEWSTATE TIMEOUT
	if (_rtcLogger->CurrentTime().secondstime() >= (dataModel_Viewstate->LastViewstatePublish()->secondstime() + DEFAULT_VIEW_TIMEOUT_SEC))
	{
		if (dataModel_Viewstate->GetNavigationMap()->ViewstateAssociation() != VIEWSTATEALIAS_STATUS_VIEW)
		{
			dataModel_Viewstate->SetNavigationMap(_viewstateMapGenerator->GenerateMap(VIEWSTATEALIAS_STATUS_VIEW));
		}			
	}

	// VIEWSTATE REFRESH
	if (_rtcLogger->CurrentTime().secondstime() >= (dataModel_Viewstate->LastViewstatePublish()->secondstime() + MAX_VIEWSTATE_REFRESH_INTERVAL_SEC))
	{
		dataModel_Viewstate->notifyObservers();
	}

	// STATUS LOGGING REFRESH
	if(_rtcLogger->CurrentTime().secondstime() >= (lastStatusLogUpdate + CONTROLLER_STATUS_OUTPUT_INTERVAL_SEC))
	{
		#if defined(ENABLE_VERBOSE_LOGGING)
		LogControllerStatus();
		#endif

		#if defined(ENABLE_ENVIORNMENT_LOGGING)
		LogEnvironmentData();
		#endif

		lastStatusLogUpdate = _rtcLogger->CurrentTime().secondstime();
	}
}

void Controller_PX4::ManageTasks()
{
	_commandInterpreter->InvokePolledInterfaceScan();
	_scheduler->QueueScheduledTasks();
}

void Controller_PX4::ProcessTasks()
{
	_taskExecutor->ProcessTaskQueue(BATCH_TASK_PROCESSING_LIMIT);
}

void Controller_PX4::Shutdown()
{
}

void Controller_PX4::LogControllerStatus()
{
	_rtcLogger->LogMessage(EVENT_TEXT_TASKPOOL_QUEUED_COUNT, TASK_ITEM_POOL_SIZE - TaskItemPool::GetInstance().FreeTaskItemCount());
	_rtcLogger->LogMessage(EVENT_TEXT_SCHEDULED_TASK_COUNT, SCHEDULED_TASK_DETAIL_COUNT - dataModel_Task->GetFreeScheduledTaskDetailCount());
	_rtcLogger->LogMessage(EVENT_TEXT_LAST_USER_INPUT_TIME, dataModel_Interface->LastInputActionTime());

	#if defined(TARGET_PLAT_AVR)
	_rtcLogger->LogMessage(EVENT_TEXT_FREE_MEMORY_AVAILABLE, freeMemory());
	#endif
}

void Controller_PX4::LogEnvironmentData()
{
	_rtcLogger->LogMessage(EVENT_TEXT_TEMPERATURE_STATE, (int)_airSensor->CurrentTemperatureFahrenheit());
	_rtcLogger->LogMessage(EVENT_TEXT_HUMIDITY_STATE, (int)_airSensor->CurrentRelativeHumidity());
}