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

#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IRtcLogger.h"
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4.h"
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4_Win32.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_RTC_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_DataLogger_Standard.h"

class ComponentPackage_RtcLogger : public IRtcLogger
{
public:
	ComponentPackage_RtcLogger(ComponentModuleImp_Factory_PX4* componentImpFactory);
	~ComponentPackage_RtcLogger();

	// Inherited via IRtcLogger
	virtual const TimeSignature & CurrentTime() override;
	virtual const char * CurrentTimeAsText() override;
	virtual EventLog_Item_Collection * GetEventLogItems() override;	
	virtual void LogEvent(const ViewstateStringAlias) override;
	virtual void LogEvent(IViewstate_Element *) override;
	virtual void LogMessage(const char *) override;
	virtual void LogMessage(const ViewstateStringAlias textAlias) override;
	virtual void LogMessage(const ViewstateStringAlias textAlias, const bool value) override;
	virtual void LogMessage(const ViewstateStringAlias textAlias, const int value) override;
	virtual void LogMessage(const ViewstateStringAlias textAlias, const TimeSignature * value) override;
	

private:
	ComponentModule_RTC_Standard * _rtc;
	ComponentModule_DataLogger_Standard * _logger;
};