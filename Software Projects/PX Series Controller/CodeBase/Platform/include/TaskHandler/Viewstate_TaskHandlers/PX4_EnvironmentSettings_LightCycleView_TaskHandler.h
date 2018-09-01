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
#include "..\..\SharedStructure\SharedInterface\IModelEnvLightData.h"
#include "..\..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\..\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\..\SharedStructure\T_DynamicDataProxy.h"

class PX4_EnvironmentSettings_LightCycleView_TaskHandler
	: public ITaskHandler
{
public:
	PX4_EnvironmentSettings_LightCycleView_TaskHandler(IModelViewstateData * viewstateData, IModelEnvLightData * envLightData, IViewstateMapGenerator * mapGenerator, INavigationTones * navTonePlayer)
		: _viewstateData(viewstateData), _envLightData(envLightData), _mapGenerator(mapGenerator), _navTonePlayer(navTonePlayer){};

	~PX4_EnvironmentSettings_LightCycleView_TaskHandler() {};

	static bool HandleIt(){};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IModelEnvLightData * _envLightData;
	IViewstateMapGenerator * _mapGenerator;
	INavigationTones * _navTonePlayer;
};

inline bool PX4_EnvironmentSettings_LightCycleView_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	// This handler only handles TASKALIAS_NAVIGATION_MENU_SELECT tasks for the VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SUNRISE_SUNSET_VIEW) { return false; }

	if (_taskItem->GetTaskAssociation() != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline bool PX4_EnvironmentSettings_LightCycleView_TaskHandler::HandleTask(TaskItem * ti)
{
	if (!_CanHandleTask(ti)) { return false; }

	ISelectableNavigationMap * map = _viewstateData->GetNavigationMap();
	const ViewstateAlias currentViewstate = map->ViewstateAssociation();
	const SelectableViewstateElementAlias currentlySelectedElement = map->CurrentSelection()->selectedElement;
	IDynamicData * dynamicDataProxy;

	switch (currentlySelectedElement) {
	case SELECTABLE_ENVIRONMENT_SUNRISE_SET_ELEMENT:
		dynamicDataProxy = new T_DynamicDataProxy<IModelEnvLightData, TimeSignature>(
			currentViewstate,
			currentlySelectedElement,
			ViewstateStringAlias::ENV_SETTINGS_LIGHTCYCLE_TEXT_SETSUNRISE,
			Viewstate_String_Generator::timespanMinuteSymbol,
			&IModelEnvLightData::GetDefaultSunriseTime,
			&IModelEnvLightData::SetDefaultSunriseTime,
			_envLightData
			);

		_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
		_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_TIME));
		_navTonePlayer->playSelectTone();
		return true;

	case SELECTABLE_ENVIRONMENT_SUNSET_SET_ELEMENT:
		dynamicDataProxy = new T_DynamicDataProxy<IModelEnvLightData, TimeSignature>(
			currentViewstate,
			currentlySelectedElement,
			ViewstateStringAlias::ENV_SETTINGS_LIGHTCYCLE_TEXT_SETSUNSET,
			Viewstate_String_Generator::timespanMinuteSymbol,
			&IModelEnvLightData::GetDefaultSunsetTime,
			&IModelEnvLightData::SetDefaultSunsetTime,
			_envLightData
			);

		_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
		_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_TIME));
		_navTonePlayer->playSelectTone(); 
		return true;

	case SELECTABLE_ENVIRONMENT_SUN_CYCLE_SET_ELEMENT:
		dynamicDataProxy = new T_DynamicDataProxy<IModelEnvLightData, bool>(
			currentViewstate,
			currentlySelectedElement,
			ViewstateStringAlias::ENV_SETTINGS_LIGHTCYCLE_TEXT_SETLIGHTCYCLEMODE,
			Viewstate_String_Generator::systemModeSymbol,
			&IModelEnvLightData::GetLightCycleDefaultState,
			&IModelEnvLightData::SetLightCycleDefaultState,
			_envLightData
			);

		_viewstateData->RegisterDynamicDataProxy(dynamicDataProxy);
		_viewstateData->SetNavigationMap(_mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_BOOLEAN_ENABLE_DISABLE));
		_navTonePlayer->playSelectTone(); 
		return true;

	default:
		ISelectableNavigationMap * newMap = _mapGenerator->GenerateMap(ViewstateAlias::VIEWSTATEALIAS_ENVIRONMENT_SETTINGS_VIEW);
		_viewstateData->SetNavigationMap(newMap);
		_navTonePlayer->playBackSelectTone();
	}

	return false;
}

inline const bool PX4_EnvironmentSettings_LightCycleView_TaskHandler::FlagStateChange()
{
	return true;
}