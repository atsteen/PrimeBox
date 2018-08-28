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
#include "..\TimeSignature.h"
#include "..\TaskAlias.h"
#include "..\ComponentAssociation.h"
#include "..\ScheduledTaskDetail.h"

class IModelTaskData
{
public:
	IModelTaskData() {};
	virtual ~IModelTaskData();

	//interface for new task creation
	virtual const int * const GetCreateSchdTaskTargetIndex() = 0;
	virtual void SetCreateSchdTaskTargetIndex(const int * const) = 0;
	virtual const ComponentAssociation * const GetCreateSchdTaskTarget() = 0;
	virtual void SetCreateSchdTaskTarget(const ComponentAssociation * const) = 0;
	virtual const bool * const GetCreateSchdTaskAction() = 0;
	virtual void SetCreateSchdTaskAction(const bool * const) = 0;
	virtual const TimeSignature * const GetCreateSchdTaskTime() = 0;
	virtual void SetCreateSchdTaskTime(const TimeSignature * const) = 0;
	virtual void ClearCreateSchdTaskValues() = 0;

	//todo... the following is a sub-optimal approach to implementing taskDetail collection edits with generic viewstates
	//the issue is the datamodel must manage member updates that update persistent memory, even for collections (poor design)
	//Ideally this interface addition should be migrated to a standalone data type with its own persistent data management
	virtual const int AddScheduledTaskDetail(const TaskDetailData * const) = 0;
	virtual void FreeScheduledTaskDetailByIndex(uint8_t index) = 0;
	virtual void SetEditableTaskDetailIndex(const int) = 0;

	virtual const TimeSignature * const GetEditableTaskDetailExecutionTime() = 0;
	virtual void SetEditableTaskDetailExecutionTime(const TimeSignature * const) = 0;
	virtual const bool * const GetEditableTaskDetailEnabledState() = 0;
	virtual void SetEditableTaskDetailEnabledState(const bool * const) = 0;
	
	virtual ScheduledTaskDetail * const GetScheduledTaskDetailByIndex(uint8_t) = 0;
	virtual const int GetFreeScheduledTaskDetailCount() = 0;
};

inline IModelTaskData::~IModelTaskData() {}