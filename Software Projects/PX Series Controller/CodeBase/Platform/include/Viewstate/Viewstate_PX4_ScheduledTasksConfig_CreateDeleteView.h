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
#include "..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\SharedStructure\SharedInterface\IModelViewstateData.h"

class Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView :
	public Viewstate_PX4
{
public:
	Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView(IModelTaskData * taskData, IModelViewstateData * viewstateData);
	virtual ~Viewstate_PX4_ScheduledTasksConfig_CreateDeleteView() override;

	virtual char * RenderText(char *, const int) override;

private:
	IModelTaskData * _taskData;
	IModelViewstateData * _viewstateData;
};

