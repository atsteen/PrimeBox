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
#include "..\..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\..\SharedStructure\SharedInterface\IModelSystemData.h"
#include "..\..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\..\SharedStructure\SharedInterface\IModelEnvLightData.h"
#include "..\..\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\..\SharedStructure\SharedInterface\IAirSensor.h"
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"
#include "..\..\SharedStructure\EventLog_Item_Collection.h"
#include "..\Group\IViewstate_Group.h"

class Viewstate_Group_PX4 : public IViewstate_Group
{
public:
	Viewstate_Group_PX4(IModelSystemData * systemData,
		IModelTaskData * taskData,
		IModelEnvLightData * lightData,
		IModelEnvAirData * airData,
		IAirSensor * airSensor,
		EventLog_Item_Collection * eventCollection,
		IModelViewstateData * viewStateData,
		IPowerRelayArray * relayArray
	);
	~Viewstate_Group_PX4() {};

	// Inherited via IViewstate_Group
	virtual ITextViewstate * GetViewstateByAlias(const ViewstateAlias) override;

private:
	IModelSystemData * _systemData = {};
	IModelTaskData * _taskData = {};
	IModelEnvLightData * _lightData = {};
	IModelEnvAirData * _airData = {};
	IAirSensor * _airSensor = {};
	ITextViewstate * _requestedViewstate = {};
	IModelViewstateData * _viewStateData = {};
	IPowerRelayArray * _relayArray = {};
	EventLog_Item_Collection * _eventCollection = {};
};
