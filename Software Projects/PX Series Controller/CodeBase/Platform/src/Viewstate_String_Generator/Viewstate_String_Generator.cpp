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

#include "..\..\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

const char Viewstate_String_Generator::airTemperatureSymbol[] = { (char)180, '\0' };
const char Viewstate_String_Generator::waterTemperatureSymbol[] = { (char)182, '\0' };
const char Viewstate_String_Generator::relativeHumiditySymbol[] = { (char)247, '\0' };
const char Viewstate_String_Generator::systemModeSymbol[] = { (char)233, '\0' };
const char Viewstate_String_Generator::selectArrowRightSymbol[] = { (char)175, '\0' };
const char Viewstate_String_Generator::selectArrowDownSymbol[] = { (char)243, '\0' };
const char Viewstate_String_Generator::miniPercentSymbol[] = { (char)235, '\0' };
const char Viewstate_String_Generator::defaultAirTempText[] = { '-', '-', '\0' };
const char Viewstate_String_Generator::defaultRelHumText[] = { '-', '-', '\0' };
const char Viewstate_String_Generator::defaultRelayIdPrefixText[] = { 'R', '#', '\0' };
const char Viewstate_String_Generator::newlineSymbol[] = { '\n', '\0' };
const char Viewstate_String_Generator::degreeSymbol[] = { (char)223, '\0' };
const char Viewstate_String_Generator::percentSymbol[] = "%";
const char Viewstate_String_Generator::timespanMinuteSymbol[] = "m";
const char Viewstate_String_Generator::backSymbol[] = { (char)176, '\0' };
const char Viewstate_String_Generator::selectBackSymbol[] = { (char)178, '\0' };
const char Viewstate_String_Generator::enabledSymbol[] = { 'Y', '\0' };
const char Viewstate_String_Generator::disabledSymbol[] = { 'N', '\0' };
const char Viewstate_String_Generator::onSymbol[] = { '+', '\0' };
const char Viewstate_String_Generator::offSymbol[] = { '-', '\0' };
const char Viewstate_String_Generator::colonSymbol[] = { ':', '\0' };

//////////////////////////////
#if defined(TARGET_PLAT_WIN32)

	const char Viewstate_String_Generator::aliasNotSet[] = "???";
	const char Viewstate_String_Generator::componentStateEnabledText[] = "[ENABLED ]";
	const char Viewstate_String_Generator::componentStateEnabledAbrvText[] = "[ENA]";
	const char Viewstate_String_Generator::componentStateDisabledText[] = "[DISABLED]";
	const char Viewstate_String_Generator::componentStateDisabledAbrvText[] = "[DIS]";
	const char Viewstate_String_Generator::componentStateOnText[] = "[ ON]";
	const char Viewstate_String_Generator::componentStateOffText[] = "[OFF]";
	const char Viewstate_String_Generator::componentStateAutoText[] = "[AUTO]";
	const char Viewstate_String_Generator::componentStateOverrideText[] = "OVR-";
	const char Viewstate_String_Generator::manualOverrideViewTextTitle[] = "MANUAL OVERRIDES";
	const char Viewstate_String_Generator::componentFanText[] = "FANS";
	const char Viewstate_String_Generator::componentPumpText[] = "PUMP";
	const char Viewstate_String_Generator::componentLightText[] = "LIGHTS";

	const char Viewstate_String_Generator::componentShortNameOutletText[] = "Outlet";
	const char Viewstate_String_Generator::componentShortNameCirculationFanText[] = "FanCirc";
	const char Viewstate_String_Generator::componentShortNameExhaustFanText[] = "FanExh";
	const char Viewstate_String_Generator::componentShortNameLightText[] = "Light";
	const char Viewstate_String_Generator::componentShortNamePumpText[] = "Pump";
	const char Viewstate_String_Generator::componentShortNameGroupA[] = "GrpA";
	const char Viewstate_String_Generator::componentShortNameGroupB[] = "GrpB";
	const char Viewstate_String_Generator::componentShortNameGroupC[] = "GrpC";
	const char Viewstate_String_Generator::componentShortNameGroupD[] = "GrpD";

	const char Viewstate_String_Generator::componentTypeLabel[] = "Type";
	const char Viewstate_String_Generator::componentGroupLabel[] = "Group";

	const char Viewstate_String_Generator::powerRelaySettingsViewTextTitle[] = "RELAY CONFIGURATION";

	const char Viewstate_String_Generator::defaultTimeText[] = "[##:##]";
	const char Viewstate_String_Generator::defaultRuleLineText[] = "--------------------";
	const char Viewstate_String_Generator::defaultTlmvTextSettings[] = "-----SETTINGS----";
	const char Viewstate_String_Generator::taskAliasDisplayText_NotSet[] = "[NotSet]";
	const char Viewstate_String_Generator::taskAliasDisplayText_EnablePump[] = "[Pmp_On]";
	const char Viewstate_String_Generator::taskAliasDisplayText_DisablePump[] = "[PmpOff]";
	const char Viewstate_String_Generator::taskAliasDisplayText_EnableFans[] = "[Fan_On]";
	const char Viewstate_String_Generator::taskAliasDisplayText_DisableFans[] = "[FanOff]";
	const char Viewstate_String_Generator::taskAliasDisplayText_EnableLights[] = "[Lht_On]";
	const char Viewstate_String_Generator::taskAliasDisplayText_DisableLights[] = "[LhtOff]";
	const char Viewstate_String_Generator::InputPromptSetTimeText[] = "Set Task Time";
	const char Viewstate_String_Generator::InputPromptSetThreeSegmentValueText[] = "Set value";
	const char Viewstate_String_Generator::InputPromptSetTaskAxtionText[] = "Set action";
	const char Viewstate_String_Generator::DefaultBackText[] = "BACK";
	const char Viewstate_String_Generator::DefaultYesText[] = "[YES]";
	const char Viewstate_String_Generator::DefaultNoText[] = "[NO]";
	const char Viewstate_String_Generator::DefaultSaveText[] = "SAVE";
	const char Viewstate_String_Generator::DefaultEditText[] = "EDIT";
	const char Viewstate_String_Generator::DefaultConfigText[] = "Config";
	const char Viewstate_String_Generator::EnvSettingsText_LightMenu[] = "Sunrise/Set Default";
	const char Viewstate_String_Generator::EnvSettingsText_AirMenu[] = "Air Circ DutyCycles";
	const char Viewstate_String_Generator::EnvSettingsText_AlarmMenu[] = "Alarm Thresholds";
	const char Viewstate_String_Generator::EnvSettingsTlmvText_Title[] = "BASIC ENVIRONMENT";
	const char Viewstate_String_Generator::EnvSettingsLightCycleText_SetRise[] = "Sunrise";
	const char Viewstate_String_Generator::EnvSettingsLightCycleText_SetSunset[] = "Sunset";
	const char Viewstate_String_Generator::EnvSettingsLightCycleText_SetLightCycleMode[] = "Default Cycle";
	const char Viewstate_String_Generator::EnvSettingsAlarmThresholdText_OverTemp[] = "OvrTmp Alarm";
	const char Viewstate_String_Generator::EnvSettingsAlarmThresholdText_OverRH[] = "OvrRH Alarm";
	const char Viewstate_String_Generator::EnvSettingsAlarmThresholdText_LogFull[] = "LogFull Alarm";
	const char Viewstate_String_Generator::EnvSettingsFanCircCycleText_Day[] = "CircFan Day";
	const char Viewstate_String_Generator::EnvSettingsFanCircCycleText_Night[] = "CircFan Nght";
	const char Viewstate_String_Generator::EnvSettingsFanCircCycleText_Duration[] = "CircFan Dur";
	const char Viewstate_String_Generator::EnvSettingsFanCircCycleText_Mode[] = "CircFan Mode";
	const char Viewstate_String_Generator::EnvSettingsFanExCycleText_Day[] = "ExFan Day";
	const char Viewstate_String_Generator::EnvSettingsFanExCycleText_Night[] = "ExFan Nght";
	const char Viewstate_String_Generator::EnvSettingsFanExCycleText_Duration[] = "ExFan Dur";
	const char Viewstate_String_Generator::EnvSettingsFanExCycleText_Mode[] = "ExFan Mode";
	const char Viewstate_String_Generator::ScheduledTaskConfig_BulkDeletePromptText[] = "Confirm Delete ALL?";
	const char Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Create[] = "New Schd Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Delete[] = "Delete Schd Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_MenuText_BulkDelete[] = "Bulk Delete Tasks";
	const char Viewstate_String_Generator::ScheduledTaskConfig_CreateText_TaskTarget[] = "Target";
	const char Viewstate_String_Generator::ScheduledTaskConfig_CreateText_TaskAction[] = "Action";
	const char Viewstate_String_Generator::ScheduledTaskConfig_CreateText_TaskTime[] = "Time";
	const char Viewstate_String_Generator::ScheduledTaskConfig_CreateSelectText_ByRelay[] = "Single Relay Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_CreateSelectText_ByGroup[] = "Type/Group Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_DeleteText_Conf[] = "Confirm Delete?";
	const char Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Set[] = "Set Existing Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Edit[] = "Edit Existing Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_MenuText_CreateDelete[] = "Create/Delete Task";
	const char Viewstate_String_Generator::ScheduledTaskConfig_TlmvText_Title[] = "SCHEDULED TASKS";
	const char Viewstate_String_Generator::EventText_NotSet[] = "Event info N/A";
	const char Viewstate_String_Generator::EventText_SystemInitComplete[] = "SysInit OK";
	const char Viewstate_String_Generator::EventText_SystemStartupComplete[] = "SysStart OK";
	const char Viewstate_String_Generator::EventText_PwrRelay_FanOn[] = "CircFans ON";
	const char Viewstate_String_Generator::EventText_PwrRelay_FanOff[] = "CircFans OFF";
	const char Viewstate_String_Generator::EventText_PwrRelay_PumpOn[] = "FloodPump ON";
	const char Viewstate_String_Generator::EventText_PwrRelay_PumpOff[] = "FloodPump OFF";
	const char Viewstate_String_Generator::EventText_PwrRelay_LightOn[] = "Lights ON";
	const char Viewstate_String_Generator::EventText_PwrRelay_LightOff[] = "Lights OFF";
	const char Viewstate_String_Generator::EventText_DataLogger_SdFail[] = "SD Failed init";
	const char Viewstate_String_Generator::EventText_SystemStatus_Ok[] = "OK";
	const char Viewstate_String_Generator::EventText_SystemStatus_Error[] = "ER";
	const char Viewstate_String_Generator::EventText_SystemStatus_Alert[] = "AL";
	const char Viewstate_String_Generator::EventText_SystemStatus_Init[] = "IN";
	const char Viewstate_String_Generator::EventText_Alarm_OverTemp[] = "Alarm-OverTemp";
	const char Viewstate_String_Generator::EventText_Alarm_OverRH[] = "Alarm-OverRH";
	const char Viewstate_String_Generator::EventText_TaskPoolQueuedCount[] = "Tasks queued in taskpool:";
	const char Viewstate_String_Generator::EventText_ScheduledTaskCount[] = "Dormant scheduled tasks:";
	const char Viewstate_String_Generator::EventText_LastUserInputTime[] = "Last user input timestamp:";
	const char Viewstate_String_Generator::EventText_FreeMemoryAvailable[] = "Available system memory:";
	const char Viewstate_String_Generator::EventText_TaskPoolFull[] = "Warning - task pool is full!";
	const char Viewstate_String_Generator::EventText_TemperatureState[] = "Current Temperature:";
	const char Viewstate_String_Generator::EventText_HumidityState[] = "Current Humidity:";
	const char Viewstate_String_Generator::MessageText_TaskRetryFailure[] = "Warning - unhandled task execution failure, exceed max retry. ID:";


	const char* const Viewstate_String_Generator::strTable[] = {
		
		//Order MUST match ViewstateStringAlias, lookup is based off the enum value
		Viewstate_String_Generator::aliasNotSet,
		Viewstate_String_Generator::componentStateEnabledText,
		Viewstate_String_Generator::componentStateEnabledAbrvText,
		Viewstate_String_Generator::componentStateDisabledText,
		Viewstate_String_Generator::componentStateDisabledAbrvText,
		Viewstate_String_Generator::componentStateOnText,
		Viewstate_String_Generator::componentStateOffText,
		Viewstate_String_Generator::componentStateAutoText,
		Viewstate_String_Generator::componentStateOverrideText,
		Viewstate_String_Generator::manualOverrideViewTextTitle,		
		//9
		Viewstate_String_Generator::componentFanText,
		Viewstate_String_Generator::componentPumpText,
		Viewstate_String_Generator::componentLightText,
		Viewstate_String_Generator::componentShortNameOutletText,
		Viewstate_String_Generator::componentShortNameCirculationFanText,
		Viewstate_String_Generator::componentShortNameExhaustFanText,
		Viewstate_String_Generator::componentShortNameLightText,
		Viewstate_String_Generator::componentShortNamePumpText,
		Viewstate_String_Generator::componentShortNameGroupA,
		Viewstate_String_Generator::componentShortNameGroupB,
		//19
		Viewstate_String_Generator::componentShortNameGroupC,		
		Viewstate_String_Generator::componentShortNameGroupD,
		Viewstate_String_Generator::componentTypeLabel,
		Viewstate_String_Generator::componentGroupLabel,
		Viewstate_String_Generator::powerRelaySettingsViewTextTitle,
		Viewstate_String_Generator::defaultTimeText,
		Viewstate_String_Generator::defaultRuleLineText,
		Viewstate_String_Generator::defaultTlmvTextSettings,
		Viewstate_String_Generator::taskAliasDisplayText_NotSet,
		Viewstate_String_Generator::taskAliasDisplayText_EnablePump,
		//29
		Viewstate_String_Generator::taskAliasDisplayText_DisablePump,
		Viewstate_String_Generator::taskAliasDisplayText_EnableFans,
		Viewstate_String_Generator::taskAliasDisplayText_DisableFans,
		Viewstate_String_Generator::taskAliasDisplayText_EnableLights,
		Viewstate_String_Generator::taskAliasDisplayText_DisableLights,
		Viewstate_String_Generator::InputPromptSetTimeText,
		Viewstate_String_Generator::InputPromptSetThreeSegmentValueText,
		Viewstate_String_Generator::InputPromptSetTaskAxtionText,
		Viewstate_String_Generator::DefaultBackText,
		Viewstate_String_Generator::DefaultYesText,
		//39
		Viewstate_String_Generator::DefaultNoText,
		Viewstate_String_Generator::DefaultSaveText,
		Viewstate_String_Generator::DefaultEditText,
		Viewstate_String_Generator::DefaultConfigText,
		Viewstate_String_Generator::EnvSettingsText_LightMenu,
		Viewstate_String_Generator::EnvSettingsText_AirMenu,
		Viewstate_String_Generator::EnvSettingsText_AlarmMenu,
		Viewstate_String_Generator::EnvSettingsTlmvText_Title,
		Viewstate_String_Generator::EnvSettingsLightCycleText_SetRise,
		Viewstate_String_Generator::EnvSettingsLightCycleText_SetSunset,
		//49
		Viewstate_String_Generator::EnvSettingsLightCycleText_SetLightCycleMode,
		Viewstate_String_Generator::EnvSettingsAlarmThresholdText_OverTemp,
		Viewstate_String_Generator::EnvSettingsAlarmThresholdText_OverRH,
		Viewstate_String_Generator::EnvSettingsAlarmThresholdText_LogFull,
		Viewstate_String_Generator::EnvSettingsFanCircCycleText_Day,
		Viewstate_String_Generator::EnvSettingsFanCircCycleText_Night,
		Viewstate_String_Generator::EnvSettingsFanCircCycleText_Duration,
		Viewstate_String_Generator::EnvSettingsFanCircCycleText_Mode,
		Viewstate_String_Generator::EnvSettingsFanExCycleText_Day,
		Viewstate_String_Generator::EnvSettingsFanExCycleText_Night,
		//59
		Viewstate_String_Generator::EnvSettingsFanExCycleText_Duration,
		Viewstate_String_Generator::EnvSettingsFanExCycleText_Mode,
		Viewstate_String_Generator::ScheduledTaskConfig_BulkDeletePromptText,
		Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Create,
		Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Delete,
		Viewstate_String_Generator::ScheduledTaskConfig_MenuText_BulkDelete,
		Viewstate_String_Generator::ScheduledTaskConfig_CreateText_TaskTarget,
		Viewstate_String_Generator::ScheduledTaskConfig_CreateText_TaskAction,
		Viewstate_String_Generator::ScheduledTaskConfig_CreateText_TaskTime,
		Viewstate_String_Generator::ScheduledTaskConfig_CreateSelectText_ByRelay,
		//69
		Viewstate_String_Generator::ScheduledTaskConfig_CreateSelectText_ByGroup,
		Viewstate_String_Generator::ScheduledTaskConfig_DeleteText_Conf,
		Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Set,
		Viewstate_String_Generator::ScheduledTaskConfig_MenuText_Edit,
		Viewstate_String_Generator::ScheduledTaskConfig_MenuText_CreateDelete,
		Viewstate_String_Generator::ScheduledTaskConfig_TlmvText_Title,
		Viewstate_String_Generator::EventText_NotSet,
		Viewstate_String_Generator::EventText_SystemInitComplete,
		Viewstate_String_Generator::EventText_SystemStartupComplete,
		Viewstate_String_Generator::EventText_PwrRelay_FanOn,
		//79
		Viewstate_String_Generator::EventText_PwrRelay_FanOff,
		Viewstate_String_Generator::EventText_PwrRelay_PumpOn,
		Viewstate_String_Generator::EventText_PwrRelay_PumpOff,
		Viewstate_String_Generator::EventText_PwrRelay_LightOn,
		Viewstate_String_Generator::EventText_PwrRelay_LightOff,
		Viewstate_String_Generator::EventText_DataLogger_SdFail,
		Viewstate_String_Generator::EventText_SystemStatus_Ok,
		Viewstate_String_Generator::EventText_SystemStatus_Error,
		Viewstate_String_Generator::EventText_SystemStatus_Alert,
		Viewstate_String_Generator::EventText_SystemStatus_Init,
		//89
		Viewstate_String_Generator::EventText_Alarm_OverTemp,
		Viewstate_String_Generator::EventText_Alarm_OverRH,
		Viewstate_String_Generator::EventText_TaskPoolQueuedCount,
		Viewstate_String_Generator::EventText_ScheduledTaskCount,
		Viewstate_String_Generator::EventText_LastUserInputTime,
		Viewstate_String_Generator::EventText_FreeMemoryAvailable,
		Viewstate_String_Generator::EventText_TaskPoolFull,
		Viewstate_String_Generator::EventText_TemperatureState,
		Viewstate_String_Generator::EventText_HumidityState,
		Viewstate_String_Generator::MessageText_TaskRetryFailure
	};

	const char * Viewstate_String_Generator::GetViewstateString(const ViewstateStringAlias fsaWin32)
	{
		return strTable[fsaWin32];
	}

///////////
#else //AVR

	char Viewstate_String_Generator::flashStringBuffer[128] = "\0";

	const char* const Viewstate_String_Generator::strTable[] = {
		
			//Order MUST match ViewstateStringAlias, lookup is based off the enum value
			aliasNotSet,
			componentStateEnabledText,
			componentStateEnabledAbrvText,
			componentStateDisabledText,
			componentStateDisabledAbrvText,
			componentStateOnText,
			componentStateOffText,
			componentStateAutoText,
			componentStateOverrideText,
			manualOverrideViewTextTitle,
			//9
			componentFanText,
			componentPumpText,
			componentLightText,
			componentShortNameOutletText,
			componentShortNameCirculationFanText,
			componentShortNameExhaustFanText,
			componentShortNameLightText,
			componentShortNamePumpText,
			componentShortNameGroupA,
			componentShortNameGroupB,
			//19
			componentShortNameGroupC,
			componentShortNameGroupD,
			componentTypeLabel,
			componentGroupLabel,
			powerRelaySettingsViewTextTitle,
			defaultTimeText,
			defaultRuleLineText,
			defaultTlmvTextSettings,
			taskAliasDisplayText_NotSet,
			taskAliasDisplayText_EnablePump,
			//29
			taskAliasDisplayText_DisablePump,
			taskAliasDisplayText_EnableFans,
			taskAliasDisplayText_DisableFans,
			taskAliasDisplayText_EnableLights,
			taskAliasDisplayText_DisableLights,
			InputPromptSetTimeText,
			InputPromptSetThreeSegmentValueText,
			InputPromptSetTaskAxtionText,
			DefaultBackText,
			DefaultYesText,
			//39
			DefaultNoText,
			DefaultSaveText,
			DefaultEditText,
			DefaultConfigText,
			EnvSettingsText_LightMenu,
			EnvSettingsText_AirMenu,
			EnvSettingsText_AlarmMenu,
			EnvSettingsTlmvText_Title,
			EnvSettingsLightCycleText_SetRise,
			EnvSettingsLightCycleText_SetSunset,
			//49
			EnvSettingsLightCycleText_SetLightCycleMode,
			EnvSettingsAlarmThresholdText_OverTemp,
			EnvSettingsAlarmThresholdText_OverRH,
			EnvSettingsAlarmThresholdText_LogFull,
			EnvSettingsFanCircCycleText_Day,
			EnvSettingsFanCircCycleText_Night,
			EnvSettingsFanCircCycleText_Duration,
			EnvSettingsFanCircCycleText_Mode,
			EnvSettingsFanExCycleText_Day,
			EnvSettingsFanExCycleText_Night,
			//59
			EnvSettingsFanExCycleText_Duration,
			EnvSettingsFanExCycleText_Mode,
			ScheduledTaskConfig_BulkDeletePromptText,
			ScheduledTaskConfig_MenuText_Create,
			ScheduledTaskConfig_MenuText_Delete,
			ScheduledTaskConfig_MenuText_BulkDelete,
			ScheduledTaskConfig_CreateText_TaskTarget,
			ScheduledTaskConfig_CreateText_TaskAction,
			ScheduledTaskConfig_CreateText_TaskTime,
			ScheduledTaskConfig_CreateSelectText_ByRelay,
			//69
			ScheduledTaskConfig_CreateSelectText_ByGroup,
			ScheduledTaskConfig_DeleteText_Conf,
			ScheduledTaskConfig_MenuText_Set,
			ScheduledTaskConfig_MenuText_Edit,
			ScheduledTaskConfig_MenuText_CreateDelete,
			ScheduledTaskConfig_TlmvText_Title,
			EventText_NotSet,
			EventText_SystemInitComplete,
			EventText_SystemStartupComplete,
			EventText_PwrRelay_FanOn,
			//79
			EventText_PwrRelay_FanOff,
			EventText_PwrRelay_PumpOn,
			EventText_PwrRelay_PumpOff,
			EventText_PwrRelay_LightOn,
			EventText_PwrRelay_LightOff,
			EventText_DataLogger_SdFail,
			EventText_SystemStatus_Ok,
			EventText_SystemStatus_Error,
			EventText_SystemStatus_Alert,
			EventText_SystemStatus_Init,
			//89
			EventText_Alarm_OverTemp,
			EventText_Alarm_OverRH,
			EventText_TaskPoolQueuedCount,
			EventText_ScheduledTaskCount,
			EventText_LastUserInputTime,
			EventText_FreeMemoryAvailable,
			EventText_TaskPoolFull,
			EventText_TemperatureState,
			EventText_HumidityState,
			MessageText_TaskRetryFailure
			//99
		};

	const char * Viewstate_String_Generator::GetViewstateString(const ViewstateStringAlias fsaAVR)
	{
		strcpy_P(flashStringBuffer, (char*)pgm_read_word(&(strTable[fsaAVR])));
	}

#endif


