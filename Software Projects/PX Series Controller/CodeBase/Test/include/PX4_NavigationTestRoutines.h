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

#include "..\SharedStructure\TaskAlias.h"
#include "..\CommandInterpreter\CommandInterpreter.h"
#include "..\TaskExecutor\TaskExecutor.h"
#include "..\TaskScheduler\TaskScheduler.h"
#include "..\ComponentModuleGroup\ComponentModuleGroup_PX4.h"

class NavigationRoutine
{
public:
	NavigationRoutine(const CommandInterpreter *ci, TaskExecutor *ta, TaskScheduler *ts) : _ci(ci), _ta(ta), _ts(ts) {}

	void RunManualOverrideDirectNavSweep()
	{
		ExecuteSteps(DirectOverrideViewNavR, sizeof(DirectOverrideViewNavR) / sizeof(DirectOverrideViewNavR[0]));
		ExecuteSteps(DirectOverrideViewNavL, sizeof(DirectOverrideViewNavL) / sizeof(DirectOverrideViewNavL[0]));
	}

	void RunManualOverrideViewNavSweep()
	{
		ExecuteSteps(ManualOverrideViewNavR, sizeof(ManualOverrideViewNavR) / sizeof(ManualOverrideViewNavR[0]));
		ExecuteSteps(ManualOverrideViewNavL, sizeof(ManualOverrideViewNavL) / sizeof(ManualOverrideViewNavL[0]));
	}

	void RunSchedTaskViewNavSweep()
	{
		ExecuteSteps(SchedTaskViewNavR, sizeof(SchedTaskViewNavR) / sizeof(SchedTaskViewNavR[0]));
		ExecuteSteps(SchedTaskViewNavL, sizeof(SchedTaskViewNavL) / sizeof(SchedTaskViewNavL[0]));
	}

	void RunEnvSettingsViewNavSweep()
	{
		ExecuteSteps(EnvSettingsViewNavR, sizeof(EnvSettingsViewNavR) / sizeof(EnvSettingsViewNavR[0]));
		ExecuteSteps(EnvSettingsViewNavL, sizeof(EnvSettingsViewNavL) / sizeof(EnvSettingsViewNavL[0]));
	}

	//void RunLightCycleEditNavSweep()
	//{
	//	ExecuteSteps(EnvSettings_LightCycleViewEditR, sizeof(EnvSettings_LightCycleViewEditR) / sizeof(EnvSettings_LightCycleViewEditR[0]));
	//	ExecuteSteps(EnvSettings_LightCycleViewEditL, sizeof(EnvSettings_LightCycleViewEditL) / sizeof(EnvSettings_LightCycleViewEditL[0]));
	//}

	//void RunFanCycleEditNavSweep()
	//{
	//	ExecuteSteps(RunFanCycleEditNavR, sizeof(RunFanCycleEditNavR) / sizeof(RunFanCycleEditNavR[0]));
	//	ExecuteSteps(RunFanCycleEditNavL, sizeof(RunFanCycleEditNavL) / sizeof(RunFanCycleEditNavL[0]));
	//}

	//void RunAlarmsEditNavSweep()
	//{
	//	ExecuteSteps(RunAlarmsEditNavR, sizeof(RunAlarmsEditNavR) / sizeof(RunAlarmsEditNavR[0]));
	//	ExecuteSteps(RunAlarmsEditNavL, sizeof(RunAlarmsEditNavL) / sizeof(RunAlarmsEditNavL[0]));
	//}

	//void RunNewTaskEditNavSweep()
	//{
	//	ExecuteSteps(NewTaskEditNavSweep, sizeof(NewTaskEditNavSweep) / sizeof(NewTaskEditNavSweep[0]));
	//}

	void RunAllNavigationSweeps()
	{
		RunManualOverrideDirectNavSweep();
		RunManualOverrideViewNavSweep();
		RunSchedTaskViewNavSweep();
		RunEnvSettingsViewNavSweep();
	}

	//void RunAllEditSweeps()
	//{
	//	RunLightCycleEditNavSweep();
	//	RunFanCycleEditNavSweep();
	//	RunAlarmsEditNavSweep();
	//}

	void RunPumpFanScheduledTaskROutine();

	//void RunL()
	//{
	//	ExecuteSteps(R, sizeof(R) / sizeof(R[0]));
	//	ExecuteSteps(L, sizeof(L) / sizeof(L[0]));
	//}

protected:
	
	void ExecuteSteps(TaskAlias steps[], int stepCount);

	TaskAlias DirectOverrideViewNavR[6] = {
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT
	};
	
	TaskAlias DirectOverrideViewNavL[6] = {
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT
	};

	TaskAlias ManualOverrideViewNavR[7] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT
	};

	TaskAlias ManualOverrideViewNavL[9] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT
	};

	TaskAlias SchedTaskViewNavR[41] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter schd task main menu
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter schd task SET task
		TASKALIAS_NAVIGATION_MENU_SELECT, //back to schd task main menu
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter schd task EDIT task
		TASKALIAS_NAVIGATION_MENU_SELECT, //back to schd task main menu
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter create/delete menu 
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter create new schd task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter set time for new task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter modal set fo new task HH
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT, //increment new task HH
		TASKALIAS_NAVIGATION_MENU_SELECT, //exit modal set for new task HH
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter modal set fo new task MM
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT, //increment new task MM
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT, //increment new task MM
		TASKALIAS_NAVIGATION_MENU_SELECT, //exit modal set for new task MM
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//BACK to create new task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		//TASKALIAS_NAVIGATION_MENU_SELECT, //SAVE new task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,// back to schd task create/delete
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		//todo... add delete task list view navigation
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		//todo.. add bulk delete
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,// back to scd task main menu view
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,// back to schd task TLMV
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT
	};

	TaskAlias SchedTaskViewNavL[45] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//enter schdtask menu view
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//enter create/delete
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		//todo... add bulk delete
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		//todo... add delete task
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//enter create new task
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//enter start time view
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//enter modal MM
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//exit modal MM
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//enter modal HH
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//exit modal HH
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//BACK to create new task view		
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		//todo... SAVE new scheduled task
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//BACK to create/delete
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//BACK to schd task main menu view
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		//todo... add EDIT EXISTING TASK view navigation
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		//todo... add SET EXISTING TASK view navigation
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//BACK to schd task TLMV
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT
	};

	TaskAlias EnvSettingsViewNavR[28] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT
	};

	TaskAlias EnvSettingsViewNavL[28] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_SELECT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
		TASKALIAS_NAVIGATION_MENU_MOVE_LEFT
	};

	//TaskAlias EnvSettings_LightCycleViewEditR[39] = {
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter envsettings main menu
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter sunrise/set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter sunrise input prompt
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment sunrise HH
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment sunrise MM
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to sunrise/set view, sunrise highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter sunset input prompt
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment sunset HH
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment sunset MM
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to sunrise/set view, sunset highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//toggle default light light cycle
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings main menu, sunrise/set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings TLMV
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT	//HOME
	//};

	//TaskAlias EnvSettings_LightCycleViewEditL[43] = {
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter envsettings main menu
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter sunrise/set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//toggle default light light cycle
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter sunset input prompt
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunset MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunset MM
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunset HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunset HH
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to sunrise/set view, sunset highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter sunrise input prompt
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunrise MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunrise MM
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal MM
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunrise HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement sunrise HH
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal HH
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to sunrise/set view, sunrise highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings main menu, sunrise/set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings TLMV
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT		//HOME
	//};

	//TaskAlias RunFanCycleEditNavR[31] = {
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter envsettings main menu
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter AirCirc view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter DayFanDutyCyc Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to AirCirc view, DayFanDutyCyc Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter NightFanDutyCyc Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to AirCirc view, NightFanDutyCyc Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//Toggle FanCyc Mode mode
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings main menu, AirCirc highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings TLMV
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT	//HOME
	//};

	//TaskAlias RunFanCycleEditNavL[33] = {
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter envsettings main menu
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter AirCirc view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//Toggle FanCyc Mode mode
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter NightFanDutyCyc Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on NightFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to AirCirc view, NightFanDutyCyc Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter DayFanDutyCyc Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on DayFanDutyCyc threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to AirCirc view, DayFanDutyCyc Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings main menu, AirCirc highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings TLMV
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT		//HOME
	//};

	//TaskAlias RunAlarmsEditNavR[31] = {
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter envsettings main menu
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter alarmthresholds view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter OverTemp Alarm Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to alarmthresholds view, OverTemp Alarm Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter OverHumid Alarm Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,	//increment OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to alarmthresholds view, OverHumid Alarm Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//Toggle LogFullAlarm mode
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings main menu, Alarm Thresholds highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings TLMV
	//	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT	//HOME
	//};

	//TaskAlias RunAlarmsEditNavL[33] = {
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter envsettings main menu
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter alarmthresholds view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//Toggle LogFullAlarm mode
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter OverHumid Alarm Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on OverHumid Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to alarmthresholds view, OverHumid Alarm Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter OverTemp Alarm Set view
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//enter modal on OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,	//decrement OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//exit modal on OverTemp Alarm threesegment value
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to alarmthresholds view, OverTemp Alarm Set highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings main menu, Alarm Thresholds highlighted
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_SELECT,		//BACK to envsettings TLMV
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	//	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT		//HOME
	//};


	TaskAlias NewTaskEditNavSweep[28] = {
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter schd task main menu
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter create/delete menu 
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter create new schd task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_SELECT, //rotate task type
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter set time for new task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter modal set fo new task HH
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT, //increment new task HH
		TASKALIAS_NAVIGATION_MENU_SELECT, //exit modal set for new task HH
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //enter modal set fo new task MM
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT, //increment new task MM
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT, //increment new task MM
		TASKALIAS_NAVIGATION_MENU_SELECT, //exit modal set for new task MM
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT,//BACK to create new task
		TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
		TASKALIAS_NAVIGATION_MENU_SELECT, //SAVE new task
	};

private:
	const CommandInterpreter *_ci;
	TaskExecutor *_ta;
	TaskScheduler *_ts;
	ComponentModuleGroup_PX4 _moduleGroup;
};


inline void NavigationRoutine::RunPumpFanScheduledTaskROutine()
{
	//Both fan and pump ENABLED at 60 second mark
	//Both fan and pump DISABLED at 90 seconds mark
	//Pump ENABLED at 120 second mark
	//Pump DISABLED at 180 second mark
	//Fan ENABLED at 180 second mark
	//Fan DISABLED at 195 second mark
	DataModel_PX4::GetInstance().SetActiveViewstate(VIEWSTATEALIAS_MANUAL_OVERRIDE_VIEW);

	TimeSignature tsNow = _moduleGroup.RTC()->GetCurrentSystemTime();

	TimeSignature tsPump{ 0, 0, 0, tsNow.hour(), (uint8_t)(tsNow.minute() + 1), 0 };
	TimeSignature tsFan{ 0, 0, 0, tsNow.hour(), (uint8_t)(tsNow.minute() + 1), 0 };

	DataModel_PX4::GetInstance().GetScheduledTaskPool()->AddNewScheduledTask(TASKALIAS_ENABLE_POWER_RELAY_FAN, tsFan);

	DataModel_PX4::GetInstance().GetScheduledTaskPool()->AddNewScheduledTask(TASKALIAS_ENABLE_POWER_RELAY_PUMP, tsPump);

	tsPump.AdjustMM(1);
	DataModel_PX4::GetInstance().GetScheduledTaskPool()->AddNewScheduledTask(TASKALIAS_ENABLE_POWER_RELAY_PUMP, tsPump);

	tsFan.AdjustMM(2);	
	DataModel_PX4::GetInstance().GetScheduledTaskPool()->AddNewScheduledTask(TASKALIAS_ENABLE_POWER_RELAY_FAN, tsFan);
	tsPump.AdjustMM(100);
	DataModel_PX4::GetInstance().GetScheduledTaskPool()->AddNewScheduledTask(TASKALIAS_ENABLE_POWER_RELAY_PUMP, tsPump);
}


inline void NavigationRoutine::ExecuteSteps(TaskAlias steps[], int stepCount)
{
	for (size_t x = 0; x < stepCount; ++x)
	{
		if (steps[x] != TASKALIAS_NOT_SET)
		{
			_ci->InvokeTaskRequest(steps[x]);
			_ta->ProcessTaskQueue(2);

			#if defined(TARGET_PLAT_AVR)
			delay(500);
			#endif
		}
	}
}