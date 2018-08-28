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

#include "..\include\ComponentPackage_PowerRelayArray.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IPersistentDataCoordinator.h"
#include "..\..\..\Platform\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_PowerRelayStateEvent.h"

ComponentPackage_PowerRelayArray::ComponentPackage_PowerRelayArray(ComponentModuleImp_Factory_PX4* componentImpFactory, IPersistentDataCoordinator * persistentDataCoordinator, IRtcLogger * logger)
	: _componentImpFactory(componentImpFactory), _persistentDataCoordinator(persistentDataCoordinator), _logger(logger){}

ComponentPackage_PowerRelayArray::~ComponentPackage_PowerRelayArray() 
{ 
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i]) { delete _powerRelays[i]; }
	}
}

int ComponentPackage_PowerRelayArray::CircuitCount()
{
	for (int i = 1; i < POWER_RELAY_COUNT; i++)
	{
		if (!_powerRelays[i]) { return i; }
	}

	return POWER_RELAY_COUNT;
}

void ComponentPackage_PowerRelayArray::EnableAll()
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i]) { _powerRelays[i]->Enable(); }
	}
}

void ComponentPackage_PowerRelayArray::DisableAll()
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i]) { _powerRelays[i]->Disable(); }
	}
}

bool ComponentPackage_PowerRelayArray::IsEnabledByAlias(const PersistentComponentAlias alias)
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i] && _powerRelays[i]->GetComponentAlias() == alias && _powerRelays[i]->IsEnabled())
		{
			return true;
		}
	}

	return false;
}

void ComponentPackage_PowerRelayArray::EnableByIndex(const int index)
{
	const ComponentPowerState currentState = _powerRelays[index]->GetPowerState();
	if (currentState == ComponentPowerState::OVERRIDE_DISABLED) { return; }
	_powerRelays[index]->Enable();
	_LogRelayStateChange(index);
}

void ComponentPackage_PowerRelayArray::DisableByIndex(const int index)
{
	const ComponentPowerState currentState = _powerRelays[index]->GetPowerState();
	if (currentState == ComponentPowerState::OVERRIDE_ENABLED) { return; }
	_powerRelays[index]->Disable();
	_LogRelayStateChange(index);
}

void ComponentPackage_PowerRelayArray::InstateOverrideByIndex(const int index)
{
	if(_powerRelays[index]->IsEnabled())
	{
		_powerRelays[index]->SetPowerState(ComponentPowerState::OVERRIDE_ENABLED);
	}
	else { _powerRelays[index]->SetPowerState(ComponentPowerState::OVERRIDE_DISABLED); }	
}

void ComponentPackage_PowerRelayArray::ReleaseOverrideByIndex(const int index)
{
	if (_powerRelays[index]->IsEnabled())
	{
		_powerRelays[index]->SetPowerState(ComponentPowerState::ENABLED);
	}
	else { _powerRelays[index]->SetPowerState(ComponentPowerState::DISABLED); }
}

void ComponentPackage_PowerRelayArray::EnableByAlias(const PersistentComponentAlias alias)
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i] && !_powerRelays[i]->IsEnabled() && _powerRelays[i]->GetComponentAlias() == alias) { _powerRelays[i]->Enable(); }
	}
}

void ComponentPackage_PowerRelayArray::DisableByAlias(const PersistentComponentAlias alias)
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i] && _powerRelays[i]->IsEnabled() && _powerRelays[i]->GetComponentAlias() == alias) { _powerRelays[i]->Disable(); }
	}
}

void ComponentPackage_PowerRelayArray::EnableAllTypesInGroup(const ComponentTypeAssociation compType, const ComponentGroupAssociation compGroup)
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (_powerRelays[i]->IsEnabled()) { continue; }

		const ComponentAssociation * const targetAssociation = _powerRelays[i]->GetComponentAssociation();
		if (_powerRelays[i] && targetAssociation->typeAssociation == compType && targetAssociation->groupAssociation == compGroup)
		{
			EnableByIndex(i);
		}
	}
}

void ComponentPackage_PowerRelayArray::DisableAllTypesInGroup(const ComponentTypeAssociation compType, const ComponentGroupAssociation compGroup)
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (!_powerRelays[i]->IsEnabled()) { continue; }

		const ComponentAssociation * const targetAssociation = _powerRelays[i]->GetComponentAssociation();
		if (_powerRelays[i] && targetAssociation->typeAssociation == compType && targetAssociation->groupAssociation == compGroup)
		{
			DisableByIndex(i);
		}
	}
}

const ComponentPowerState ComponentPackage_PowerRelayArray::GetRelayPowerStateByIndex(const int index)
{
	return _powerRelays[index]->GetPowerState();
}

const ComponentAssociation * const ComponentPackage_PowerRelayArray::GetRelayComponentAssociationByIndex(const int relayIndex)
{
	if (relayIndex > this->CircuitCount() - 1) { return _powerRelays[this->CircuitCount() - 1]->GetComponentAssociation(); } // todo.. handle with bounds exception
	return _powerRelays[relayIndex]->GetComponentAssociation();
}

void ComponentPackage_PowerRelayArray::SetRelayComponentAssociationByIndex(const int relayIndex, const ComponentAssociation * const association)
{
	if (!association) { return; }

	this->_powerRelays[relayIndex]->SetComponentAssociation(association);
}

void ComponentPackage_PowerRelayArray::_LogRelayStateChange(int index)
{
	IViewstate_Element * eventLogElement = new Viewstate_Element_Text_PowerRelayStateEvent(0, 1, index, *GetRelayComponentAssociationByIndex(index), GetRelayPowerStateByIndex(index));
	_logger->LogEvent(eventLogElement);
}

bool ComponentPackage_PowerRelayArray::AddPowerRelay(const PersistentComponentAlias componentAlias, const PersistentDataAlias dataAlias, const ComponentTypeAssociation type, const ComponentGroupAssociation group)
{
	for (int i = 0; i < POWER_RELAY_COUNT; i++)
	{
		if (!_powerRelays[i])
		{
			ComponentAssociation association = { group, type };
			_powerRelays[i] = new ComponentModule_PowerRelay_Standard(_componentImpFactory->Make_PowerRelay(componentAlias), componentAlias, dataAlias, _persistentDataCoordinator);
			if (_powerRelays[i]->GetComponentAssociation()->typeAssociation == ComponentTypeAssociation::TYPE_NOT_SET) { _powerRelays[i]->SetComponentAssociation(&association); }

			return true;
		}
	}

	//TODO, add exception handling
	return false; 
}
