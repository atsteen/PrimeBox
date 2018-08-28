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

#include "..\TaskHandler.h"


class PX4_PowerRelay_TaskHandler : public TaskHandler
{
public:
	PX4_PowerRelay_TaskHandler(TaskAlias ta, ViewstateAlias vs, SelectableViewstateElementAlias svea) : TaskHandler(ta, vs, svea){};
	~PX4_PowerRelay_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override = 0;
	virtual const bool FlagStateChange() override { return true; }

protected:

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;
};

inline bool PX4_PowerRelay_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if ((ti->GetTaskAssociation() == _HtaskAssociation) &&
		(ti->GetViewStateAssociation() == _HviewstateAssociation) &&
		(ti->GetSelectableViewstateElementAssociation() == _HviewstateAssociation)
	) { return true; }

	return false;
}