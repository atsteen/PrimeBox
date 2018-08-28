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
#include "..\TimeSignature.h"

class IModelInterfaceData
{
public:
	IModelInterfaceData() {};
	virtual ~IModelInterfaceData();

	virtual const bool GetPromptInputModalState() = 0;
	virtual const TimeSignature * LastInputActionTime() = 0;
	virtual void RegisterUserInputAction(TimeSignature ts) = 0;
	virtual void SetPromptInputModalState(bool state) = 0;
};

inline IModelInterfaceData::~IModelInterfaceData() {}