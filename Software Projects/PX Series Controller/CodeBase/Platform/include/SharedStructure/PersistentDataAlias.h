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

enum class PersistentDataAlias {
	NOT_SET,

	//Env settings data alias
	LIGHTS_STATE_AUTO_CYCLE, //bool
	ALARM_LOGFULL_STATE, //bool

	EXHAUST_FANS_STATE_DUTY_CYCLE_DAY, //int
	EXHAUST_FANS_STATE_DUTY_CYCLE_NIGHT, //int
	EXHAUST_FANS_STATE_DUTY_CYCLE_DURATION, //int
	EXHAUST_FANS_STATE_AUTO_CYCLE, //bool

	CIRCULATION_FANS_STATE_DUTY_CYCLE_DAY, //int
	CIRCULATION_FANS_STATE_DUTY_CYCLE_NIGHT, //int
	CIRCULATION_FANS_STATE_DUTY_CYCLE_DURATION, //int
	CIRCULATION_FANS_STATE_AUTO_CYCLE, //bool

	ALARM_THRESHOLD_OVER_TEMP, //int
	ALARM_THRESHOLD_OVER_RH, //int

	LIGHTS_STATE_AUTO_SUNRISE, //TimeSignature
	LIGHTS_STATE_AUTO_SUNSET, //TimeSignature

	//Task settings data alias
	SCHEDULED_TASK_POOL, //ScheduledTaskDetailPool 

	//System settings data alias
	SYSTEM_SKU, // System SKU

	//PowerRelay items
	POWER_RELAY_STATE_CHANNEL_A,
	POWER_RELAY_STATE_CHANNEL_B,
	POWER_RELAY_STATE_CHANNEL_C,
	POWER_RELAY_STATE_CHANNEL_D,
	POWER_RELAY_STATE_CHANNEL_E,
	POWER_RELAY_STATE_CHANNEL_F,
	POWER_RELAY_STATE_CHANNEL_G,
	POWER_RELAY_STATE_CHANNEL_H
};

enum class PersistentComponentAlias{
	NOT_SET,
	POWER_RELAY_ARRAY,
	POWER_RELAY_CHANNEL_A,
	POWER_RELAY_CHANNEL_B,
	POWER_RELAY_CHANNEL_C,
	POWER_RELAY_CHANNEL_D,
	POWER_RELAY_CHANNEL_E,
	POWER_RELAY_CHANNEL_F,
	POWER_RELAY_CHANNEL_G,
	POWER_RELAY_CHANNEL_H,
	DATA_MODEL_SYSTEM,
	DATA_MODEL_ENVIRONMENT,
	DATA_MODEL_TASK
};