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
#include "..\SystemSKU.h"
#include "..\..\Viewstate_String_Generator\Viewstate_String_Generator.h"

class IModelSystemData
{
public:
	IModelSystemData() {};
	virtual ~IModelSystemData();

	virtual void SetControllerRestartSignal(bool) = 0;
	virtual const bool GetControllerRestartSignal() = 0;
	virtual SystemSKU const* GetSystemSKU() = 0;
	virtual const bool * const GetLogAlarmDefaultState() = 0;
	virtual void SetLogAlarmDefaultState(const bool * const state) = 0;
	virtual const ViewstateStringAlias GetSystemMode() = 0;
	virtual const char * GetCurrentTimeText() = 0;
};

inline IModelSystemData::~IModelSystemData() {}