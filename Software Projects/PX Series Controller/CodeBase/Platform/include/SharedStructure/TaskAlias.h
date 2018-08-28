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

enum TaskAlias {
	TASKALIAS_NOT_SET,
	TASKALIAS_NAVIGATION_MENU_SELECT,
	TASKALIAS_NAVIGATION_MENU_MOVE_LEFT,
	TASKALIAS_NAVIGATION_MENU_MOVE_RIGHT,
	TASKALIAS_ENABLE_POWER_RELAY,
	TASKALIAS_DISABLE_POWER_RELAY,
	TASKALIAS_TOGGLE_OVERRIDE_POWER,
	TASKALIAS_ENABLE_DISPLAY,
	TASKALIAS_DISABLE_DISPLAY,
	TASKALIAS_REFRESH_STATE_SYSTEM_ALARMS,
	TASKALIAS_REFRESH_STATE_CIRCULATION_FANS,
	TASKALIAS_REFRESH_STATE_EXHAUST_FANS,
	TASKALIAS_REFRESH_STATE_LIGHT
};