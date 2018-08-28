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
#include "Viewstate_PX4.h"
#include "..\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\..\include\SharedStructure\SharedInterface\IModelEnvAirData.h"
#include "..\..\include\SharedStructure\SharedInterface\IModelViewstateData.h"

class Viewstate_PX4_EnvironmentSettings_FanCycleView :
	public Viewstate_PX4
{
public:
	Viewstate_PX4_EnvironmentSettings_FanCycleView(IModelEnvAirData * airData, IModelViewstateData * viewstateData);
	virtual ~Viewstate_PX4_EnvironmentSettings_FanCycleView() override;

	virtual char * RenderText(char *, const int) override;
	virtual char * RenderElementListText(char *, const int, VElementList, SelectableViewstateElementAlias);

private:
	IModelEnvAirData * _airData;
	IModelViewstateData * _viewstateData;
};

