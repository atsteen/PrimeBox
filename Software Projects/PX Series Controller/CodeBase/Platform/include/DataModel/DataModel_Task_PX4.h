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
#include "..\SharedStructure\SharedInterface\IModelTaskData.h"
#include "..\SharedStructure\SharedInterface\Ipersistent.h"
#include "..\SharedStructure\Subject.h"
#include "..\SharedStructure\ScheduledTaskDetail.h"

class DataModel_Task_PX4 :
	public IModelTaskData,
	public Ipersistent,
	public Subject
{
public:
	DataModel_Task_PX4(const PersistentComponentAlias, IPersistentDataCoordinator *);
	~DataModel_Task_PX4() {};

	virtual const int * const GetCreateSchdTaskTargetIndex() override;
	virtual void SetCreateSchdTaskTargetIndex(const int * const) override;
	virtual const ComponentAssociation * const GetCreateSchdTaskTarget() override;
	virtual void SetCreateSchdTaskTarget(const ComponentAssociation * const taskType) override;
	virtual const bool * const GetCreateSchdTaskAction() override;
	virtual void SetCreateSchdTaskAction(const bool * const) override;
	virtual const TimeSignature * const GetCreateSchdTaskTime() override;
	virtual void SetCreateSchdTaskTime(const TimeSignature * const) override;
	virtual void ClearCreateSchdTaskValues() override;

	// Inherited via IModelTaskData
	//todo... see comment in interface about sub-optimal taskdetail interface design
	const int AddScheduledTaskDetail(const TaskDetailData * const) override;
	virtual void FreeScheduledTaskDetailByIndex(uint8_t index) override;
	virtual void SetEditableTaskDetailIndex(const int) override;

	virtual const TimeSignature * const GetEditableTaskDetailExecutionTime() override;
	virtual void SetEditableTaskDetailExecutionTime(const TimeSignature * const) override;
	virtual const bool * const GetEditableTaskDetailEnabledState() override;
	virtual void SetEditableTaskDetailEnabledState(const bool * const) override;

	ScheduledTaskDetail * const GetScheduledTaskDetailByIndex(uint8_t) override;
	virtual const int GetFreeScheduledTaskDetailCount() override;	

	// Inherited via Ipersistent
	virtual void RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;
	virtual void UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;
	virtual const PersistentComponentAlias GetComponentAlias() override;

private:	
	int _editableTaskDetailIndex = 0;
	ScheduledTaskDetail _scheduledTaskDetails[SCHEDULED_TASK_DETAIL_COUNT];
	int _createSchdTaskTargetIndex = -1;
	ComponentAssociation _createSchdTaskTargetType;
	bool _creatSchdTaskAction = false;
	TimeSignature _createSchdTaskTime = { 0,0,0 };
};