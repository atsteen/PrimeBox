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

#include "..\..\include\TaskExecutor\TaskExecutor.h"
#include "..\..\include\SharedStructure\TaskItemPool.h"

TaskExecutor::TaskExecutor(IRtcLogger * rtcLogger, ITaskHandlerFactory * handlerFactory)
{	
	_rtcLogger = rtcLogger;
	_taskHandlerList = handlerFactory->MakeHandlerList();
}

void TaskExecutor::ProcessTaskQueue(int taskCount)
{
	if (_taskHandlerList->empty()) { return; }

	int attemptedTasks = 0;
	while (attemptedTasks < taskCount || TaskItemPool::GetInstance().FreeTaskItemCount() <= BATCH_TASK_PROCESSING_LIMIT)
	{
		TaskItem *currentTask = TaskItemPool::GetInstance().DequeueTaskItem();
		if (!currentTask || currentTask->GetTaskAssociation() == TASKALIAS_NOT_SET) { break; }

		ScheduledTaskDetail * currentTaskScheduleDetail = currentTask->GetScheduledTaskDetailContext();

		if (currentTaskScheduleDetail && (currentTaskScheduleDetail->GetScheduledTaskExecutionTime()->secondsInDay() >  _rtcLogger->CurrentTime().secondsInDay()))
		{
			TaskItemPool::GetInstance().QueueTaskItem(currentTask);
		}
		else
		{
			//todo... remove!
			/*_rtcLogger->LogMessage("TaskExecutor is processing task...");*/

			const T_ListNode<ITaskHandler&> * handlerNode = _taskHandlerList->front();

			while (handlerNode)
			{
				if (handlerNode->element.HandleTask(currentTask)) { TaskItemPool::GetInstance().FreeTaskItem(currentTask); }
				if (handlerNode->next == nullptr) { _ProcessUnhandledTask(currentTask); }
				handlerNode = handlerNode->next;
			}
		}

		++attemptedTasks;
	}
}

void TaskExecutor::_ProcessUnhandledTask(TaskItem * unhandledTask)
{
	if (unhandledTask->IncrementFailedExecutionCount() >= MAX_TASK_RETRY_ATTEMPTS)
	{
		_rtcLogger->LogMessage(MESSAGE_TEXT_TASK_RETRY_FAILURE, unhandledTask->GetTaskAssociation());
		TaskItemPool::GetInstance().FreeTaskItem(unhandledTask);
	}
	else
	{
		TaskItemPool::GetInstance().QueueTaskItem(unhandledTask);
	}
}
