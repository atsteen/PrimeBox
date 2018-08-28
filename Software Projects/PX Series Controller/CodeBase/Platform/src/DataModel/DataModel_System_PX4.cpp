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

#include "..\..\include\DataModel\DataModel_System_PX4.h"

DataModel_System_PX4::DataModel_System_PX4(const PersistentComponentAlias ca, IPersistentDataCoordinator * pdc, IRtcLogger * rtcLogger) :
	Ipersistent(ca, pdc), _rtcLogger(rtcLogger) { this->RestorePersistentData(_persistentDataCoordinator); }

void DataModel_System_PX4::SetControllerRestartSignal(bool restartSignal)
{
	_signalControllerRestart = restartSignal;
	this->notifyObservers();
}

const bool DataModel_System_PX4::GetControllerRestartSignal()
{
	return _signalControllerRestart;
}

const SystemSKU * DataModel_System_PX4::GetSystemSKU()
{
	return &_sysSKU;
}

const bool * const DataModel_System_PX4::GetLogAlarmDefaultState()
{
	return &_logAlarmDefaultState;
}

void DataModel_System_PX4::SetLogAlarmDefaultState(const bool * const state)
{
	_logAlarmDefaultState = *state;
	this->notifyObservers();
	this->UpdatePersistentData(_persistentDataCoordinator);
}

const PersistentComponentAlias DataModel_System_PX4::GetComponentAlias()
{
	return this->_componentAlias;
}

void DataModel_System_PX4::RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent)
{
	persistentDataAgent->ReadPersistentItem(&_logAlarmDefaultState, PersistentDataAlias::ALARM_LOGFULL_STATE);
	persistentDataAgent->ReadPersistentItem(&_sysSKU, PersistentDataAlias::SYSTEM_SKU);
}

void DataModel_System_PX4::UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent)
{
	persistentDataAgent->WritePersistentItem(&_logAlarmDefaultState, PersistentDataAlias::ALARM_LOGFULL_STATE);
	persistentDataAgent->WritePersistentItem(&_sysSKU, PersistentDataAlias::SYSTEM_SKU);
}

const ViewstateStringAlias DataModel_System_PX4::GetSystemMode()
{
	return _systemMode;
}

const char * DataModel_System_PX4::GetCurrentTimeText()
{
	return _rtcLogger->CurrentTimeAsText();
}