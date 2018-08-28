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
#include "..\SharedStructure\SharedInterface\ITaskHandlerFactory.h"
#include "..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\SharedStructure\SharedInterface\IModelEnvLightData.h"
#include "..\SharedStructure\SharedInterface\IModelSystemData.h"
#include "..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\SharedStructure\SharedInterface\IPowerRelayArray.h"
#include "..\SharedStructure\SharedInterface\ITextDisplay.h"
#include "..\SharedStructure\SharedInterface\INavigationTones.h"

class TaskHandlerFactory_PX4 : public ITaskHandlerFactory
{
public:
	TaskHandlerFactory_PX4(IModelViewstateData * viewstateData,
		IViewstateMapGenerator * mapGenerator,
		IModelEnvAirData * environmentAirData,
		IModelEnvLightData * environmentLightData,
		IModelSystemData * systemData,
		IModelTaskData * taskData,
		IRtcLogger * rtcLogger,
		IPowerRelayArray * powerRelays,
		ITextDisplay * display,
		INavigationTones * navTonePlayer
	)
		: _viewstateData(viewstateData),
		_mapGenerator(mapGenerator),
		_environmentAirData(environmentAirData),
		_environmentLightData(environmentLightData),
		_systemData(systemData),
		_taskData(taskData),
		_rtcLogger(rtcLogger),
		_powerRelays(powerRelays),
		_display(display),
		_navTonePlayer(navTonePlayer)
	{}

	virtual ~TaskHandlerFactory_PX4() override;

	// Inherited via ITaskHandlerFactory
	virtual T_List<ITaskHandler&> * MakeHandlerList() override;

private:
	IModelViewstateData * _viewstateData;
	IViewstateMapGenerator * _mapGenerator;
	T_List<ITaskHandler&> _taskHandlers;
	IModelEnvAirData * _environmentAirData;
	IModelEnvLightData * _environmentLightData;
	IModelSystemData * _systemData;
	IModelTaskData * _taskData;
	IRtcLogger * _rtcLogger;
	IPowerRelayArray * _powerRelays;
	ITextDisplay * _display;
	INavigationTones * _navTonePlayer;
};