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
#include "..\..\..\..\..\Configurations\PX4_Config.h"
#include "..\..\..\..\..\Platform\include\SharedStructure\TimeSignature.h"
#include "..\..\..\..\..\Platform\include\SharedStructure\\SystemSKU.h"
#include "..\..\..\..\..\Platform\include\SharedStructure\\ScheduledTaskDetail.h"
#include "..\..\..\ComponentModule_Imp_NvMemoryManager.h"
#include "..\..\..\..\..\Platform\include\SharedStructure\\T_DataItemList.h"
#include "..\..\..\..\..\Platform\include\SharedStructure\PersistentData\PersistentData_PX4.h"

#if defined(TARGET_PLAT_WIN32)

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>

class ComponentModule_Imp_NvMemoryManager_Win32 :
	public ComponentModule_Imp_NvMemoryManager
{
public:
	ComponentModule_Imp_NvMemoryManager_Win32();
	virtual ~ComponentModule_Imp_NvMemoryManager_Win32() override;

	void SsTokens(const string str, const char delim, vector<string> * vecPtr);
	void AppendPersistentData(const string);
	void OverwritePersistentData(const string);

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
	const string _persistentDataItemFileDir = "PersistentData";
	const string _persistentDataItemFileName = "PersistentDataValues.csv";
	const string relativeFilePath = _persistentDataItemFileDir + "\\" + _persistentDataItemFileName;
	PersistentData_PX4 _persistentDataMap;
	map<PersistentDataAlias, string> _persistentDataAliasNameMap;
};

#endif