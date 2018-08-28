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

#include "..\..\include\SharedStructure\TaskItemPool.h"

TaskItemPool & TaskItemPool::GetInstance()
{
	static TaskItemPool taskItemPoolInstance;
	return taskItemPoolInstance;
}

TaskItem * TaskItemPool::GetNewTaskItem()
{
	if (FreeTaskItemCount() < 1)
	{ 
		return nullptr; 
	}
	
	TaskItem *ti = nullptr;

	for (int i = 0; i < TASK_ITEM_POOL_SIZE; i++)
	{
		if (_taskItems[i].GetTaskAssociation() == TASKALIAS_NOT_SET)
		{
			ti = &_taskItems[i];
			break;
		}
	}

	return ti;
}

void TaskItemPool::FreeTaskItem(TaskItem * ta)
{
	ta->Deallocate();
}

int TaskItemPool::FreeTaskItemCount()
{
	int i = 0;

	for (int j = 0; j < TASK_ITEM_POOL_SIZE; j++)
	{
		if (_taskItems[j].GetTaskAssociation() == TASKALIAS_NOT_SET) { ++i; }
	}

	return i;
}

bool TaskItemPool::QueueTaskItem(TaskItem * taskItem)
{
	bool retVal = _taskQueue.Enqueue(taskItem);

	return retVal;
}

TaskItem * TaskItemPool::DequeueTaskItem()
{ 
	TaskItem * retVal = _taskQueue.Dequeue();

	return retVal;
}

TaskItem * const * TaskItemPool::QueueTaskItemTop(TaskItem * taskItem)
{
	return _taskQueue.EnqueueTop(taskItem);
}

TaskItem * const * TaskItemPool::QueueTaskItemAfter(TaskItem * taskItem, TaskItem * const * afterItemPtr)
{
	return _taskQueue.EnqueueAfter(taskItem, afterItemPtr);
}
