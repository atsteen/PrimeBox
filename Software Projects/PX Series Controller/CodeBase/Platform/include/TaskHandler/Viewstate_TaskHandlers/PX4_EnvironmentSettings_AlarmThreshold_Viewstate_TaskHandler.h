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

#include "..\..\SharedStructure\SharedInterface\ITaskHandler.h"
#include "..\..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\..\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\..\SharedStructure\SharedInterface\IModelSystemData.h"
#include "..\..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\..\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\..\SharedStructure\T_DynamicDataProxy.h"

class PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler : public ITaskHandler
{
public:
	PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler(IModelViewstateData * viewstateData, IModelEnvAirData * envAirData, IModelSystemData * systemData, IViewstateMapGenerator * mapGenerator)
		: _viewstateData(viewstateData), _envAirData(envAirData), _systemData(systemData), _mapGenerator(mapGenerator){};
	~PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IModelEnvAirData * _envAirData;
	IViewstateMapGenerator * _mapGenerator;
	IModelSystemData * _systemData;
};

inline bool PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	ISelectableNavigationMap * map = _viewstateData->GetNavigationMap();
	const ViewstateAlias currentViewstate = map->ViewstateAssociation();
	const SelectableViewstateElementAlias currentlySelectedElement = map->CurrentSelection()->selectedElement;
	IDynamicData * dynamicDataProxy;

	// All menu navigation handled by default navigation handler... only need select actions here
	switch (currentlySelectedElement) {

		case SELECTABLE_ENVIRONMENT_OVERTEMP_ALARM_SET_ELEMENT:
			dynamicDataProxy = new T_DynamicDataProxy<IModelEnvAirData, int>(
				currentViewstate,
				currentlySelectedElement,
				ViewstateStringAlias::ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_DAY,
				Viewstate_String_Generator::percentSymbol,
				&IModelEnvAirData::GetAlarmThresholdOverTempF,
				&IModelEnvAirData::SetAlarmThresholdOverTempF,
				_envAirData
				);			

			_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
			_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_THREESEGMENT));
			return true;

		case SELECTABLE_ENVIRONMENT_OVERHUM_ALARM_SET_ELEMENT:
			dynamicDataProxy = new T_DynamicDataProxy<IModelEnvAirData, int>(
				currentViewstate,
				currentlySelectedElement,
				ViewstateStringAlias::ENV_SETTINGS_FAN_CIRC_CYCLE_TEXT_NIGHT,
				Viewstate_String_Generator::percentSymbol,
				&IModelEnvAirData::GetAlarmThresholdOverRH,
				&IModelEnvAirData::SetAlarmThresholdOverRH,
				_envAirData
				);

			_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
			_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_THREESEGMENT));
			return true;

		case SELECTABLE_ENVIRONMENT_LOGFULL_ALARM_SET_ELEMENT:
			dynamicDataProxy = new T_DynamicDataProxy<IModelSystemData, bool>(
				currentViewstate,
				currentlySelectedElement,
				ViewstateStringAlias::ENV_SETTINGS_ALARM_THRESHOLD_TEXT_LOGFULL,
				Viewstate_String_Generator::systemModeSymbol,
				&IModelSystemData::GetLogAlarmDefaultState,
				&IModelSystemData::SetLogAlarmDefaultState,
				_systemData
				);

			_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
			_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ENABLE_DISABLE));
			return true;		
	}

	return false;
}

inline bool PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	// This handler only handles TASKALIAS_NAVIGATION_MENU_SELECT tasks for the VIEWSTATEALIAS_ENVIRONMENT_ALARM_THRESHOLDS_VIEW
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_ALARM_THRESHOLDS_VIEW) { return false; }
	
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_EnvironmentSettings_AlarmThreshold_Viewstate_TaskHandler::FlagStateChange()
{
	return true;
}