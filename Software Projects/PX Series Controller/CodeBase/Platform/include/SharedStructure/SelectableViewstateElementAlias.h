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

enum SelectableViewstateElementAlias {
	//common selectable elements
	SELECTABLE_ELEMENT_NOT_SET,
	SELECTABLE_ELEMENT_HIDDEN,
	SELECTABLE_ELEMENT_AUTO_REDIR,
	SELECTABLE_BACK_ELEMENT,
	SELECTABLE_SAVE_ELEMENT,
	SELECTABLE_ELEMENT_DYNAMIC,

	//Specific to VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW
	SELECTABLE_PUMP_PWR_SETTING_ELEMENT, //todo... deprecate once moved to dynamic power relays
	SELECTABLE_FANS_PWR_SETTING_ELEMENT, //todo... deprecate once moved to dynamic power relays
	SELECTABLE_LIGHTS_PWR_SETTING_ELEMENT, //todo... deprecate once moved to dynamic power relays
	SELECTABLE_EDIT_RELAY_TYPE,
	SELECTABLE_EDIT_RELAY_GROUP,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_CONFIGURATION_VIEW
	SELECTABLE_MENU_SELECT_SCHD_TASK_SET_EXISTING_ELEMENT,
	SELECTABLE_MENU_SELECT_SCHD_TASK_EDIT_EXISTING_ELEMENT,
	SELECTABLE_MENU_SELECT_SCHD_TASK_CREATE_DELETE_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_SET_EXISTING_VIEW
	SELECTABLE_SCHEDULED_TASKLIST_SET_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_EDIT_EXISTING_VIEW
	SELECTABLE_SCHEDULED_TASKLIST_EDIT_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_DELETE_VIEW
	SELECTABLE_MENU_SELECT_NEW_SCHD_TASK_ELEMENT,
	SELECTABLE_MENU_SELECT_DELETE_SCHD_TASK_ELEMENT,
	SELECTABLE_MENU_SELECT_BULK_DELETE_SCHD_TASK_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TASK_VIEW
	SELECTABLE_SCHEDULED_TASK_TASK_TARGET_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_TASK_ACTION_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_TASK_TIME_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_SELECT_VIEW
	SELECTABLE_SCHEDULED_TASK_CREATE_SELECT_BYRELAY_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_CREATE_SELECT_BYGROUP_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_CREATE_TYPECONF_VIEW
	SELECTABLE_SCHEDULED_TASK_CREATE_RELAY_TASK_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_CREATE_TYPE_TASK_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_CREATE_GROUP_TASK_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_EXISTING_VIEW
	SELECTABLE_SCHEDULED_TASKLIST_DELETE_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_DELETE_TASK_CONF_VIEW
	SELECTABLE_SCHEDULED_TASK_DELETE_CONFYES_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_DELETE_CONFNO_ELEMENT,

	//Specific to VIEWSTATEALIAS_SCHEDULED_TASK_BULK_DELETE_TASK_CONF_VIEW
	SELECTABLE_SCHEDULED_TASK_BULK_DELETE_CONFYES_ELEMENT,
	SELECTABLE_SCHEDULED_TASK_BULK_DELETE_CONFNO_ELEMENT,

	//Specific to VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW
	SELECTABLE_MENU_SELECT_ENVIRONMENT_SUNRISE_SUNSET_ELEMENT,
	SELECTABLE_MENU_SELECT_ENVIRONMENT_AIR_CIRC_ELEMENT,
	SELECTABLE_MENU_SELECT_ENVIRONMENT_ALARM_THRESHOLDS_ELEMENT,

	//Specific to VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW
	SELECTABLE_ENVIRONMENT_SUNRISE_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_SUNSET_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_SUN_CYCLE_SET_ELEMENT,

	//Specific to VIEWSTATEALIAS_ENVIRONMENT_AIR_CIRC_VIEW
	SELECTABLE_ENVIRONMENT_FAN_CIRC_DAY_DUTY_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_CIRC_NIGHT_DUTY_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_CIRC_CYCLE_DURATION_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_CIRC_CYCLE_MODE_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_EX_DAY_DUTY_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_EX_NIGHT_DUTY_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_EX_CYCLE_DURATION_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_FAN_EX_CYCLE_MODE_SET_ELEMENT,

	//Specific to VIEWSTATEALIAS_ENVIRONMENT_ALARM_THRESHOLDS_VIEW
	SELECTABLE_ENVIRONMENT_OVERTEMP_ALARM_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_OVERHUM_ALARM_SET_ELEMENT,
	SELECTABLE_ENVIRONMENT_LOGFULL_ALARM_SET_ELEMENT,

	//Specific to VIEWSTATEALIAS_TIME_INPUT_PROMPT
	SELECTABLE_SETTIME_HH_ELEMENT,
	SELECTABLE_SETTIME_MM_ELEMENT,

	//Specific to VIEWSTATEALIAS_TIME_INPUT_PROMPT
	SELECTABLE_SETBOOLEANVALUE_ELEMENT,
	SELECTABLE_SETTHREESEGMENTVALUE_ELEMENT
};