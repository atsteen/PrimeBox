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
#include "..\SharedStructure\SharedInterface\ICommandInterpreter.h"
#include "..\SharedStructure\SharedInterface\IModelInterfaceData.h"
#include "..\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\SharedStructure\TaskAlias.h"
#include "..\SharedStructure\ViewstateAlias.h"
#include "..\SharedStructure\SelectableViewstateElementAlias.h"
#include "..\SharedStructure\TaskItemPool.h"
#include "..\SharedStructure\T_List.h"

class CommandInterpreter_PX4 : public ICommandInterpreter
{
public:
	CommandInterpreter_PX4(IModelInterfaceData * interfaceData, IRtcLogger * rtcLogger) : _interfaceData(interfaceData), _rtcLogger(rtcLogger){}
	~CommandInterpreter_PX4() {}

	// Inherited via ICommandInterpreter
	virtual void InvokeTaskRequest(const TaskAlias ta) const override;
	virtual const bool InvokePolledInterfaceScan() override;
	virtual void AddPolledInterface(IPolledInterfaceControl & polledInterface) override;
	

private:
	IModelInterfaceData * _interfaceData;
	IRtcLogger * _rtcLogger;
	T_List<IPolledInterfaceControl &> _polledInterfaces;
};