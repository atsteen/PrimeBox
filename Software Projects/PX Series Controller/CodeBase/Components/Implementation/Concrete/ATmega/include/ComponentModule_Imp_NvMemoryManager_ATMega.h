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
#include "PX4_Config.h"
#include "..\SharedStructure\TimeSignature.h"
#include "..\SharedStructure\SystemSKU.h"
#include "ComponentModule_Imp_NvMemoryManager.h"
#include "..\SharedStructure\T_DataItemList.h"
#include "..\SharedStructure\PersistentData\PersistentData_PX4.h"

#if defined(TARGET_PLAT_AVR)

class ComponentModule_Imp_NvMemoryManager_ATMega :
	public ComponentModule_Imp_NvMemoryManager
{
public:
	ComponentModule_Imp_NvMemoryManager_ATMega();
	virtual ~ComponentModule_Imp_NvMemoryManager_ATMega() override;

	// Inherited via ComponentModule_Imp
	virtual bool DoSelfDiagnostic_Imp() override;

	// Inherited via ComponentModule_Imp_NvMemoryManager
	virtual bool ReadPersistentItem(bool *, const PersistentDataAlias) override;
	virtual bool ReadPersistentItem(int *, const PersistentDataAlias) override;
	virtual bool ReadPersistentItem(TimeSignature *, const PersistentDataAlias) override;
	virtual bool ReadPersistentItem(SystemSKU *, const PersistentDataAlias) override;
	virtual bool ReadPersistentItem(PowerRelayStateData *, const PersistentDataAlias) override;
	virtual bool ReadPersistentItem(ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias) override;

	virtual bool WritePersistentItem(const bool *, const PersistentDataAlias) override;
	virtual bool WritePersistentItem(const int *, const PersistentDataAlias) override;
	virtual bool WritePersistentItem(const TimeSignature *, const PersistentDataAlias) override;
	virtual bool WritePersistentItem(const SystemSKU *, const PersistentDataAlias) override;
	virtual bool WritePersistentItem(const PowerRelayStateData *, const PersistentDataAlias) override;
	virtual bool WritePersistentItem(const ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias) override;

protected:
	PersistentData_PX4 _persistentDataMap;

	struct sTaskDetail{
		uint8_t triggerhh = 0;
		uint8_t triggermm = 0;
		uint8_t triggerss = 0;
		TaskAlias taskAlias = TASKALIAS_NOT_SET;
		bool taskIsEnabled = 0;
	};
};

#endif