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

#include "..\include\ComponentModule_PowerRelay_Standard.h"

ComponentModule_PowerRelay_Standard::ComponentModule_PowerRelay_Standard(ComponentModule_Imp_PowerRelay * imp, const PersistentComponentAlias componentAlias, PersistentDataAlias dataAlias, IPersistentDataCoordinator * persistentDataCoordinator)
	: ComponentModule_PowerRelay(imp), Ipersistent(componentAlias, persistentDataCoordinator), persistentDataAlias(dataAlias)
{
	if(this->_persistentDataCoordinator){ RestorePersistentData(this->_persistentDataCoordinator); }
}

ComponentModule_PowerRelay_Standard::~ComponentModule_PowerRelay_Standard(){}

const ComponentAssociation * const ComponentModule_PowerRelay_Standard::GetComponentAssociation()
{
	return &stateData.association;
}

const ViewstateStringAlias ComponentModule_PowerRelay_Standard::GetRelayGroupName()
{
	switch (this->stateData.association.groupAssociation) {
	case ComponentGroupAssociation::GROUP_B :
		return COMPONENT_TEXT_SHORT_GROUP_B;
		break;
	case ComponentGroupAssociation::GROUP_C:
		return COMPONENT_TEXT_SHORT_GROUP_C;
		break;
	case ComponentGroupAssociation::GROUP_D:
		return COMPONENT_TEXT_SHORT_GROUP_D;
		break;
	default:
		return COMPONENT_TEXT_SHORT_GROUP_A;
	}
}

const ViewstateStringAlias ComponentModule_PowerRelay_Standard::GetRelayTypeName()
{
	switch (this->stateData.association.typeAssociation) {
	case ComponentTypeAssociation::FAN_CIRCULATION :
		return COMPONENT_TEXT_SHORT_CIRCULATION_FAN;
		break;
	case ComponentTypeAssociation::FAN_EXHAUST :
		return COMPONENT_TEXT_SHORT_EXHAUST_FAN;
		break;
	case ComponentTypeAssociation::PUMP_WATER:
		return COMPONENT_TEXT_SHORT_LIGHT;
		break;
	case ComponentTypeAssociation::LIGHT_PRIMARY:
		return COMPONENT_TEXT_SHORT_PUMP;
		break;
	default:
		return COMPONENT_TEXT_SHORT_OUTLET;
	}
}

void ComponentModule_PowerRelay_Standard::SetComponentAssociation(const ComponentAssociation * const newAssociation)
{
	stateData.association.typeAssociation = newAssociation->typeAssociation;
	stateData.association.groupAssociation = newAssociation->groupAssociation;
	if (this->_persistentDataCoordinator) { UpdatePersistentData(this->_persistentDataCoordinator); }
}

void ComponentModule_PowerRelay_Standard::SetPowerState(const ComponentPowerState powerstate)
{
	this->stateData.powerState = powerstate;
	if (this->_persistentDataCoordinator) { UpdatePersistentData(this->_persistentDataCoordinator); }
}

bool ComponentModule_PowerRelay_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}

const bool ComponentModule_PowerRelay_Standard::IsEnabled()
{
	//TODO - redundant metod, migrate to GetState()
	return _imp->GetState();
}

void ComponentModule_PowerRelay_Standard::Enable()
{
	if (stateData.powerState == ComponentPowerState::OVERRIDE_ENABLED || stateData.powerState == ComponentPowerState::OVERRIDE_DISABLED) { return; }
	_imp->SetState(true);
	stateData.powerState = ComponentPowerState::ENABLED;
	if (this->_persistentDataCoordinator){ UpdatePersistentData(this->_persistentDataCoordinator); }
}

void ComponentModule_PowerRelay_Standard::Disable()
{
	if (stateData.powerState == ComponentPowerState::OVERRIDE_ENABLED || stateData.powerState == ComponentPowerState::OVERRIDE_DISABLED) { return; }
	_imp->SetState(false);
	stateData.powerState = ComponentPowerState::DISABLED;
	if (this->_persistentDataCoordinator) { UpdatePersistentData(this->_persistentDataCoordinator); }
}

const bool ComponentModule_PowerRelay_Standard::IsInOverride()
{
	//TODO - redundant metod, migrate to GetState()
	return isInOverride;
}

const ComponentPowerState ComponentModule_PowerRelay_Standard::GetPowerState()
{
	return stateData.powerState;
}

void ComponentModule_PowerRelay_Standard::RestorePersistentData(IPersistentDataCoordinator * persistentDataCoordinator)
{
	persistentDataCoordinator->ReadPersistentItem(&stateData, persistentDataAlias);

	if (stateData.powerState == ComponentPowerState::ENABLED | stateData.powerState == ComponentPowerState::OVERRIDE_ENABLED)
	{
		this->_imp->SetState(true);
	}
}

void ComponentModule_PowerRelay_Standard::UpdatePersistentData(IPersistentDataCoordinator * persistentDataCoordinator)
{
	persistentDataCoordinator->WritePersistentItem(&stateData, persistentDataAlias);
}

const PersistentComponentAlias ComponentModule_PowerRelay_Standard::GetComponentAlias()
{
	return this->_componentAlias;
}
