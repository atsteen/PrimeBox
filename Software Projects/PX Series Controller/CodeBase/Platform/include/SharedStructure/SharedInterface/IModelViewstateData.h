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

#include "..\TimeSignature.h"
#include "..\SharedInterface\ISelectableNavigationMap.h"
#include "..\..\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\Subject.h"
#include "..\SharedInterface\IDynamicData.h"

class IModelViewstateData
{
public:
	IModelViewstateData() {}; 
	virtual ~IModelViewstateData();

	virtual ISelectableNavigationMap * const GetNavigationMap() = 0;
	virtual ISelectableNavigationMap * const SetNavigationMap(ISelectableNavigationMap * newMap) = 0;
	virtual ISelectableNavigationMap * const SetNavigationMap(ISelectableNavigationMap * newMap, const int selectedElementIndex) = 0;

	virtual const TimeSignature * LastViewstatePublish() = 0;
	virtual void RegisterViewstatePublish(TimeSignature ts) = 0;

	virtual const bool GetDynamicViewstateModalState() const = 0;
	virtual void SetDynamicViewstateModalState(const bool value) = 0;
	virtual const int GetViewstateSelectableElementIndex() = 0;
	virtual void SetViewstateSelectableElementIndex(const int selectedElementIndex) = 0;
	virtual void ForceModelUpdateNotify() = 0;

	//DynamicDataProxy methods
	virtual void RegisterDynamicDataProxy(IDynamicData * dynamicData) = 0;
	virtual IDynamicData * GetDynamicDataProxy() = 0;


};

inline IModelViewstateData::~IModelViewstateData() {}