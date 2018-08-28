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

#include "..\include\ComponentModule_NvMemoryManager_Standard.h"

ComponentModule_NvMemoryManager_Standard::ComponentModule_NvMemoryManager_Standard(ComponentModule_Imp_NvMemoryManager * imp) : ComponentModule_NvMemoryManager(imp){}

ComponentModule_NvMemoryManager_Standard::~ComponentModule_NvMemoryManager_Standard(){}

bool ComponentModule_NvMemoryManager_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}

bool ComponentModule_NvMemoryManager_Standard::ReadPersistentItem(bool * b, const PersistentDataAlias aliasIndex)
{
	return _imp->ReadPersistentItem(b, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::ReadPersistentItem(int * i, const PersistentDataAlias aliasIndex)
{
	return _imp->ReadPersistentItem(i, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::ReadPersistentItem(TimeSignature * ts, const PersistentDataAlias aliasIndex)
{
	return _imp->ReadPersistentItem(ts, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::ReadPersistentItem(SystemSKU * sku, const PersistentDataAlias aliasIndex)
{
	return _imp->ReadPersistentItem(sku, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::ReadPersistentItem(PowerRelayStateData * stateData, const PersistentDataAlias alias)
{
	return _imp->ReadPersistentItem(stateData, alias);
}

bool ComponentModule_NvMemoryManager_Standard::ReadPersistentItem(ScheduledTaskDetail taskDetailCollection[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias aliasIndex)
{
	return _imp->ReadPersistentItem(taskDetailCollection, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::WritePersistentItem(const bool * b, const PersistentDataAlias aliasIndex)
{
	return _imp->WritePersistentItem(b, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::WritePersistentItem(const int * i, const PersistentDataAlias aliasIndex)
{
	return _imp->WritePersistentItem(i, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::WritePersistentItem(const TimeSignature * ts, const PersistentDataAlias aliasIndex)
{
	return _imp->WritePersistentItem(ts, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::WritePersistentItem(const SystemSKU * sku, const PersistentDataAlias aliasIndex)
{
	return _imp->WritePersistentItem(sku, aliasIndex);
}

bool ComponentModule_NvMemoryManager_Standard::WritePersistentItem(const PowerRelayStateData * stateData, const PersistentDataAlias alias)
{
	return _imp->WritePersistentItem(stateData, alias);
}

bool ComponentModule_NvMemoryManager_Standard::WritePersistentItem(const ScheduledTaskDetail taskDetailCollection[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias aliasIndex)
{
	return _imp->WritePersistentItem(taskDetailCollection, aliasIndex);
}


