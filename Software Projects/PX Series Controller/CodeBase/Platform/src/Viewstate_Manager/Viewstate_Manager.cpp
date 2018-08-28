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

#include "..\..\include\Viewstate_Manager\Viewstate_Manager.h"

Viewstate_Manager::Viewstate_Manager(
	IViewstate_Group * viewStates,
	IModelViewstateData * viewstateData,
	ComponentPackage_UI_PX4 * interfacePackage,
	ComponentPackage_RtcLogger * rtcLogger)
	: _viewStates(viewStates), _viewstateData(viewstateData), _interfacePackage(interfacePackage), _rtcLogger(rtcLogger)
{}

const char * Viewstate_Manager::GetActiveViewContent()
{
	ViewstateAlias activeViewAlias = _viewstateData->GetNavigationMap()->ViewstateAssociation();
	ITextViewstate * _activeView = _viewStates->GetViewstateByAlias(activeViewAlias);	
	return _activeView->RenderText(_outTextBuff, OUT_BUFF_TEXTSIZE);
}

void Viewstate_Manager::update(Subject & s)
{
	if (_viewstateData->GetNavigationMap()->CurrentSelection()->viewstate == ViewstateAlias::VIEWSTATEALIAS_NOT_SET) { return; }
	_interfacePackage->WriteDisplayText(GetActiveViewContent());	
	_viewstateData->RegisterViewstatePublish(_rtcLogger->CurrentTime());
}