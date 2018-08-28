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
#include "SharedInterface\ITaskItem.h"
#include "SharedInterface\ITaskItem_Context_ViewState.h"
#include "SharedInterface\ITaskItem_Context_ScheduledTaskDetail.h"
#include "..\SharedStructure\ScheduledTaskDetail.h"

class TaskItem
	: public ITaskItem, public ITaskItem_Context_ScheduledTaskDetail //, public ITaskItem_Context_ViewState
{
public:
	TaskItem() {}
	virtual ~TaskItem() {}

	// Inherited via ITaskItem
	virtual void SetTaskAlias(const TaskAlias) override;
	virtual void Deallocate() override;
	virtual const TaskAlias GetTaskAssociation() override;
	int IncrementFailedExecutionCount();

	// TODO... clean up unused methods like setcontext
	// Inherited via ITaskItem_Context_ViewState
	//virtual const ViewstateAlias GetViewStateAssociation() override;
	//virtual const SelectableViewstateElementAlias GetSelectableViewstateElementAssociation() override;
	//virtual void SetViewstateContext(ViewstateAlias, SelectableViewstateElementAlias) override;
	//virtual const bool GetViewstateContextRequirement() override;
	//virtual void SetViewstateContextRequirement() override;

	// Inherited via ITaskItem_Context_ScheduledTaskDetail
	virtual void SetScheduledTaskDetailContext(ScheduledTaskDetail *) override;
	virtual ScheduledTaskDetail * GetScheduledTaskDetailContext() override;

protected:
	TaskAlias _taskAssociation = TASKALIAS_NOT_SET;
	//ViewstateAlias _viewstateAssociation = VIEWSTATEALIAS_NOT_SET;
	//SelectableViewstateElementAlias _selectableElementAssociation = SELECTABLE_ELEMENT_NOT_SET;
	int _failedExecutionCount = 0;
	bool _viewstateContextRequirement = false;
	ScheduledTaskDetail * _scheduledTaskContext = nullptr;
};