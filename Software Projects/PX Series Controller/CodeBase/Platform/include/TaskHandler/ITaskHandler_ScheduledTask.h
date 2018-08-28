#pragma once

#include "..\TaskItem\TaskItem.h"

class ITaskHandler_ScheduledTask
{
public:
	ITaskHandler_ScheduledTask() {}
	virtual ~ITaskHandler_ScheduledTask() = 0;
};

inline ITaskHandler_ScheduledTask::~ITaskHandler_ScheduledTask() {}
