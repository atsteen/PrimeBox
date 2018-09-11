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

#include "..\..\include\DataModel\DataModel_Viewstate_PX4.h"

const TimeSignature * DataModel_Viewstate_PX4::LastViewstatePublish()
{
	return &_lastStatusPublish;
}

//TODO - review all references, ensure status publish isnt confused with viewstate publish in callers...
void DataModel_Viewstate_PX4::RegisterViewstatePublish(TimeSignature ts)
{
	_lastStatusPublish.SetSignature(&ts);
}

const int DataModel_Viewstate_PX4::GetViewstateSelectableElementIndex()
{
	return _dynamicViewstateSelectedElementIndex;
}

void DataModel_Viewstate_PX4::SetViewstateSelectableElementIndex(const int selectedElementIndex)
{
	_dynamicViewstateSelectedElementIndex = selectedElementIndex;
}

const bool DataModel_Viewstate_PX4::GetDynamicViewstateModalState() const
{
	return _viewstateIsModal;
}

void DataModel_Viewstate_PX4::SetDynamicViewstateModalState(const bool value)
{
	_viewstateIsModal = value;
}

void DataModel_Viewstate_PX4::RegisterDynamicDataProxy(IDynamicData * dynamicData)
{
	if (_dynamicData) { delete _dynamicData; }
	_dynamicData = dynamicData;
}

ISelectableNavigationMap * const DataModel_Viewstate_PX4::GetNavigationMap()
{
	return _viewstateMap;
}

ISelectableNavigationMap * const DataModel_Viewstate_PX4::SetNavigationMap(ISelectableNavigationMap * newMap)
{
	//todo... next statement is misleading if map is already altered...
	_viewstateMap = newMap;
	this->notifyObservers();
	return _viewstateMap;
}

ISelectableNavigationMap * const DataModel_Viewstate_PX4::SetNavigationMap(ISelectableNavigationMap * newMap, const int selectedElementIndex)
{
	this->SetViewstateSelectableElementIndex(selectedElementIndex);
	return this->SetNavigationMap(newMap);
}


