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
#include "..\..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\..\SharedStructure\SharedInterface\IViewstateMapGenerator.h"
#include "..\..\SharedStructure\T_DynamicDataProxy.h"

class PX4_InputViewstate_TimeSpanValue_TaskHandler : public ITaskHandler
{
public:
	PX4_InputViewstate_TimeSpanValue_TaskHandler(IModelViewstateData * viewstateData, IViewstateMapGenerator * mapGenerator)
		: _viewstateData(viewstateData), _mapGenerator(mapGenerator){};
	~PX4_InputViewstate_TimeSpanValue_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IViewstateMapGenerator * _mapGenerator;

	void _returnToPreviousViewstate();
};

inline bool PX4_InputViewstate_TimeSpanValue_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	ISelectableNavigationMap * map = _viewstateData->GetNavigationMap(); 
	const SelectableViewstateElementAlias currentlySelectedElement = map->CurrentSelection()->selectedElement;

	switch (_taskItem->GetTaskAssociation()) {
		case TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT :
			if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT) { this->_returnToPreviousViewstate(); }
			if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SAVE_ELEMENT)
			{			
				_viewstateData->GetDynamicDataProxy()->commit();
				this->_returnToPreviousViewstate();
			}
			if(currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SETTIME_HH_ELEMENT || currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SETTIME_MM_ELEMENT)
			{
				_viewstateData->SetDynamicViewstateModalState(!_viewstateData->GetDynamicViewstateModalState());
				_viewstateData->ForceModelUpdateNotify();
			}

			break;

		case TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT :
			if (_viewstateData->GetDynamicViewstateModalState())
			{
				if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SETTIME_HH_ELEMENT)
				{
					_viewstateData->GetDynamicDataProxy()->getDynamicTimeValue()->AdjustHH(-1);
					_viewstateData->ForceModelUpdateNotify();
				}
				
				if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SETTIME_MM_ELEMENT)
				{
					_viewstateData->GetDynamicDataProxy()->getDynamicTimeValue()->AdjustMM(-1);
					_viewstateData->ForceModelUpdateNotify();
				}
			}

			break;

		case TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT:
			if (_viewstateData->GetDynamicViewstateModalState())
			{
				if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SETTIME_HH_ELEMENT)
				{
					_viewstateData->GetDynamicDataProxy()->getDynamicTimeValue()->AdjustHH(1);
					_viewstateData->ForceModelUpdateNotify();
				}
				
				if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_SETTIME_MM_ELEMENT)
				{
					_viewstateData->GetDynamicDataProxy()->getDynamicTimeValue()->AdjustMM(1);
					_viewstateData->ForceModelUpdateNotify();
				}
			}

			break;
	};

	return true;
}

inline bool PX4_InputViewstate_TimeSpanValue_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{	
	// This handler only handles tasks for VIEWSTATEALIAS_INPUT_PROMPT_TIME
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_INPUT_PROMPT_TIME) { return false; }
	
	// This handler only handles TASKALIAS_NAVIGATION_MENU_MOVE_* or TASKALIAS_NAVIGATION_MENU_SELECT tasks
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT
		&& currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT
		&& currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT)
	{
		return false;
	}

	return true;
}

inline void PX4_InputViewstate_TimeSpanValue_TaskHandler::_returnToPreviousViewstate()
{
	ViewstateAlias returnViwestate = _viewstateData->GetDynamicDataProxy()->getReturnViewstate();
	SelectableViewstateElementAlias returnSelectedElement = _viewstateData->GetDynamicDataProxy()->getReturnSelectedElement();
	ISelectableNavigationMap * newMap = _mapGenerator->GenerateMap(returnViwestate);
	newMap->SetSelection(returnSelectedElement);
	_viewstateData->SetNavigationMap(newMap);
}

inline const bool PX4_InputViewstate_TimeSpanValue_TaskHandler::FlagStateChange()
{
	return true;
}