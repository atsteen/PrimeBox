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

#include "..\..\SharedStructure\SharedInterface\ITaskHandler.h"
#include "..\..\SharedStructure\SharedInterface\ITextDisplay.h"

class PX4_StateRefresh_Display : public ITaskHandler
{
public:
	PX4_StateRefresh_Display(ITextDisplay * textDisplay) : _textDisplay(textDisplay){};

	~PX4_StateRefresh_Display() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	ITextDisplay * _textDisplay;
};

inline bool PX4_StateRefresh_Display::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	if (_taskItem->GetTaskAssociation() == TaskAlias::TASKALIAS_DISABLE_DISPLAY) { _textDisplay->DisableBacklight(); }
	else { _textDisplay->EnableBacklight(); }

	return true;
}

inline bool PX4_StateRefresh_Display::_CanHandleTask(TaskItem * _taskItem)
{
	if (_taskItem->GetTaskAssociation() == TaskAlias::TASKALIAS_DISABLE_DISPLAY) { return true; }
	if (_taskItem->GetTaskAssociation() == TaskAlias::TASKALIAS_ENABLE_DISPLAY) { return true; }
	return false;
}

inline const bool PX4_StateRefresh_Display::FlagStateChange()
{
	return true;
}