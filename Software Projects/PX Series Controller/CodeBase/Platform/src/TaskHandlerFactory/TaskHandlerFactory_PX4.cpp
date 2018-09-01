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

#include "..\..\include\TaskHandlerFactory\TaskHandlerFactory_PX4.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ViewstateNavigate_TaskHandler.h"
#include "..\..\include\TaskHandler\Component_TaskHandler\PX4_PowerRelay_TaskHandler.h"
#include "..\..\include\TaskHandler\StateRefresh_TaskHandler\PX4_StateRefresh_Alarms.h"
#include "..\..\include\TaskHandler\StateRefresh_TaskHandler\PX4_StateRefresh_Display.h"
#include "..\..\include\TaskHandler\StateRefresh_TaskHandler\PX4_StateRefresh_FansCirculation.h"
#include "..\..\include\TaskHandler\StateRefresh_TaskHandler\PX4_StateRefresh_FansExhaust.h"
#include "..\..\include\TaskHandler\StateRefresh_TaskHandler\PX4_StateRefresh_Lights.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ManualOverrideViewstate_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_EnvironmentSettings_FanCycle_Viewstate_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_EnvironmentSettings_LightCycleView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_CreateSelectView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_CreateView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_SetView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_EditView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_DeleteView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_DeleteTaskConfView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_PowerRelaySettingsViewstate_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_PowerRelayEditViewstate_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_InputViewstate_ThreeSegmentValue_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_InputViewstate_BooleanValue_TaskHandler.h"
#include "..\..\include\TaskHandler\Viewstate_TaskHandlers\PX4_InputViewstate_TimeSpanValue_TaskHandler.h"

TaskHandlerFactory_PX4::~TaskHandlerFactory_PX4()
{
	while (!_taskHandlers.empty())
	{
		_taskHandlers.removeFront();
	}
}

T_List<ITaskHandler&>* TaskHandlerFactory_PX4::MakeHandlerList()
{
	//general handlers
	_taskHandlers.addBack(*new PX4_ViewstateNavigate_TaskHandler(_viewstateData, _mapGenerator, _navTonePlayer));
	_taskHandlers.addBack(*new PX4_InputViewstate_ThreeSegmentValue_TaskHandler(_viewstateData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_InputViewstate_BooleanValue_TaskHandler(_viewstateData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_InputViewstate_TimeSpanValue_TaskHandler(_viewstateData, _mapGenerator));
	
	//state handlers
	_taskHandlers.addBack(*new PX4_StateRefresh_Alarms(_systemData, _environmentAirData, _rtcLogger));
	_taskHandlers.addBack(*new PX4_StateRefresh_Lights(_powerRelays, _environmentLightData, _rtcLogger));
	_taskHandlers.addBack(*new PX4_StateRefresh_FansCirculation(_systemData, _environmentAirData, _environmentLightData, _rtcLogger, _powerRelays));
	_taskHandlers.addBack(*new PX4_StateRefresh_FansExhaust(_systemData, _environmentAirData, _environmentLightData, _rtcLogger, _powerRelays));
	_taskHandlers.addBack(*new PX4_StateRefresh_Display(_display));

	//viewstate menu handlers
	_taskHandlers.addBack(*new PX4_ManualOverrideViewstate_TaskHandler(_viewstateData, _powerRelays));
	_taskHandlers.addBack(*new PX4_EnvironmentSettings_FanCycle_Viewstate_TaskHandler(_viewstateData, _environmentAirData,_mapGenerator));
	_taskHandlers.addBack(*new PX4_EnvironmentSettings_LightCycleView_TaskHandler(_viewstateData, _environmentLightData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler(_viewstateData, _environmentAirData, _systemData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_PowerRelaySettingsViewstate_TaskHandler(_viewstateData, _powerRelays, _mapGenerator));
	_taskHandlers.addBack(*new PX4_PowerRelayEditViewstate_TaskHandler(_viewstateData, _mapGenerator, _powerRelays));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_CreateView_TaskHandler(_viewstateData, _taskData, _mapGenerator, _powerRelays));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_CreateTaskSelectView_TaskHandler(_viewstateData, _taskData, _mapGenerator, _powerRelays));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_CreateTaskConfView_TaskHandler(_viewstateData, _taskData, _mapGenerator, _powerRelays));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_SetView_TaskHandler(_viewstateData, _taskData, _mapGenerator, _powerRelays));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_EditView_TaskHandler(_viewstateData, _taskData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_DeleteView_TaskHandler(_viewstateData, _taskData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_DeleteTaskConfView_TaskHandler(_viewstateData, _taskData, _mapGenerator));
	_taskHandlers.addBack(*new PX4_ScheduledTasksConfig_DeleteBulkTaskConfView_TaskHandler(_viewstateData, _taskData, _mapGenerator));

	//component handlers
	_taskHandlers.addBack(*new PX4_PowerRelay_TaskHandler(_powerRelays));

	return &_taskHandlers;
}