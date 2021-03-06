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
#include "..\PersistentDataAlias.h"
#include "..\TimeSignature.h"
#include "..\SystemSKU.h"
#include "..\PowerRelayStateData.h"
#include "..\..\..\..\Configurations\PX4_Config.h"
//#include "PX4_Config.h"
#include "..\ScheduledTaskDetail.h"

class IPersistentDataCoordinator
{
public:
	IPersistentDataCoordinator() {};
	~IPersistentDataCoordinator();

	virtual bool ReadPersistentItem(bool *, const PersistentDataAlias) = 0;
	virtual bool ReadPersistentItem(int *, const PersistentDataAlias) = 0;
	virtual bool ReadPersistentItem(TimeSignature *, const PersistentDataAlias) = 0;
	virtual bool ReadPersistentItem(SystemSKU *, const PersistentDataAlias) = 0;
	virtual bool ReadPersistentItem(PowerRelayStateData *, const PersistentDataAlias) = 0;
	virtual bool ReadPersistentItem(ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias) = 0;
	

	virtual bool WritePersistentItem(const bool *, const PersistentDataAlias) = 0;
	virtual bool WritePersistentItem(const int *, const PersistentDataAlias) = 0;
	virtual bool WritePersistentItem(const TimeSignature *, const PersistentDataAlias) = 0;
	virtual bool WritePersistentItem(const SystemSKU *, const PersistentDataAlias) = 0;
	virtual bool WritePersistentItem(const PowerRelayStateData *, const PersistentDataAlias) = 0;
	virtual bool WritePersistentItem(const ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias) = 0;
};

inline IPersistentDataCoordinator::~IPersistentDataCoordinator() {}