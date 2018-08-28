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
#include "..\..\Components\Abstraction\IComponentModule.h"
#include "..\..\Components\Implementation\ComponentModule_Imp_DataLogger.h"
#include "..\..\Platform\include\Viewstate_String_Generator\Viewstate_String_Generator.h"
#include "..\..\Platform\include\SharedStructure\TimeSignature.h"

class ComponentModule_DataLogger :
	public IComponentModule
{
public:
	ComponentModule_DataLogger(ComponentModule_Imp_DataLogger *imp) : _imp(imp) {}
	virtual ~ComponentModule_DataLogger() override { delete _imp; }

	virtual void LogSystemEvent(const ViewstateStringAlias) = 0;
	virtual void LogMessage(const char *) = 0;

protected:
	ComponentModule_Imp_DataLogger *_imp;
};