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
#include "..\..\SharedStructure\SharedInterface\IPowerRelayArray.h"

class PX4_ManualOverrideViewstate_TaskHandler : public ITaskHandler
{
public:
	PX4_ManualOverrideViewstate_TaskHandler(IModelViewstateData * viewstateData, IPowerRelayArray * relayArray)
		: _viewstateData(viewstateData), _relayArray(relayArray){};
	~PX4_ManualOverrideViewstate_TaskHandler() {};

	static bool HandleIt() {};

	// Inherited via ITaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override;

protected:
	virtual bool _CanHandleTask(TaskItem *) override;

private:
	IModelViewstateData * _viewstateData;
	IPowerRelayArray * _relayArray;
};

inline bool PX4_ManualOverrideViewstate_TaskHandler::HandleTask(TaskItem * _taskItem)
{
	if (!_CanHandleTask(_taskItem)) { return false; }

	const int currentSelectedIndex = _viewstateData->GetViewstateSelectableElementIndex();
	const SelectableViewstateElementAlias currentlySelectedElement = _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement;
	const int relayCount = _relayArray->CircuitCount();
	int nextSelectedListIndex = currentSelectedIndex;
	SelectableViewstateElementAlias nextSelectedElement = SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET;

	switch (_taskItem->GetTaskAssociation()) {
		case TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT:
			if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT && currentSelectedIndex == 0)
			{
				nextSelectedElement = SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC;
				nextSelectedListIndex = 0;
			}
			else if (currentSelectedIndex < relayCount - 1) { ++nextSelectedListIndex; }	
			
			break;

		case TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT:
			if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC && currentSelectedIndex == 0)
			{
				nextSelectedElement = SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT;
			}
			else if(currentlySelectedElement != SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT && currentSelectedIndex > 0)
			{
				--nextSelectedListIndex;
			}

			break;

		case TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT:
			if (currentlySelectedElement == SelectableViewstateElementAlias::SELECTABLE_ELEMENT_DYNAMIC)
			{
				switch (_relayArray->GetRelayPowerStateByIndex(currentSelectedIndex)) {
					case ComponentPowerState::DISABLED :
						_relayArray->InstateOverrideByIndex(currentSelectedIndex);
						break;

					case ComponentPowerState::OVERRIDE_DISABLED:
						_relayArray->ReleaseOverrideByIndex(currentSelectedIndex);
						_relayArray->EnableByIndex(currentSelectedIndex);
						_relayArray->InstateOverrideByIndex(currentSelectedIndex);
						break;

					case ComponentPowerState::OVERRIDE_ENABLED:
						_relayArray->ReleaseOverrideByIndex(currentSelectedIndex);
						_relayArray->EnableByIndex(currentSelectedIndex);
						break;

					default:
						_relayArray->DisableByIndex(currentSelectedIndex);
						break;
				}
			}
			break;
	}

	ISelectableNavigationMap * const map = _viewstateData->GetNavigationMap();
	if (nextSelectedElement != SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET) { map->SetSelection(nextSelectedElement); }
	_viewstateData->SetViewstateSelectableElementIndex(nextSelectedListIndex);
	_viewstateData->SetNavigationMap(map); //SetNavigationMap call required to trigger viewstate refresh callback

	return true;
}

inline bool PX4_ManualOverrideViewstate_TaskHandler::_CanHandleTask(TaskItem * _taskItem)
{
	if (_viewstateData->GetNavigationMap()->ViewstateAssociation() != ViewstateAlias::VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW) { return false; }

	// This handler only handles menu select or menu navigation tasks
	const TaskAlias currentTaskAssociation = _taskItem->GetTaskAssociation();
	if (currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_SELECT &&
		currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT &&
		currentTaskAssociation != TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)
	{
		return false;
	}

	return true;
}

inline const bool PX4_ManualOverrideViewstate_TaskHandler::FlagStateChange()
{
	return true;
}