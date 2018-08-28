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

#include "..\..\include\SharedStructure\TaskItem.h"

void TaskItem::SetTaskAlias(const TaskAlias ta)
{
	_taskAssociation = ta;
}

void TaskItem::Deallocate()
{
	_taskAssociation = TASKALIAS_NOT_SET;
	//_viewstateAssociation = VIEWSTATEALIAS_NOT_SET;
	//_selectableElementAssociation = SELECTABLE_ELEMENT_NOT_SET;
	_failedExecutionCount = 0;
	_scheduledTaskContext = nullptr;
}

//const ViewstateAlias TaskItem::GetViewStateAssociation()
//{
//	return _viewstateAssociation;
//}
//
//const SelectableViewstateElementAlias TaskItem::GetSelectableViewstateElementAssociation()
//{
//	return _selectableElementAssociation;
//}
//
//void TaskItem::SetViewstateContext(ViewstateAlias viewstateAlias, SelectableViewstateElementAlias selectableElementAlias)
//{
//	_viewstateAssociation = viewstateAlias;
//	_selectableElementAssociation = selectableElementAlias;
//}
//
//const bool TaskItem::GetViewstateContextRequirement()
//{
//	return _viewstateContextRequirement;
//}
//
//void TaskItem::SetViewstateContextRequirement()
//{
//	_viewstateContextRequirement = true;
//}

void TaskItem::SetScheduledTaskDetailContext(ScheduledTaskDetail * scheduledTaskContext)
{
	_scheduledTaskContext = scheduledTaskContext;
}

ScheduledTaskDetail * TaskItem::GetScheduledTaskDetailContext()
{
	return _scheduledTaskContext;
}

const TaskAlias TaskItem::GetTaskAssociation()
{
	return _taskAssociation;
}

int TaskItem::IncrementFailedExecutionCount()
{
	return ++_failedExecutionCount;
}
