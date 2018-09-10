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
#include "..\SharedStructure\Subject.h"
#include "..\SharedStructure\SharedInterface\IModelSystemData.h"
#include "..\SharedStructure\SharedInterface\Ipersistent.h"
#include "..\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\Viewstate_String_Generator\Viewstate_String_Generator.h"

class DataModel_System_PX4 :
	public IModelSystemData,
	public Ipersistent,
	public Subject
{
public:
	DataModel_System_PX4(const PersistentComponentAlias, IPersistentDataCoordinator *, IRtcLogger *);
	~DataModel_System_PX4() {};

	// Inherited via IModelSystemData
	virtual void SetControllerRestartSignal(bool) override;
	virtual const bool GetControllerRestartSignal() override;
	virtual const SystemSKU * GetSystemSKU() override;
	virtual const bool * const GetLogAlarmDefaultState() override;
	virtual void SetLogAlarmDefaultState(const bool * const state) override;
	virtual const ViewstateStringAlias GetSystemMode() override;
	virtual const char * GetCurrentTimeText();

protected:
	// Inherited via Ipersistent
	virtual const PersistentComponentAlias GetComponentAlias() override;
	virtual void RestorePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;
	virtual void UpdatePersistentData(IPersistentDataCoordinator * persistentDataAgent) override;

private:
	bool _signalControllerRestart = false;
	SystemSKU _sysSKU = { '0', '0', '3' };
	bool _logAlarmDefaultState = true;
	ViewstateStringAlias _systemMode = ViewstateStringAlias::EVENT_TEXT_SYSTEMSTATUS_INIT;
	IRtcLogger * _rtcLogger = {};
};