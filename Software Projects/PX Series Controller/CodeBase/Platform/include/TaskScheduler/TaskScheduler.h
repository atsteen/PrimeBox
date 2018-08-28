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

#include "..\SharedStructure\TaskItemPool.h"
#include "..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\SharedStructure\SharedInterface\ITextDisplay.h"

class TaskScheduler
{
public:
	TaskScheduler(IModelTaskData * taskData, IRtcLogger * rtcLogger) :
		_taskData(taskData), _rtcLogger(rtcLogger){};
	~TaskScheduler() {};

	void QueueScheduledTasks();
	void FreeScheduledTask(ScheduledTaskDetail *);
	void FreeScheduledTask(const int);

private:
	long _lastScheduledTaskExecution = 0;
	IModelTaskData * _taskData;
	IRtcLogger * _rtcLogger;
};

