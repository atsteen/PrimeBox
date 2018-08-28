#pragma once
#include "..\T_DataItemList.h"
#include "..\TimeSignature.h"
#include "..\SystemSKU.h"
#include "..\PowerRelayStateData.h"
#include "..\ScheduledTaskDetail.h"

class PersistentData_PX4
{
public:
	PersistentData_PX4();

	int GetAddress(const bool, const PersistentDataAlias);
	int GetAddress(const int, const PersistentDataAlias);
	int GetAddress(const TimeSignature, const PersistentDataAlias);
	int GetAddress(const SystemSKU, const PersistentDataAlias);
	int GetAddress(const PowerRelayStateData, const PersistentDataAlias);
	int GetAddress(const ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias);

private:
	T_DataItemList<bool> boolItemList;
	T_DataItemList<int> intItemList;
	T_DataItemList<TimeSignature> TimeSignatureItemList;
	T_DataItemList<SystemSKU> SystemSkuItemList;
	T_DataItemList<PowerRelayStateData> relayStateItemList;
	T_DataItemList<const ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT]> STPoolItemList;

	int _NvMemoryAddressStartIndex = 0;
};

inline PersistentData_PX4::PersistentData_PX4()
{
	//todo... bug when itemLists change... existing addersses wont align and new entries will be created on top of old entries
	// suggest init on sku, wipe NVmem table if sku's dont match 
	int nextItemAddress = _NvMemoryAddressStartIndex;

	//Env settings persistent data init
	nextItemAddress += boolItemList.PushItem(PersistentDataAlias::LIGHTS_STATE_AUTO_CYCLE, nextItemAddress);
	nextItemAddress += boolItemList.PushItem(PersistentDataAlias::ALARM_LOGFULL_STATE, nextItemAddress);

	nextItemAddress += intItemList.PushItem(PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DAY, nextItemAddress);
	nextItemAddress += intItemList.PushItem(PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_NIGHT, nextItemAddress);
	nextItemAddress += intItemList.PushItem(PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DURATION, nextItemAddress);
	nextItemAddress += boolItemList.PushItem(PersistentDataAlias::EXHAUST_FANS_STATE_AUTO_CYCLE, nextItemAddress);

	nextItemAddress += intItemList.PushItem(PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DAY, nextItemAddress);
	nextItemAddress += intItemList.PushItem(PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_NIGHT, nextItemAddress);
	nextItemAddress += intItemList.PushItem(PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DURATION, nextItemAddress);
	nextItemAddress += boolItemList.PushItem(PersistentDataAlias::CIRCULATION_FANS_STATE_AUTO_CYCLE, nextItemAddress);
	
	nextItemAddress += intItemList.PushItem(PersistentDataAlias::ALARM_THRESHOLD_OVER_TEMP, nextItemAddress);
	nextItemAddress += intItemList.PushItem(PersistentDataAlias::ALARM_THRESHOLD_OVER_RH, nextItemAddress);

	nextItemAddress += TimeSignatureItemList.PushItem(PersistentDataAlias::LIGHTS_STATE_AUTO_SUNRISE, nextItemAddress);
	nextItemAddress += TimeSignatureItemList.PushItem(PersistentDataAlias::LIGHTS_STATE_AUTO_SUNSET, nextItemAddress);

	//Task settings data alias
	nextItemAddress += STPoolItemList.PushItem(PersistentDataAlias::SCHEDULED_TASK_POOL, nextItemAddress);

	//Power Relay Settings
	nextItemAddress += relayStateItemList.PushItem(PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_A, nextItemAddress);
	nextItemAddress += relayStateItemList.PushItem(PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_B, nextItemAddress);
	nextItemAddress += relayStateItemList.PushItem(PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_C, nextItemAddress);
	nextItemAddress += relayStateItemList.PushItem(PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_D, nextItemAddress);

	//System settings data alias
	nextItemAddress += SystemSkuItemList.PushItem(PersistentDataAlias::SYSTEM_SKU, nextItemAddress);
}

inline int PersistentData_PX4::GetAddress(const bool item, const PersistentDataAlias alias)
{
	DataItemListNode<bool> * nextItem = boolItemList.GetTop();

	while (nextItem)
	{
		if (nextItem->dataAlias == alias)
		{
			return nextItem->address;
		}

		nextItem = nextItem->nextItem;
	}

	return -1;
}

inline int PersistentData_PX4::GetAddress(const int item, const PersistentDataAlias alias)
{
	DataItemListNode<int> * nextItem = intItemList.GetTop();

	while (nextItem)
	{
		if (nextItem->dataAlias == alias)
		{
			return nextItem->address;
		}

		nextItem = nextItem->nextItem;
	}

	return -1;
}

inline int PersistentData_PX4::GetAddress(const TimeSignature item, const PersistentDataAlias alias)
{
	DataItemListNode<TimeSignature> * nextItem = TimeSignatureItemList.GetTop();

	while (nextItem)
	{
		if (nextItem->dataAlias == alias)
		{
			return nextItem->address;
		}

		nextItem = nextItem->nextItem;
	}

	return -1;
}

inline int PersistentData_PX4::GetAddress(const SystemSKU item, const PersistentDataAlias alias)
{
	DataItemListNode<SystemSKU> * nextItem = SystemSkuItemList.GetTop();

	while (nextItem)
	{
		if (nextItem->dataAlias == alias)
		{
			return nextItem->address;
		}

		nextItem = nextItem->nextItem;
	}

	return -1;
}


inline int PersistentData_PX4::GetAddress(const PowerRelayStateData item, const PersistentDataAlias alias)
{
	DataItemListNode<PowerRelayStateData> * nextItem = relayStateItemList.GetTop();

	while (nextItem)
	{
		if (nextItem->dataAlias == alias)
		{
			return nextItem->address;
		}

		nextItem = nextItem->nextItem;
	}

	return -1;
}

inline int PersistentData_PX4::GetAddress(const ScheduledTaskDetail taskDetailCollection[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias alias)
{
	DataItemListNode<const ScheduledTaskDetail[SCHEDULED_TASK_DETAIL_COUNT]> * nextItem = STPoolItemList.GetTop();

	while (nextItem)
	{
		if (nextItem->dataAlias == alias)
		{
			return nextItem->address;
		}

		nextItem = nextItem->nextItem;
	}

	return -1;
}
