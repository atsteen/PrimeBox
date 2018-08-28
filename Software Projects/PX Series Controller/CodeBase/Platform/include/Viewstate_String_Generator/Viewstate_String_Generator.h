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

enum ViewstateStringAlias {
	ALIAS_NOT_SET,
	//Viewstate_Element_Text_ComponentState
	COMPONENT_TEXT_STATE_ENABLED,
	COMPONENT_TEXT_STATE_ENABLED_ABRV,
	COMPONENT_TEXT_STATE_DISABLED,
	COMPONENT_TEXT_STATE_DISABLED_ABRV,
	COMPONENT_TEXT_STATE_ON,
	COMPONENT_TEXT_STATE_OFF,
	COMPONENT_TEXT_STATE_AUTO,
	COMPONENT_TEXT_STATE_OVERRIDE,

	//Viewstate_PX4_ManualOverrideView & Viewstate_PX4_PowerRelaySettingsView
	MANUAL_OVERRIDE_VIEW_TEXT_TITLE,
	COMPONENT_TEXT_FAN,
	COMPONENT_TEXT_PUMP,
	COMPONENT_TEXT_LIGHT,
	COMPONENT_TEXT_SHORT_OUTLET,
	COMPONENT_TEXT_SHORT_CIRCULATION_FAN,
	COMPONENT_TEXT_SHORT_EXHAUST_FAN,
	COMPONENT_TEXT_SHORT_LIGHT,
	COMPONENT_TEXT_SHORT_PUMP,

	//Viewstate_PX4_PowerRelaySettingsView & Viewstate_PX4_PowerRelayEditView
	COMPONENT_TEXT_SHORT_GROUP_A,
	COMPONENT_TEXT_SHORT_GROUP_B,
	COMPONENT_TEXT_SHORT_GROUP_C,
	COMPONENT_TEXT_SHORT_GROUP_D,
	COMPONENT_TEXT_TYPE_LABEL,
	COMPONENT_TEXT_GROUP_LABEL,

	//VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW_TLMV
	POWER_RELAY_SETTINGS_VIEW_TEXT_TITLE,

	//Common
	DEFAULT_TIME_TEXT,
	DEFAULT_RULE_LINE,
	DEFAULT_TLMV_TEXT_SETTINGS,

	TASKALIAS_DISPLAY_TEXT_NOT_SET,
	TASKALIAS_DISPLAY_TEXT_ENABLE_PUMP,
	TASKALIAS_DISPLAY_TEXT_DISABLE_PUMP,
	TASKALIAS_DISPLAY_TEXT_ENABLE_FANS,
	TASKALIAS_DISPLAY_TEXT_DISABLE_FANS,
	TASKALIAS_DISPLAY_TEXT_ENABLE_LIGHTS,
	TASKALIAS_DISPLAY_TEXT_DISABLE_LIGHTS,

	//Viewstate_PX4_SetTimeView
	INPUT_PROMPT_SET_TIME_SIGNATURE,

	//Viewstate_PX4_SetThreeSegmentView
	INPUT_PROMPT_SET_THREE_SEGMENT_VALUE,
	INPUT_PROMPT_SET_TASK_ACTION,

	//Common
	DEFAULT_BACK_TEXT,
	DEFAULT_YES_TEXT,
	DEFAULT_NO_TEXT,
	DEFAULT_SAVE_TEXT,
	DEFAULT_EDIT_TEXT,
	DEFAULT_CONFIG_TEXT,

	//Viewstate_PX4_EnvironmentSettingsView
	ENV_SETTINGS_TEXT_LIGHT_MENU,
	ENV_SETTINGS_TEXT_AIR_MENU,
	ENV_SETTINGS_TEXT_ALARM_MENU,

	//Viewstate_PX4_EnvironmentSettingsView_TLMV
	ENV_SETTINGS_TLMV_TEXT_TITLE,

	//Viewstate_PX4_EnvironmentSettings_LightCycleView
	ENV_SETTINGS_LIGHTCYCLE_TEXT_SETSUNRISE,
	ENV_SETTINGS_LIGHTCYCLE_TEXT_SETSUNSET,
	ENV_SETTINGS_LIGHTCYCLE_TEXT_SETLIGHTCYCLEMODE,

	//Viewstate_PX4_EnvironmentSettings_AlarmThresholdView
	ENV_SETTINGS_ALARM_THRESHOLD_TEXT_OVER_TEMP,
	ENV_SETTINGS_ALARM_THRESHOLD_TEXT_OVER_RH,
	ENV_SETTINGS_ALARM_THRESHOLD_TEXT_LOGFULL,

	//Viewstate_PX4_EnvironmentSettings_FanCycleView
	ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_DAY,
	ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_NIGHT,
	ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_DURATION,
	ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_MODE,
	ENV_SETTINGS_FAN_EX_CYCLE_TEXT_DAY,
	ENV_SETTINGS_FAN_EX_CYCLE_TEXT_NIGHT,
	ENV_SETTINGS_FAN_EX_CYCLE_TEXT_DURATION,
	ENV_SETTINGS_FAN_EX_CYCLE_TEXT_MODE,

	//Viewstate_PX4_ScheduledTasksConfig_BulkDeleteTaskView
	SCH_TASK_CONFIG_BULKDELETE_PROMPT_TEXT,
	
	//Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView
	SCH_TASK_CONFIG_MENU_TEXT_CREATE,
	SCH_TASK_CONFIG_MENU_TEXT_DELETE,
	SCH_TASK_CONFIG_MENU_TEXT_BULKDELETE,

	//Viewstate_PX4_ScheduledTasksConfig_CreateTaskView
	SCH_TASK_CONFIG_CREATE_TEXT_TASKTARGET,
	SCH_TASK_CONFIG_CREATE_TEXT_TASKACTION,
	SCH_TASK_CONFIG_CREATE_TEXT_TASKTIME,

	//Viewstate_PX4_ScheduledTasksConfig_CreateTaskSelectView
	SCH_TASK_CONFIG_CREATE_SELECT_TEXT_BY_RELAY,
	SCH_TASK_CONFIG_CREATE_SELECT_TEXT_BY_GROUP,

	//Viewstate_PX4_ScheduledTasksConfig_DeleteTaskConfView
	SCH_TASK_CONFIG_DELETE_TEXT_CONF,

	//Viewstate_PX4_ScheduledTasksConfigView
	SCH_TASK_CONFIG_MENU_TEXT_SET,
	SCH_TASK_CONFIG_MENU_TEXT_EDIT,
	SCH_TASK_CONFIG_MENU_TEXT_CREATEDELETE,

	//Viewstate_PX4_ScheduledTasksConfigView_TLMV
	SCH_TASK_CONFIG_TLMV_TEXT_TITLE,

	//Event strings for logging
	EVENT_TEXT_NOT_SET,
	EVENT_TEXT_SYSTEM_INIT_COMPLETE,
	EVENT_TEXT_SYSTEM_STARTUP_COMPLETE,
	EVENT_TEXT_POWERRELAY_FAN_ON,
	EVENT_TEXT_POWERRELAY_FAN_OFF,
	EVENT_TEXT_POWERRELAY_PUMP_ON,
	EVENT_TEXT_POWERRELAY_PUMP_OFF,
	EVENT_TEXT_POWERRELAY_LIGHT_ON,
	EVENT_TEXT_POWERRELAY_LIGHT_OFF,
	EVENT_TEXT_DATALOGGER_SD_FAIL,
	EVENT_TEXT_SYSTEMSTATUS_OK,
	EVENT_TEXT_SYSTEMSTATUS_ERROR,
	EVENT_TEXT_SYSTEMSTATUS_ALERT,
	EVENT_TEXT_SYSTEMSTATUS_INIT,
	EVENT_TEXT_ALARM_OVERTEMP,
	EVENT_TEXT_ALARM_OVERRH,
	EVENT_TEXT_TASKPOOL_QUEUED_COUNT,
	EVENT_TEXT_SCHEDULED_TASK_COUNT,
	EVENT_TEXT_LAST_USER_INPUT_TIME,
	EVENT_TEXT_FREE_MEMORY_AVAILABLE,
	EVENT_TEXT_TASKPOOL_FULL,

	//Message strings for logging
	MESSAGE_TEXT_TASK_RETRY_FAILURE

};

#if defined(TARGET_PLAT_AVR)

	#include <avr/pgmspace.h>	
	const char aliasNotSet[] PROGMEM = "???";
	const char componentStateEnabledText[] PROGMEM = "[ENABLED ]";
	const char componentStateEnabledAbrvText[] PROGMEM = "[ENA]";
	const char componentStateDisabledText[] PROGMEM = "[DISABLED]";
	const char componentStateDisabledAbrvText[] PROGMEM = "[DIS]";
	const char componentStateOnText[] PROGMEM = "[ ON]";
	const char componentStateOffText[] PROGMEM = "[OFF]";
	const char componentStateAutoText[] PROGMEM = "[AUTO]";
	const char componentStateOverrideText[] PROGMEM = "OVR-";
	const char manualOverrideViewTextTitle[] PROGMEM = "MANUAL OVERRIDES";
	const char componentFanText[] PROGMEM = "FANS";
	const char componentPumpText[] PROGMEM = "PUMP";
	const char componentLightText[] PROGMEM = "LIGHTS";

	const char componentShortNameOutletText[] PROGMEM = "Outlet";
	const char componentShortNameCirculationFanText[] PROGMEM = "FanCir";
	const char componentShortNameExhaustFanText[] PROGMEM = "FanExh";
	const char componentShortNameLightText[] PROGMEM = "Light";
	const char componentShortNamePumpText[] PROGMEM = "Pump";

	const char componentShortNameGroupA[] PROGMEM = "GrpA";
	const char componentShortNameGroupB[] PROGMEM = "GrpB";
	const char componentShortNameGroupC[] PROGMEM = "GrpC";
	const char componentShortNameGroupD[] PROGMEM = "GrpD";

	const char componentTypeLabel[] PROGMEM = "Type";
	const char componentGroupLabel[] PROGMEM = "Group";

	const char PowerRelaySettingsViewTextTitle[] PROGMEM = "RELAY CONFIGURATION";

	const char defaultTimeText[] PROGMEM = "[##:##]";
	const char defaultRuleLineText[] PROGMEM = "--------------------";
	const char defaultTlmvTextSettings[] PROGMEM = "-----SETTINGS----";
	const char taskAliasDisplayText_NotSet[] PROGMEM = "[NotSet]";	
	const char taskAliasDisplayText_EnablePump[] PROGMEM = "[Pmp_On]";
	const char taskAliasDisplayText_DisablePump[] PROGMEM = "[PmpOff]";
	const char taskAliasDisplayText_EnableFans[] PROGMEM = "[Fan_On]";
	const char taskAliasDisplayText_DisableFans[] PROGMEM = "[FanOff]";
	const char taskAliasDisplayText_EnableLights[] PROGMEM = "[Lht_On]";
	const char taskAliasDisplayText_DisableLights[] PROGMEM = "[LhtOff]";
	const char InputPromptSetTimeText[] PROGMEM = "Set Task Time";
	const char InputPromptSetThreeSegmentValueText[] PROGMEM = "Set value";
	const char InputPromptSetTaskAxtionText[] PROGMEM = "Set action";
	const char DefaultBackText[] PROGMEM = "BACK";
	const char DefaultYesText[] PROGMEM = "[YES]";
	const char DefaultNoText[] PROGMEM = "[NO]";
	const char DefaultSaveText[] PROGMEM = "SAVE";
	const char DefaultEditText[] PROGMEM = "EDIT";
	const char DefaultConfigText[] PROGMEM = "Config";
	const char EnvSettingsText_LightMenu[] PROGMEM = "Sunrise/Set Default";
	const char EnvSettingsText_AirMenu[] PROGMEM = "Air Circ DutyCycles";
	const char EnvSettingsText_AlarmMenu[] PROGMEM = "Alarm Thresholds";
	const char EnvSettingsTlmvText_Title[] PROGMEM = "BASIC ENVIRONMENT";
	const char EnvSettingsLightCycleText_SetRise[] PROGMEM = "Sunrise";
	const char EnvSettingsLightCycleText_SetSunset[] PROGMEM = "Sunset";
	const char EnvSettingsLightCycleText_SetLightCycleMode[] PROGMEM = "Default Cycle";
	const char EnvSettingsAlarmThresholdText_OverTemp[] PROGMEM = "OvrTmp Alarm";
	const char EnvSettingsAlarmThresholdText_OverRH[] PROGMEM = "OvrRH Alarm";
	const char EnvSettingsAlarmThresholdText_LogFull[] PROGMEM = "LogFull Alarm";
	const char EnvSettingsFanCircCycleText_Day[] PROGMEM = "CircFan Day";
	const char EnvSettingsFanCircCycleText_Night[] PROGMEM = "CircFan Nght";
	const char EnvSettingsFanCircCycleText_Duration[] PROGMEM = "CircFan Dur";
	const char EnvSettingsFanCircCycleText_Mode[] PROGMEM = "CircFan Mode";
	const char EnvSettingsFanExCycleText_Day[] PROGMEM = "ExFan Day";
	const char EnvSettingsFanExCycleText_Night[] PROGMEM = "ExFan Nght";
	const char EnvSettingsFanExCycleText_Duration[] PROGMEM = "ExFan Dur";
	const char EnvSettingsFanExCycleText_Mode[] PROGMEM = "ExFan Mode";
	const char ScheduledTaskConfig_BulkDeletePromptText[] PROGMEM = "Confirm Delete ALL?";
	const char ScheduledTaskConfig_MenuText_Create[] PROGMEM = "New Schd Task";
	const char ScheduledTaskConfig_MenuText_Delete[] PROGMEM = "Delete Schd Task";
	const char ScheduledTaskConfig_MenuText_BulkDelete[] PROGMEM = "Bulk Delete Tasks";
	const char ScheduledTaskConfig_CreateText_TaskTarget[] PROGMEM = "Target";
	const char ScheduledTaskConfig_CreateText_TaskAction[] PROGMEM = "Action";
	const char ScheduledTaskConfig_CreateText_TaskTime[] PROGMEM = "Time";
	const char ScheduledTaskConfig_CreateSelectText_ByRelay[] PROGMEM = "Single Relay Task";
	const char ScheduledTaskConfig_CreateSelectText_ByGroup[] PROGMEM = "Type/Group Task";
	const char ScheduledTaskConfig_DeleteText_Conf[] PROGMEM = "Confirm Delete?";
	const char ScheduledTaskConfig_MenuText_Set[] PROGMEM = "Set Existing Task";
	const char ScheduledTaskConfig_MenuText_Edit[] PROGMEM = "Edit Existing Task";
	const char ScheduledTaskConfig_MenuText_CreateDelete[] PROGMEM = "Create/Delete Task";
	const char ScheduledTaskConfig_TlmvText_Title[] PROGMEM = "SCHEDULED TASKS";
	const char EventText_NotSet[] PROGMEM = "Event info N/A";
	const char EventText_SystemInitComplete[] PROGMEM = "SysInit OK";
	const char EventText_SystemStartupComplete[] PROGMEM = "SysStart OK";
	const char EventText_PwrRelay_FanOn[] PROGMEM = "CircFans ON";
	const char EventText_PwrRelay_FanOff[] PROGMEM = "CircFans OFF";
	const char EventText_PwrRelay_PumpOn[] PROGMEM = "FloodPump ON";
	const char EventText_PwrRelay_PumpOff[] PROGMEM = "FloodPump OFF";
	const char EventText_PwrRelay_LightOn[] PROGMEM = "Lights ON";
	const char EventText_PwrRelay_LightOff[] PROGMEM = "Lights OFF";
	const char EventText_DataLogger_SdFail[] PROGMEM = "SD Failed init";
	const char EventText_SystemStatus_Ok[] PROGMEM = "OK";
	const char EventText_SystemStatus_Error[] PROGMEM = "ER";
	const char EventText_SystemStatus_Alert[] PROGMEM = "AL";
	const char EventText_SystemStatus_Init[] PROGMEM = "IN";
	const char EventText_Alarm_OverTemp[] PROGMEM = "Alarm-OverTemp";
	const char EventText_Alarm_OverRH[] PROGMEM = "Alarm-OverRH";
	const char EventText_TaskPoolQueuedCount[] PROGMEM = "Tasks queued in taskpool:";
	const char EventText_ScheduledTaskCount[] PROGMEM = "Dormant scheduled tasks:";
	const char EventText_LastUserInputTime[] PROGMEM = "Last user input timestamp:";
	const char EventText_FreeMemoryAvailable[] PROGMEM = "Available system memory:";
	const char EventText_TaskPoolFull[] PROGMEM = "Warning - task pool is full!";
	const char MessageText_TaskRetryFailure[] PROGMEM = "Warning - unhandled task execution failure, exceed max retry. ID:";

	//const char EventText_[] PROGMEM = "";
	//--------------
	//Alarm-OverTemp 

#endif

class Viewstate_String_Generator
{
public:
	Viewstate_String_Generator() {};
	~Viewstate_String_Generator() {};

	//Static char arrays (always in memory)
	static const char airTemperatureSymbol[];
	static const char waterTemperatureSymbol[];
	static const char relativeHumiditySymbol[];
	static const char defaultRelayIdPrefixText[];
	static const char systemModeSymbol[];
	static const char selectArrowRightSymbol[];
	static const char selectArrowDownSymbol[];
	static const char miniPercentSymbol[];
	static const char newlineSymbol[];
	static const char degreeSymbol[];
	static const char percentSymbol[];
	static const char backSymbol[];
	static const char selectBackSymbol[];
	static const char timespanMinuteSymbol[];
	static const char defaultAirTempText[];
	static const char defaultRelHumText[];
	static const char enabledSymbol[];
	static const char disabledSymbol[];
	static const char onSymbol[];
	static const char offSymbol[];
	static const char colonSymbol[];

	//Function to return character array pointer (in-memory OR FlashString)
	static const char * GetViewstateString(const ViewstateStringAlias);

protected:
	//The following character arrays are stored in memory for Win32, and Flash for AVR
	#if defined(TARGET_PLAT_WIN32)

		static const char* const strTable[];
		
		static const char aliasNotSet[];
		static const char componentStateEnabledText[];
		static const char componentStateEnabledAbrvText[];
		static const char componentStateDisabledText[];
		static const char componentStateDisabledAbrvText[];
		static const char componentStateOnText[];
		static const char componentStateOffText[];
		static const char componentStateAutoText[];
		static const char componentStateOverrideText[];
		static const char manualOverrideViewTextTitle[];
		static const char componentFanText[];
		static const char componentPumpText[];
		static const char componentLightText[];

		static const char componentShortNameOutletText[];
		static const char componentShortNameCirculationFanText[];
		static const char componentShortNameExhaustFanText[];
		static const char componentShortNameLightText[];
		static const char componentShortNamePumpText[];
		static const char componentShortNameGroupA[];
		static const char componentShortNameGroupB[];
		static const char componentShortNameGroupC[];
		static const char componentShortNameGroupD[];
		static const char componentTypeLabel[];
		static const char componentGroupLabel[];

		static const char powerRelaySettingsViewTextTitle[];

		static const char defaultTimeText[];
		static const char defaultRuleLineText[];
		static const char defaultTlmvTextSettings[];
		static const char taskAliasDisplayText_NotSet[];
		static const char taskAliasDisplayText_EnablePump[];
		static const char taskAliasDisplayText_DisablePump[];
		static const char taskAliasDisplayText_EnableFans[];
		static const char taskAliasDisplayText_DisableFans[];
		static const char taskAliasDisplayText_EnableLights[];
		static const char taskAliasDisplayText_DisableLights[];
		static const char InputPromptSetTimeText[];
		static const char InputPromptSetThreeSegmentValueText[];
		static const char InputPromptSetTaskAxtionText[];
		static const char DefaultBackText[];
		static const char DefaultYesText[];
		static const char DefaultNoText[];
		static const char DefaultSaveText[];
		static const char DefaultEditText[];
		static const char DefaultConfigText[];
		static const char EnvSettingsText_LightMenu[];
		static const char EnvSettingsText_AirMenu[];
		static const char EnvSettingsText_AlarmMenu[];
		static const char EnvSettingsTlmvText_Title[];
		static const char EnvSettingsLightCycleText_SetRise[];
		static const char EnvSettingsLightCycleText_SetSunset[];
		static const char EnvSettingsLightCycleText_SetLightCycleMode[];
		static const char EnvSettingsAlarmThresholdText_OverTemp[];
		static const char EnvSettingsAlarmThresholdText_OverRH[];
		static const char EnvSettingsAlarmThresholdText_LogFull[];
		static const char EnvSettingsFanCircCycleText_Day[];
		static const char EnvSettingsFanCircCycleText_Night[];
		static const char EnvSettingsFanCircCycleText_Duration[];
		static const char EnvSettingsFanCircCycleText_Mode[];
		static const char EnvSettingsFanExCycleText_Day[];
		static const char EnvSettingsFanExCycleText_Night[];
		static const char EnvSettingsFanExCycleText_Duration[];
		static const char EnvSettingsFanExCycleText_Mode[];
		static const char ScheduledTaskConfig_BulkDeletePromptText[];
		static const char ScheduledTaskConfig_MenuText_Create[];
		static const char ScheduledTaskConfig_MenuText_Delete[];
		static const char ScheduledTaskConfig_MenuText_BulkDelete[];
		static const char ScheduledTaskConfig_CreateText_TaskTarget[];
		static const char ScheduledTaskConfig_CreateText_TaskAction[];
		static const char ScheduledTaskConfig_CreateText_TaskTime[];
		static const char ScheduledTaskConfig_CreateSelectText_ByRelay[];
		static const char ScheduledTaskConfig_CreateSelectText_ByGroup[];
		static const char ScheduledTaskConfig_DeleteText_Conf[];
		static const char ScheduledTaskConfig_MenuText_Set[];
		static const char ScheduledTaskConfig_MenuText_Edit[];
		static const char ScheduledTaskConfig_MenuText_CreateDelete[];
		static const char ScheduledTaskConfig_TlmvText_Title[];
		static const char EventText_NotSet[];
		static const char EventText_SystemInitComplete[];
		static const char EventText_SystemStartupComplete[];
		static const char EventText_PwrRelay_FanOn[];
		static const char EventText_PwrRelay_FanOff[];
		static const char EventText_PwrRelay_PumpOn[];
		static const char EventText_PwrRelay_PumpOff[];
		static const char EventText_PwrRelay_LightOn[];
		static const char EventText_PwrRelay_LightOff[];
		static const char EventText_DataLogger_SdFail[];
		static const char EventText_SystemStatus_Ok[];
		static const char EventText_SystemStatus_Error[];
		static const char EventText_SystemStatus_Alert[];
		static const char EventText_SystemStatus_Init[];
		static const char EventText_Alarm_OverTemp[];
		static const char EventText_Alarm_OverRH[];
		static const char EventText_TaskPoolQueuedCount[];
		static const char EventText_ScheduledTaskCount[];
		static const char EventText_LastUserInputTime[];
		static const char EventText_FreeMemoryAvailable[];
		static const char EventText_TaskPoolFull[];
		static const char MessageText_TaskRetryFailure[];

	#else //AVR

		static char flashStringBuffer[];
		static const char* const strTable[] PROGMEM;

	#endif
};

