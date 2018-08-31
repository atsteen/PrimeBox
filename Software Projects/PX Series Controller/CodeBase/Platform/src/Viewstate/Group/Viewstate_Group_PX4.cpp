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

#include "..\..\..\include\Viewstate\Group\Viewstate_Group_PX4.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_StatusView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ManualOverrideView_TLMV.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ManualOverrideView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfigView_TLMV.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfigView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateTaskSelectView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateTaskView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_SetTaskView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_EditTaskView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_DeleteTaskView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_BulkDeleteTaskView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettingsView_TLMV.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettingsView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettings_LightCycleView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettings_FanCycleView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_EnvironmentSettings_AlarmThresholdView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_SetTimeView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_SetThreeSegmentView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_SetBooleanView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_PowerRelayView_TLMV.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_PowerRelaySettingsView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_PowerRelayEditView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateTaskByAssociationView.h"
#include "..\..\..\include\Viewstate\Viewstate_PX4_ScheduledTasksConfig_CreateTaskByRelayView.h"

Viewstate_Group_PX4::Viewstate_Group_PX4(IModelSystemData * systemData, IModelTaskData * taskData, IModelEnvLightData * lightData, IModelEnvAirData * airData, IAirSensor * airSensor, EventLog_Item_Collection * eventCollection, IModelViewstateData * viewStateData, IPowerRelayArray * relayArray) :
	_systemData(systemData),
	_taskData(taskData),
	_lightData(lightData),
	_airData(airData),
	_airSensor(airSensor),
	_eventCollection(eventCollection),
	_viewStateData(viewStateData),
	_relayArray(relayArray)
{}

ITextViewstate * Viewstate_Group_PX4::GetViewstateByAlias(const ViewstateAlias viewstateAlias)
{
	if (_requestedViewstate) { delete _requestedViewstate; }

	switch (viewstateAlias) {
		case ViewstateAlias::VIEWSTATEALIAS_STATUS_VIEW :			
			_requestedViewstate = new Viewstate_PX4_StatusView(_airSensor, _airData, _systemData, _eventCollection);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW_TLMV :
			_requestedViewstate = new Viewstate_PX4_ManualOverrideView_TLMV;
			break;

		case ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW :
			_requestedViewstate = new Viewstate_PX4_ManualOverrideView(_viewStateData, _relayArray);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW_TLMV:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfigView_TLMV;
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfigView(_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_SET_EXISTING_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_SetTaskView(_viewStateData, _taskData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView(_taskData,_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TASK_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_CreateTaskView(_taskData,_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_SELECT_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_CreateTaskSelectView(_taskData, _viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_ASSOCIATION_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_CreateTaskByAssociationView(_taskData, _viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_BY_RELAY_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_CreateTaskByRelayView(_taskData, _viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_EDIT_EXISTING_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_EditTaskView(_viewStateData,_taskData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_DeleteTaskView(_viewStateData, _taskData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_CONF_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView(_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_SCHEDULED_TASK_BULK_DELETE_TASK_CONF_VIEW:
			_requestedViewstate = new Viewstate_PX4_ScheduledTasksConfig_BulkDeleteTaskView(_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW_TLMV:
			_requestedViewstate = new Viewstate_PX4_EnvironmentSettingsView_TLMV;
			break;

		case ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW:
			_requestedViewstate = new Viewstate_PX4_EnvironmentSettingsView(_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW:
			_requestedViewstate = new Viewstate_PX4_EnvironmentSettings_LightCycleView(_lightData, _viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_AIR_CIRC_VIEW:
			_requestedViewstate = new Viewstate_PX4_EnvironmentSettings_FanCycleView(_airData, _viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_ALARM_THRESHOLDS_VIEW:
			_requestedViewstate = new Viewstate_PX4_EnvironmentSettings_AlarmThresholdView(_airData,_systemData,_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW_TLMV:
			_requestedViewstate = new Viewstate_PX4_PowerRelayView_TLMV();
			break;

		case ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW:
			_requestedViewstate = new Viewstate_PX4_PowerRelaySettingsView(_viewStateData, _relayArray);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_TIME:
			_requestedViewstate = new Viewstate_PX4_SetTimeView(_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_THREESEGMENT:
			_requestedViewstate = new Viewstate_PX4_SetThreeSegmentView(_viewStateData);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ENABLE_DISABLE:
			_requestedViewstate = new Viewstate_PX4_SetBooleanView(_viewStateData, VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ENABLE_DISABLE);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ON_OFF:
			_requestedViewstate = new Viewstate_PX4_SetBooleanView(_viewStateData, VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ON_OFF);
			break;

		case ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_EDIT_VIEW :
			_requestedViewstate = new Viewstate_PX4_PowerRelayEditView(_viewStateData, _relayArray);
			break;

		default :
			_requestedViewstate = new Viewstate_PX4_StatusView(
				_airSensor,
				_airData,
				_systemData,
				_eventCollection);
			break;
	}
		
	return _requestedViewstate;
}










