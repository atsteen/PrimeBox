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

#include "PX4_PowerRelay_TaskHandler.h"
#include "..\..\ComponentModuleGroup\ComponentModuleGroup_PX4.h"
#include "..\..\SharedStructure\Logger.h"

class PX4_PowerRelay_EnableFan_TaskHandler
	: public PX4_PowerRelay_TaskHandler, public Logger
{
public:
	PX4_PowerRelay_EnableFan_TaskHandler()
		: PX4_PowerRelay_TaskHandler(
			TaskAlias::TASKALIAS_ENABLE_POWER_RELAY_FAN,
			ViewstateAlias::VIEWSTATEALIAS_NOT_SET,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET
		), Logger(LoggerObj::OBJ_TASKHANDLER_POWER_RELAY_CHANNEL_B) {};

	~PX4_PowerRelay_EnableFan_TaskHandler() {};

	// Inherited via PX4_PowerRelay_TaskHandler
	virtual bool HandleTask(TaskItem *) override;

protected:

	// Inherited via PX4_PowerRelay_TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;
};

inline bool PX4_PowerRelay_EnableFan_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		#if defined(ENABLE_VERBOSE_LOGGING)
			this->PushCallStack();
			this->MarkObjID();
		#endif

		ComponentModuleGroup_PX4 _moduleGroup;
		_moduleGroup.FanRelay()->Enable();

		#if defined(ENABLE_VERBOSE_LOGGING)			
			char callStackStr[T_STACK_MAX_SIZE * 3];
			this->ComposeCallStack(callStackStr);
			this->DataLogger()->LogMessageVerbose(callStackStr, Viewstate_String_Generator::GetViewstateString(EVENT_TEXT_POWERRELAY_FAN_ON));
		#endif
		
		this->DataLogger()->LogSystemEventImmediate(EVENT_TEXT_POWERRELAY_FAN_ON);
		
		#if defined(ENABLE_VERBOSE_LOGGING)
			this->PopCallStack();
		#endif

		return true;
	}

	return false;
}

inline bool PX4_PowerRelay_EnableFan_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (ti->GetTaskAssociation() == _HtaskAssociation) { return true; }

	return false;
}