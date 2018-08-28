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

#include "..\SharedStructure\SharedInterface\ITaskHandler.h"

class TaskHandler : public ITaskHandler
{
public:
	TaskHandler(TaskAlias ta, ViewstateAlias vs, SelectableViewstateElementAlias svea)
		: _HtaskAssociation(ta), _HviewstateAssociation(vs), _HselectableElementAssociation(svea) {};

	virtual ~TaskHandler() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override { return false; }
	virtual const bool FlagStateChange() override { return false; }

protected:
	TaskAlias _HtaskAssociation = TaskAlias::TASKALIAS_NOT_SET;
	ViewstateAlias _HviewstateAssociation = VIEWSTATEALIAS_NOT_SET;
	SelectableViewstateElementAlias _HselectableElementAssociation = SELECTABLE_ELEMENT_NOT_SET;

	// Inherited via ITaskHandler
	virtual bool _CanHandleTask(TaskItem *) override { return false; }
};
