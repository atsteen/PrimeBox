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

#include "..\..\include\TaskScheduler\TaskScheduler.h"

void TaskScheduler::QueueScheduledTasks()
{//todo... this whole method needs a rewrite... better resiliency.. support whole minute task scheduling with executed task history

	long currentTicks = _rtcLogger->CurrentTime().secondstime();

	if ((_lastScheduledTaskExecution + 60) > currentTicks) { return; }

	//iterate through schedtaskdetails
	for (int i = 0; i < SCHEDULED_TASK_DETAIL_COUNT; ++i)
	{		
		ScheduledTaskDetail * taskDetail = _taskData->GetScheduledTaskDetailByIndex(i);

		if (*taskDetail->GetScheduledTaskAlias() != TASKALIAS_NOT_SET)
		{
			if ((taskDetail->GetScheduledTaskExecutionTime()->hour() == _rtcLogger->CurrentTime().hour())
				&& (taskDetail->GetScheduledTaskExecutionTime()->minute() == _rtcLogger->CurrentTime().minute()))
			{
				TaskItem * taskItem = TaskItemPool::GetInstance().GetNewTaskItem();
				if (!taskItem) { return; } //todo... report no available TaskPool items

				taskItem->SetTaskAlias(*taskDetail->GetScheduledTaskAlias());
				taskItem->SetScheduledTaskDetailContext(taskDetail);

				TaskItemPool::GetInstance().QueueTaskItem(taskItem);
			}
		}
	}

	_lastScheduledTaskExecution = currentTicks;
}

void TaskScheduler::FreeScheduledTask(ScheduledTaskDetail * taskDetail)
{
	taskDetail->ClearTaskDetailData();
}

void TaskScheduler::FreeScheduledTask(const int index)
{
	if (index >= SCHEDULED_TASK_DETAIL_COUNT) { return; }
	FreeScheduledTask(_taskData->GetScheduledTaskDetailByIndex(index));
}