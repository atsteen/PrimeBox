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
#include "TaskItem.h"
#include "T_queue.h"
#include "..\..\..\Configurations\PX4_Config.h"

#if defined(TARGET_PLAT_AVR) && defined(ENABLE_VERBOSE_LOGGING)
#include <Arduino.h>
#endif

class TaskItemPool
{
public:
	static TaskItemPool& GetInstance();
	~TaskItemPool() {};

	TaskItem * GetNewTaskItem();
	void FreeTaskItem(TaskItem *);
	int FreeTaskItemCount();
	bool QueueTaskItem(TaskItem *);
	TaskItem * const * QueueTaskItemTop(TaskItem *);
	TaskItem * const * QueueTaskItemAfter(TaskItem *, TaskItem * const *);
	TaskItem * DequeueTaskItem();

private:
	TaskItemPool(){};
	TaskItem _taskItems[TASK_ITEM_POOL_SIZE];
	T_queue<TaskItem *> _taskQueue;
};