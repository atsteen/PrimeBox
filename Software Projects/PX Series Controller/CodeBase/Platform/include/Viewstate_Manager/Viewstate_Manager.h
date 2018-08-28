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

#include "..\SharedStructure\Observer.h"
#include "..\Viewstate\Group\IViewstate_Group.h"
#include "..\Viewstate\ITextViewstate.h"
#include "..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\..\..\Components\ComponentPackages\include\ComponentPackage_UI_PX4.h"
#include "..\..\..\Components\ComponentPackages\include\ComponentPackage_RtcLogger.h"

#define OUT_BUFF_TEXTSIZE 84

class Viewstate_Manager : public Observer
{
public:
	Viewstate_Manager(
		IViewstate_Group * viewStates,
		IModelViewstateData * viewstateData,
		ComponentPackage_UI_PX4 * interfacePackage,
		ComponentPackage_RtcLogger * rtcLogger
	);
	~Viewstate_Manager() {};

	const char * GetActiveViewContent();

private:	
	char _outTextBuff[OUT_BUFF_TEXTSIZE];
	IViewstate_Group * _viewStates;
	ComponentPackage_UI_PX4 * _interfacePackage;
	IModelViewstateData * _viewstateData;
	ComponentPackage_RtcLogger * _rtcLogger;
	NavigationMapSelection * _lastPublishedMapSelection;

	// Inherited via Observer
	virtual void update(Subject & s) override;
};