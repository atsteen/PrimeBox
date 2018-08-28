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
#include "..\SharedStructure\SharedInterface\IModelViewstateData.h"

class Viewstate_PX4_ScheduledTasksConfig_BulkDeleteTaskView :
	public Viewstate_PX4
{
public:
	Viewstate_PX4_ScheduledTasksConfig_BulkDeleteTaskView(IModelViewstateData * viewstateData);
	virtual ~Viewstate_PX4_ScheduledTasksConfig_BulkDeleteTaskView() override;
	virtual char * RenderText(char *, const int) override;

private:
	IModelViewstateData * _viewstateData;
};

