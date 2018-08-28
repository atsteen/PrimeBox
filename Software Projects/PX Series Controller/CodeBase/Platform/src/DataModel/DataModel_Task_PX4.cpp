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

#include "..\..\include\DataModel\DataModel_Task_PX4.h"

DataModel_Task_PX4::DataModel_Task_PX4(const PersistentComponentAlias ca, IPersistentDataCoordinator * pdc) : Ipersistent(ca, pdc)
{
	this->RestorePersistentData(_persistentDataCoordinator);
}

const int * const DataModel_Task_PX4::GetCreateSchdTaskTargetIndex()
{
	return &_createSchdTaskTargetIndex;
}

void DataModel_Task_PX4::SetCreateSchdTaskTargetIndex(const int * const index)
{
	_createSchdTaskTargetIndex = *index;
}

const ComponentAssociation * const DataModel_Task_PX4::GetCreateSchdTaskTarget()
{
	return &_createSchdTaskTargetType;
}

void DataModel_Task_PX4::SetCreateSchdTaskTarget(const ComponentAssociation * const taskType)
{
	_createSchdTaskTargetType.groupAssociation = taskType->groupAssociation;
	_createSchdTaskTargetType.typeAssociation = taskType->typeAssociation;
	this->notifyObservers();
}

const bool * const DataModel_Task_PX4::GetCreateSchdTaskAction()
{
	return &_creatSchdTaskAction;
}

void DataModel_Task_PX4::SetCreateSchdTaskAction(const bool * const action)
{
	_creatSchdTaskAction = *action;
}

const TimeSignature * const DataModel_Task_PX4::GetCreateSchdTaskTime()
{
	return &_createSchdTaskTime;
}

void DataModel_Task_PX4::SetCreateSchdTaskTime(const TimeSignature * const newTime)
{
	_createSchdTaskTime.SetSignature(newTime->year(), newTime->month(), newTime->day(), newTime->hour(), newTime->minute(), newTime->second());
	this->notifyObservers();
}

void DataModel_Task_PX4::ClearCreateSchdTaskValues()
{
	this->_createSchdTaskTargetIndex = -1;
	this->_createSchdTaskTargetType.typeAssociation = ComponentTypeAssociation::TYPE_NOT_SET;
	this->_createSchdTaskTargetType.groupAssociation = ComponentGroupAssociation::GROUP_A;
	this->_creatSchdTaskAction = false;
	this->_createSchdTaskTime.SetSignature(0, 0, 0, 0, 0, 0);
}

const int DataModel_Task_PX4::GetFreeScheduledTaskDetailCount()
{
	int i = 0;

	for (int j = 0; j < SCHEDULED_TASK_DETAIL_COUNT; j++)
	{
		if (*_scheduledTaskDetails[j].GetScheduledTaskAlias() == TASKALIAS_NOT_SET) { ++i; }
	}

	return i;
}

const PersistentComponentAlias DataModel_Task_PX4::GetComponentAlias()
{
	return this->_componentAlias;
}

const int DataModel_Task_PX4::AddScheduledTaskDetail(const TaskDetailData * const newTaskDetail)
{
	if (this->GetFreeScheduledTaskDetailCount() < 1)
	{
		//todo.. report taskDetail collection full		
	}

	for (uint8_t i = 0; i < SCHEDULED_TASK_DETAIL_COUNT; i++)
	{
		if (*_scheduledTaskDetails[i].GetScheduledTaskAlias() == TASKALIAS_NOT_SET)
		{
			_scheduledTaskDetails[i].SetTaskDetailData(newTaskDetail);
			this->UpdatePersistentData(_persistentDataCoordinator);
			return i;
		}
	}

	return -1;
}

void DataModel_Task_PX4::FreeScheduledTaskDetailByIndex(uint8_t index)
{
	while (index < SCHEDULED_TASK_DETAIL_COUNT - 1 && *_scheduledTaskDetails[index + 1].GetScheduledTaskAlias() != TASKALIAS_NOT_SET)
	{
		_scheduledTaskDetails[index].SetTaskDetailData(_scheduledTaskDetails[index + 1].GetTaskDetailData());
		++index;
	}

	TimeSignature ts(0, 0, 0);
	_scheduledTaskDetails[index].ClearTaskDetailData();
	this->UpdatePersistentData(_persistentDataCoordinator);
}

void DataModel_Task_PX4::SetEditableTaskDetailIndex(const int index)
{
	_editableTaskDetailIndex = index;
}

const TimeSignature * const DataModel_Task_PX4::GetEditableTaskDetailExecutionTime()
{
	return _scheduledTaskDetails[_editableTaskDetailIndex].GetScheduledTaskExecutionTime();
}

void DataModel_Task_PX4::SetEditableTaskDetailExecutionTime(const TimeSignature * const newTime)
{
	_scheduledTaskDetails[_editableTaskDetailIndex].SetScheduledTaskExecutionTime(newTime);
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const bool * const DataModel_Task_PX4::GetEditableTaskDetailEnabledState()
{
	return _scheduledTaskDetails[_editableTaskDetailIndex].GetScheduledTaskEnabledState();
}

void DataModel_Task_PX4::SetEditableTaskDetailEnabledState(const bool * const newState)
{
	_scheduledTaskDetails[_editableTaskDetailIndex].SetScheduledTaskEnabledState(newState);
	this->UpdatePersistentData(_persistentDataCoordinator);
}

ScheduledTaskDetail * const DataModel_Task_PX4::GetScheduledTaskDetailByIndex(uint8_t index)
{
	if (index >= SCHEDULED_TASK_DETAIL_COUNT) { return nullptr; }
	else { return &_scheduledTaskDetails[index]; }
}

void DataModel_Task_PX4::RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent)
{
	persistentDataAgent->ReadPersistentItem(_scheduledTaskDetails, PersistentDataAlias::SCHEDULED_TASK_POOL);
}

void DataModel_Task_PX4::UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent)
{
	persistentDataAgent->WritePersistentItem(_scheduledTaskDetails, PersistentDataAlias::SCHEDULED_TASK_POOL);
}


