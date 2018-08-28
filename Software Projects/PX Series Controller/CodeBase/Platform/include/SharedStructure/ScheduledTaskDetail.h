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
#include "TimeSignature.h"
#include "TaskAlias.h"
#include "ComponentAssociation.h"

struct TaskDetailData
{
	TaskAlias scheduledTaskAlias = TASKALIAS_NOT_SET;
	bool isEnabaled = true;
	ComponentAssociation relayAssociation;
	int relayIndex = -1;
	TimeSignature scheduledExecutionTime{ 0,0,0 };
};

class ScheduledTaskDetail
{
public:
	const TaskAlias * const GetScheduledTaskAlias() { return &_detailData.scheduledTaskAlias; }
	void SetScheduledTaskAlias(const TaskAlias * const newAlias) { _detailData.scheduledTaskAlias = *newAlias; }

	const bool * const GetScheduledTaskEnabledState() { return &_detailData.isEnabaled; }
	void SetScheduledTaskEnabledState(const bool * const newState) { _detailData.isEnabaled = *newState; }

	const ComponentAssociation * const GetScheduledTaskrelayAssociation() { return &_detailData.relayAssociation; }
	void SetScheduledTaskrelayAssociation(const ComponentAssociation * const);

	const int * const GetScheduledTaskrelayIndex() { return &_detailData.relayIndex; }
	void SetScheduledTaskrelayIndex(const int * const newIndex) { _detailData.relayIndex = *newIndex; }

	const TimeSignature * const GetScheduledTaskExecutionTime() { return &_detailData.scheduledExecutionTime; }
	void SetScheduledTaskExecutionTime(const TimeSignature * const newTime) { _detailData.scheduledExecutionTime.SetSignature(newTime); }

	const TaskDetailData * const GetTaskDetailData() { return &_detailData; }
	void SetTaskDetailData(const TaskDetailData * const);

	void ClearTaskDetailData();

private:
	TaskDetailData _detailData;
};

inline void ScheduledTaskDetail::SetScheduledTaskrelayAssociation(const ComponentAssociation * const newAssociation)
{
	_detailData.relayAssociation.typeAssociation = newAssociation->typeAssociation;
	_detailData.relayAssociation.groupAssociation = newAssociation->groupAssociation;
}

inline void ScheduledTaskDetail::SetTaskDetailData(const TaskDetailData * const taksDetail)
{
	_detailData.scheduledTaskAlias = taksDetail->scheduledTaskAlias;
	_detailData.isEnabaled = taksDetail->isEnabaled;
	_detailData.relayAssociation.typeAssociation = taksDetail->relayAssociation.typeAssociation;
	_detailData.relayAssociation.groupAssociation = taksDetail->relayAssociation.groupAssociation;
	_detailData.relayIndex = taksDetail->relayIndex;
	_detailData.scheduledExecutionTime.SetSignature(&taksDetail->scheduledExecutionTime);
}

inline void ScheduledTaskDetail::ClearTaskDetailData()
{
	TimeSignature ts{ 0,0,0 };
	_detailData.scheduledTaskAlias = TaskAlias::TASKALIAS_NOT_SET;
	_detailData.isEnabaled = false;
	_detailData.relayAssociation.typeAssociation = ComponentTypeAssociation::TYPE_NOT_SET;
	_detailData.relayAssociation.groupAssociation = ComponentGroupAssociation::GROUP_A;
	_detailData.relayIndex = -1;
	_detailData.scheduledExecutionTime.SetSignature(&ts);
}