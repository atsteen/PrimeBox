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

#if defined(TARGET_PLAT_AVR)

#include <arduino.h>
#include <EEPROMex.h>

//non-vol state fields
extern const byte address_pumpPWRState;

#endif

class PX4_PowerRelay_DisablePump_TaskHandler
	: public PX4_PowerRelay_TaskHandler, public Logger
{
public:
	PX4_PowerRelay_DisablePump_TaskHandler()
		: PX4_PowerRelay_TaskHandler(
			TaskAlias::TASKALIAS_DISABLE_POWER_RELAY_PUMP,
			ViewstateAlias::VIEWSTATEALIAS_NOT_SET,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET
		), Logger(LoggerObj::OBJ_TASKHANDLER_POWER_RELAY_CHANNEL_A) {};

	~PX4_PowerRelay_DisablePump_TaskHandler() {};

	// Inherited via PX4_PowerRelay_TaskHandler
	virtual bool HandleTask(TaskItem *) override;

protected:

	// Inherited via PX4_PowerRelay_TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override; //override to handle task from any context (defult requires full context match)
};

inline bool PX4_PowerRelay_DisablePump_TaskHandler::HandleTask(TaskItem * ti)
{
	#if defined(ENABLE_VERBOSE_LOGGING)
		this->PushCallStack();
	#endif

	if (_CanHandleTask(ti))
	{
		ComponentModuleGroup_PX4 _moduleGroup;
		_moduleGroup.PumpRelay()->Disable();

		#if defined(ENABLE_VERBOSE_LOGGING)
			char callStackStr[T_STACK_MAX_SIZE * 3];
			this->ComposeCallStack(callStackStr);
			this->DataLogger()->LogMessageVerbose(callStackStr, Viewstate_String_Generator::GetViewstateString(EVENT_TEXT_POWERRELAY_PUMP_OFF));
		#endif

		this->DataLogger()->LogSystemEventImmediate(EVENT_TEXT_POWERRELAY_PUMP_OFF);

		#if defined(ENABLE_VERBOSE_LOGGING)
			this->PopCallStack();
		#endif

		return true;
	}

	#if defined(ENABLE_VERBOSE_LOGGING)
		this->PopCallStack();
	#endif

	return false;
}

inline bool PX4_PowerRelay_DisablePump_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (ti->GetTaskAssociation() == _HtaskAssociation) { return true; }

	return false;
}