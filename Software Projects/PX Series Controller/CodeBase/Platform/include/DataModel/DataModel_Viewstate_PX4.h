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
#include "..\SharedStructure\SharedInterface\IModelViewstateData.h"
#include "..\SharedStructure\Subject.h"

class DataModel_Viewstate_PX4 : public IModelViewstateData, public Subject
{
public:
	DataModel_Viewstate_PX4() {};
	~DataModel_Viewstate_PX4() {};	

	// Inherited via IModelViewstateData
	virtual ISelectableNavigationMap * const GetNavigationMap() override;
	virtual ISelectableNavigationMap * const SetNavigationMap(ISelectableNavigationMap * newMap) override;
	virtual ISelectableNavigationMap * const SetNavigationMap(ISelectableNavigationMap * newMap, const int selectedElementIndex) override;
	virtual const TimeSignature * LastViewstatePublish() override;
	virtual void RegisterViewstatePublish(TimeSignature ts) override;
	virtual const bool GetDynamicViewstateModalState() const override;
	virtual void SetDynamicViewstateModalState(const bool value) override;
	virtual const int GetViewstateSelectableElementIndex() override;
	virtual void SetViewstateSelectableElementIndex(const int selectedElementIndex) override;
	virtual void ForceModelUpdateNotify() override { this->notifyObservers(); }

	virtual void RegisterDynamicDataProxy(IDynamicData * dynamicData) override;
	virtual IDynamicData * GetDynamicDataProxy() override { return _dynamicData; }


private:
	bool _viewstateIsModal = false;
	TimeSignature _lastStatusPublish = { 2000,1,1 };
	ISelectableNavigationMap * _viewstateMap = {};
	IDynamicData * _dynamicData = {};

	//deprecate once viewstates are refactored using dynamic data proxy
	int _dynamicViewstateSelectedElementIndex = 0; 
	ViewstateStringAlias _dynamicViewstateTitleAlias;
	const char * _dynamicViewstateSuffixSymbol = {};
};