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

#include "..\..\include\CommandInterpreter\CommandInterpreter_PX4.h"

void CommandInterpreter_PX4::InvokeTaskRequest(const TaskAlias ta) const
{
	TaskItem *taskItem = TaskItemPool::GetInstance().GetNewTaskItem();
	if (!taskItem)
	{
		_rtcLogger->LogMessage(EVENT_TEXT_TASKPOOL_FULL);
		return;
	}

	taskItem->SetTaskAlias(ta);

	if (ta == TASKALIAS_NAVIGATION_MENU_SELECT ||
		ta == TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT ||
		ta == TASKALIAS_NAVIGATION_MENU_MOVE_LEFT
		)
	{
		_interfaceData->RegisterUserInputAction(_rtcLogger->CurrentTime());

		//todo... remove if not needed
		//taskItem->SetViewstateContextRequirement();
	}

	//todo... remove!
	//_rtcLogger->LogMessage("CommandInterpreter is queueing a task...");

	TaskItemPool::GetInstance().QueueTaskItem(taskItem);
}

void CommandInterpreter_PX4::AddPolledInterface(IPolledInterfaceControl &polledInterface)
{
	_polledInterfaces.addBack(polledInterface);
}

const bool CommandInterpreter_PX4::InvokePolledInterfaceScan()
{
	const T_ListNode<IPolledInterfaceControl &> * node = _polledInterfaces.front();

	while (node)
	{
		TaskAlias flaggedTask = node->element.GetRequestedTask();
		if (flaggedTask != TASKALIAS_NOT_SET)
		{ 
			this->InvokeTaskRequest(TASKALIAS_ENABLE_DISPLAY); // interface tasks always activate ui
			this->InvokeTaskRequest(flaggedTask);
		}

		node = node->next;
	}
	
	return false;
}