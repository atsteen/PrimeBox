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
#include "..\Implementation\ComponentModule_Imp.h"

class ComponentModule_Imp_DataLogger :
	public ComponentModule_Imp
{
public:
	ComponentModule_Imp_DataLogger(){}
	virtual ~ComponentModule_Imp_DataLogger() = 0;

	virtual void LogMessage(const char * logText, const bool prependTimeSignature = true, const bool terminateWithNewline = true) = 0;
	virtual void LogMessageImmediate(const char * logText, const bool prependTimeSignature = true, const bool terminateWithNewline = true) = 0;
};

inline ComponentModule_Imp_DataLogger::~ComponentModule_Imp_DataLogger() {}