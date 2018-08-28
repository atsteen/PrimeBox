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
#include "..\ComponentAssociation.h"
#include "..\PersistentDataAlias.h"
#include "..\ComponentPowerState.h"

class IPowerRelayArray
{
public:
	IPowerRelayArray() {};
	~IPowerRelayArray();

	virtual bool AddPowerRelay(const PersistentComponentAlias, const PersistentDataAlias, const ComponentTypeAssociation, const ComponentGroupAssociation) = 0;
	virtual int CircuitCount() = 0;
	virtual void EnableAll() = 0;
	virtual void DisableAll() = 0;
	virtual bool IsEnabledByAlias(const PersistentComponentAlias) = 0;
	virtual void EnableByIndex(const int) = 0;
	virtual void DisableByIndex(const int) = 0;
	virtual void ReleaseOverrideByIndex(const int) = 0;
	virtual void InstateOverrideByIndex(const int) = 0;
	virtual void EnableByAlias(const PersistentComponentAlias) = 0;
	virtual void DisableByAlias(const PersistentComponentAlias) = 0;
	virtual void EnableAllTypesInGroup(const ComponentTypeAssociation, const ComponentGroupAssociation) = 0;
	virtual void DisableAllTypesInGroup(const ComponentTypeAssociation, const ComponentGroupAssociation) = 0;
	virtual const ComponentPowerState GetRelayPowerStateByIndex(const int) = 0;
	virtual const ComponentAssociation * const GetRelayComponentAssociationByIndex(const int) = 0;
	virtual void SetRelayComponentAssociationByIndex(const int, const ComponentAssociation * const) = 0;
};

inline IPowerRelayArray::~IPowerRelayArray() {}