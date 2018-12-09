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

#include "..\..\..\Configurations\PX4_Config.h"
#include "IController.h"
#include "..\SharedStructure\SharedInterface\IPersistentDataCoordinator.h"
#include "..\..\..\Components\ComponentPackages\include\ComponentPackage_RtcLogger.h"
#include "..\..\..\Components\ComponentPackages\include\ComponentPackage_UI_PX4.h"
#include "..\..\..\Components\ComponentPackages\include\ComponentPackage_PowerRelayArray.h"
#include "..\..\..\Components\ComponentPackages\include\ComponentPackage_CombinedAirSensor.h"
#include "..\..\include\DataModel\DataModel_System_PX4.h"
#include "..\..\include\DataModel\DataModel_Interface_PX4.h"
#include "..\..\include\DataModel\DataModel_Environment_PX4.h"
#include "..\..\include\DataModel\DataModel_Task_PX4.h"
#include "..\..\include\DataModel\DataModel_Viewstate_PX4.h"
#include "..\Viewstate_Manager\Viewstate_Manager.h"
#include "..\Viewstate\Group\Viewstate_Group_PX4.h"
#include "..\TaskScheduler\TaskScheduler.h"
#include "..\TaskHandlerFactory\TaskHandlerFactory_PX4.h"
#include "..\TaskExecutor\TaskExecutor.h"
#include "..\SharedStructure\SharedInterface\ICommandInterpreter.h"
#include "..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"

class Controller_PX4 : public IController
{
public:
	Controller_PX4();
	virtual ~Controller_PX4() override;

	// DataModels
	DataModel_System_PX4 * dataModel_System;
	DataModel_Interface_PX4 * dataModel_Interface;
	DataModel_Environment_PX4 * dataModel_Environment;
	DataModel_Task_PX4 * dataModel_Task;
	DataModel_Viewstate_PX4 * dataModel_Viewstate;

	// Inherited via IController
	virtual bool Initialize() override;
	virtual bool Run() override;
	virtual void Shutdown() override;

protected:	
	long lastRelayUpdate = 0;
	long lastStatusLogUpdate = 0;

	void LogControllerStatus();
	void LogEnvironmentData();
	void UpdateState();
	void ManageTasks();
	void ProcessTasks();
	
private:
	IPersistentDataCoordinator * _persistentDataCoordinator;
	ComponentPackage_RtcLogger * _rtcLogger;
	ComponentPackage_UI_PX4 * _userInterface;
	ComponentPackage_PowerRelayArray * _powerRelays;
	ComponentPackage_CombinedAirSensor * _airSensor;

	Viewstate_Manager * _vsm;
	Viewstate_Group_PX4 * _vsg;

	TaskHandlerFactory_PX4 * _taskHandlerFactory;
	TaskExecutor * _taskExecutor;
	T_List<ITaskHandler> * _taskHandlers;
	TaskScheduler * _scheduler;
	ICommandInterpreter * _commandInterpreter;
	IViewstateMapGenerator * _viewstateMapGenerator;
};