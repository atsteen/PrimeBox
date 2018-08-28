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

#include "..\..\..\Configurations\PX4_Config.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\INavigationTones.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IPostTones.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IPowerRelayArray.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_PowerRelay_Standard.h"

class ComponentPackage_PowerRelayArray : public IPowerRelayArray
{
public:
	ComponentPackage_PowerRelayArray(ComponentModuleImp_Factory_PX4* componentImpFactory, IPersistentDataCoordinator * persistentDataCoordinator, IRtcLogger * logger);
	~ComponentPackage_PowerRelayArray();

	// Inherited via IPowerRelayArray
	virtual bool AddPowerRelay(const PersistentComponentAlias, const PersistentDataAlias, const ComponentTypeAssociation, const ComponentGroupAssociation) override;
	virtual int CircuitCount() override;
	virtual void EnableAll() override;
	virtual void DisableAll() override;
	virtual bool IsEnabledByAlias(const PersistentComponentAlias) override;
	virtual void EnableByIndex(const int) override;
	virtual void DisableByIndex(const int) override;
	virtual void ReleaseOverrideByIndex(const int) override;
	virtual void InstateOverrideByIndex(const int) override;
	virtual void EnableByAlias(const PersistentComponentAlias) override;
	virtual void DisableByAlias(const PersistentComponentAlias) override;
	virtual void EnableAllTypesInGroup(const ComponentTypeAssociation, const ComponentGroupAssociation) override;
	virtual void DisableAllTypesInGroup(const ComponentTypeAssociation, const ComponentGroupAssociation) override;
	virtual const ComponentPowerState GetRelayPowerStateByIndex(const int) override;
	virtual const ComponentAssociation * const GetRelayComponentAssociationByIndex(const int) override;
	virtual void SetRelayComponentAssociationByIndex(const int, const ComponentAssociation * const) override;

private:
	ComponentModuleImp_Factory_PX4 * _componentImpFactory;
	IPersistentDataCoordinator * _persistentDataCoordinator;
	ComponentModule_PowerRelay_Standard *_powerRelays[POWER_RELAY_COUNT];
	IRtcLogger * _logger;

	void _LogRelayStateChange(int index);
};