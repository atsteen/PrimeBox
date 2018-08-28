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

#include "..\..\include\ComponentModule_Imp\ComponentModule_Imp_NvMemoryManager_ATMega.h"

#if defined(TARGET_PLAT_AVR)

#include <arduino.h>
#include <EEPROMex.h>

ComponentModule_Imp_NvMemoryManager_ATMega::ComponentModule_Imp_NvMemoryManager_ATMega(){}

ComponentModule_Imp_NvMemoryManager_ATMega::~ComponentModule_Imp_NvMemoryManager_ATMega(){}

bool ComponentModule_Imp_NvMemoryManager_ATMega::DoSelfDiagnostic_Imp()
{
	return false;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::ReadPersistentItem(bool * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	//Serial.print(F("Reading bool item from EEPROM address "));
	//Serial.println(address);

	*dataItem = EEPROM.readByte(address);
	//Serial.print(F("Assigned bit value of "));
	//Serial.println(*dataItem);

	return true;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::ReadPersistentItem(int * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	//Serial.print(F("Reading int item from EEPROM address "));
	//Serial.println(address);

	*dataItem = EEPROM.readInt(address);
	//Serial.print(F("Assigned int value of "));
	//Serial.println(*dataItem);

	return true;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::ReadPersistentItem(TimeSignature * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	TimeSignature savedTime(EEPROM.readLong(address));
	//Serial.print(F("Reading longTime ("));
	//Serial.print(EEPROM.readLong(address));
	//Serial.print(F(") raw long, ("));
	if(savedTime.secondstime() > 0)
	{
		*dataItem = savedTime;
		//Serial.print(dataItem->secondstime());
		//Serial.print(F(") secondsTime from EEPROM address "));
		//Serial.println(address);
		return true;
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::ReadPersistentItem(SystemSKU * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	EEPROM.readBlock(address, *dataItem);
	return false;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::ReadPersistentItem(ScheduledTaskDetailPool * dataItem, const PersistentDataAlias alias)
{	
	int address = _persistentDataMap.GetAddress(*dataItem, alias);

	//Serial.print(F("Reading ScheduledTaskDetailPool item from EEPROM address "));
	//Serial.println(address);

	dataItem->FreeAllScheduledTaskDetails(); //ensure all new details

	for(int i = 0; i < SCHEDULED_TASK_DETAIL_COUNT; ++i)
	{
		ScheduledTaskDetail * dataItemTaskDetail = dataItem->GetNewScheduledTaskDetail();
		if(dataItemTaskDetail)
		{
			sTaskDetail details;
			uint8_t offset = sizeof(*dataItemTaskDetail)*i;
			
			//Serial.print(F("Reading ScheduledTaskDetail from EEPROM address "));
			//Serial.println(address + offset);

			EEPROM.readBlock(address + offset, details);

			//if EEPROM values do not appear valid, move to next iteration
			if(details.taskAlias == 0){ continue; }

			//Serial.print(F("Assigning ScheduledTaskDetail ["));
			//Serial.print(i);
			//Serial.print(F("] from EEPROM address "));
			//Serial.print(address + offset);
			//Serial.print(F(", timeSig="));
			//Serial.print(details.triggerhh);
			//Serial.print(F(":"));
			//Serial.print(details.triggermm);
			//Serial.print(F(":"));
			//Serial.print(details.triggerss);
			//Serial.print(F(", alias="));
			//Serial.print(details.taskAlias);
			//Serial.print(F(", isEnabled="));
			//Serial.println(details.taskIsEnabled);

			dataItemTaskDetail->_scheduledExecutionTime.SetSignature(0, 0, 0, details.triggerhh, details.triggermm, details.triggerss);
			dataItemTaskDetail->_scheduledTaskAlias = details.taskAlias;
			dataItemTaskDetail->_isEnabaled = details.taskIsEnabled;
		}
		else
		{
			//Serial.println(F("ScheduledTaskDetailPool is full!"));
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::WritePersistentItem(const bool * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	//Serial.print(F("Writing bool item to EEPROM address "));
	//Serial.println(address);

	return EEPROM.updateByte(address, *dataItem);
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::WritePersistentItem(const int * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	//Serial.print(F("Writing int item to EEPROM address "));
	//Serial.println(address);

	return EEPROM.updateInt(address, *dataItem);

}

bool ComponentModule_Imp_NvMemoryManager_ATMega::WritePersistentItem(const TimeSignature * dataItem, const PersistentDataAlias alias)
{
	// Constructor for TimeSignature assumes today seconds... but secondstime() outputs 1970 seconds... account for diff
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	long _seconds = dataItem->unixtime();
	//Serial.print(F("Writing longTime ("));
	//Serial.print(_seconds);
	//Serial.print(F(") to EEPROM address "));
	//Serial.println(address);
	EEPROM.updateLong(address, _seconds);
	return true;
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::WritePersistentItem(const SystemSKU * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	//Serial.print(F("Writing sku: "));
	//Serial.print(dataItem->platform);
	//Serial.print(F("-"));
	//Serial.println(dataItem->model);
	//Serial.print(F("-"));
	//Serial.println(dataItem->version);
	return EEPROM.updateBlock(address, *dataItem);
}

bool ComponentModule_Imp_NvMemoryManager_ATMega::WritePersistentItem(const ScheduledTaskDetailPool * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	ScheduledTaskDetailPool pool = *dataItem;

	//Serial.print(F("Writing ScheduledTaskDetailPool item to EEPROM address "));
	//Serial.println(address);

	for(uint8_t i = 0; i < SCHEDULED_TASK_DETAIL_COUNT; ++i)
	{		
		const ScheduledTaskDetail dataItemTaskDetail = *pool.GetScheduledTaskDetail(i);
		uint8_t offset = sizeof(dataItemTaskDetail)*i;

		sTaskDetail details;
		details.triggerhh = dataItemTaskDetail._scheduledExecutionTime.hour();
		details.triggermm = dataItemTaskDetail._scheduledExecutionTime.minute();
		details.triggerss = dataItemTaskDetail._scheduledExecutionTime.second();
		details.taskAlias =	dataItemTaskDetail._scheduledTaskAlias;
		details.taskIsEnabled =	dataItemTaskDetail._isEnabaled;

		//Serial.print(F("Writing ScheduledTaskDetail ["));
		//Serial.print(i);		
		//Serial.print(F("] to EEPROM address "));
		//Serial.print(address + offset);
		//Serial.print(F(", triggerTime="));
		//Serial.print(details.triggerhh);
		//Serial.print(F(":"));
		//Serial.print(details.triggermm);
		//Serial.print(F(":"));
		//Serial.print(details.triggerss);
		//Serial.print(F(", alias="));
		//Serial.print(details.taskAlias);
		//Serial.print(F(", isEnabled="));
		//Serial.println(details.taskIsEnabled);

		EEPROM.updateBlock(address + offset, details);
	}

	return true;
}

#endif
