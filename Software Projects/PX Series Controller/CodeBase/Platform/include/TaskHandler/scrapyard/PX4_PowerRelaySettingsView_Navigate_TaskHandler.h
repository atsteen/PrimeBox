#pragma once

#include "..\TaskHandler.h"
#include "..\..\DataModel\DataModel_PX4.h"

#define SELECTABLE_ELEMENT_COUNT 4
class PX4_PowerRelaySettingsView_Navigate_TaskHandler
	: public TaskHandler
{
public:
	PX4_PowerRelaySettingsView_Navigate_TaskHandler()
		: TaskHandler(
			TaskAlias::TASKALIAS_NOT_SET, //Leave TASKALIAS_NOT_SET to handle both navLeft and navRight
			ViewstateAlias::VIEWSTATEALIAS_POWER_RELAY_SETTINGS_VIEW,
			SelectableViewstateElementAlias::SELECTABLE_ELEMENT_NOT_SET //Leave SELECTABLE_ELEMENT_NOT_SET to handle all viewstate selections
		) {};

	~PX4_PowerRelaySettingsView_Navigate_TaskHandler() {};

	// Inherited via TaskHandler
	virtual bool HandleTask(TaskItem *) override;
	virtual const bool FlagStateChange() override { return true; }

protected:
	SelectableViewstateElementAlias _selectableOrder[SELECTABLE_ELEMENT_COUNT]{
		SelectableViewstateElementAlias::SELECTABLE_BACK_ELEMENT,
		SelectableViewstateElementAlias::SELECTABLE_PUMP_PWR_SETTING_ELEMENT,
		SelectableViewstateElementAlias::SELECTABLE_FANS_PWR_SETTING_ELEMENT,
		SelectableViewstateElementAlias::SELECTABLE_LIGHTS_PWR_SETTING_ELEMENT
	};

	bool Handle_NavLeft(SelectableViewstateElementAlias currentlySelected);
	bool Handle_NavRight(SelectableViewstateElementAlias currentlySelected);

	// Inherited via TaskHandler
	virtual bool _CanHandleTask(TaskItem *) override;
};

inline bool PX4_PowerRelaySettingsView_Navigate_TaskHandler::HandleTask(TaskItem * ti)
{
	if (_CanHandleTask(ti))
	{
		if (ti->GetTaskAssociation() == TASKALIAS_NAVIGATION_MENU_MOVE_LEFT)
		{
			return Handle_NavLeft(DataModel_PX4::GetInstance().GetSelectedViewstateElement());
		}
		else { return Handle_NavRight(DataModel_PX4::GetInstance().GetSelectedViewstateElement()); }
	}

	return false;
}

inline bool PX4_PowerRelaySettingsView_Navigate_TaskHandler::_CanHandleTask(TaskItem * ti)
{
	if (((ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_LEFT) |
		(ti->GetTaskAssociation() == TaskAlias::TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT)) && 
		(ti->GetViewStateAssociation() == _HviewstateAssociation))
	{ 
		return true; 
	}

	return false;
}

inline bool PX4_PowerRelaySettingsView_Navigate_TaskHandler::Handle_NavLeft(SelectableViewstateElementAlias currentlySelected)
{
	if (_selectableOrder[0] == currentlySelected)
	{
		DataModel_PX4::GetInstance().SetSelectedViewstateElement(_selectableOrder[SELECTABLE_ELEMENT_COUNT - 1]);
		this->GetBuzzer()->playNavTone();
		return true;
	}

	for (int i = 1; i < SELECTABLE_ELEMENT_COUNT; i++)
	{
		if (_selectableOrder[i] == currentlySelected)
		{
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(_selectableOrder[i - 1]);
			this->GetBuzzer()->playNavTone();
			return true;
		}
	}

	return false;
}

inline bool PX4_PowerRelaySettingsView_Navigate_TaskHandler::Handle_NavRight(SelectableViewstateElementAlias currentlySelected)
{
	if (_selectableOrder[SELECTABLE_ELEMENT_COUNT - 1] == currentlySelected)
	{
		DataModel_PX4::GetInstance().SetSelectedViewstateElement(_selectableOrder[0]);
		this->GetBuzzer()->playNavTone();
		return true;
	}

	for (int i = 0; i < SELECTABLE_ELEMENT_COUNT; i++)
	{
		if (_selectableOrder[i] == currentlySelected)
		{
			DataModel_PX4::GetInstance().SetSelectedViewstateElement(_selectableOrder[i + 1]);
			this->GetBuzzer()->playNavTone();
			return true;
		}
	}

	return false;
}