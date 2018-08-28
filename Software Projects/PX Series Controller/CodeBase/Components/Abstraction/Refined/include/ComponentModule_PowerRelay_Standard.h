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

#include "..\..\ComponentModule_PowerRelay.h"
#include "..\..\..\Abstraction\IComponentModule_PowerState.h"
#include "..\..\..\..\Platform\include\SharedStructure\SharedInterface\Ipersistent.h"
#include "..\..\..\..\Platform\include\SharedStructure\PowerRelayStateData.h"
#include "..\..\..\..\Platform\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

class ComponentModule_PowerRelay_Standard :
	public ComponentModule_PowerRelay,
	public IComponentModule_PowerState,
	public Ipersistent
{
public:
	ComponentModule_PowerRelay_Standard(ComponentModule_Imp_PowerRelay *imp, const PersistentComponentAlias componentAlias, PersistentDataAlias dataAlias, IPersistentDataCoordinator * persistentDataCoordinator);
	virtual ~ComponentModule_PowerRelay_Standard() override;

	bool isInOverride = false;
	const ComponentAssociation * const GetComponentAssociation();
	const ViewstateStringAlias GetRelayGroupName();
	const ViewstateStringAlias GetRelayTypeName();
	void SetComponentAssociation(const ComponentAssociation * const);
	void SetPowerState (const ComponentPowerState);

	// Inherited via ComponentModule
	virtual bool DoSelfDiagnostic() override;

	// Inherited via ComponentModule_PowerRelay
	virtual void Enable() override;
	virtual void Disable() override;

	// Inherited via IComponentModule_PowerState
	virtual const bool IsEnabled() override;
	virtual const bool IsInOverride() override;
	virtual const ComponentPowerState GetPowerState() override;

	// Inherited via Ipersistent
	virtual const PersistentComponentAlias GetComponentAlias() override;
	virtual void RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;

protected:

	PersistentDataAlias persistentDataAlias;
	PowerRelayStateData stateData;

	// Inherited via Ipersistent
	virtual void UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;
};

