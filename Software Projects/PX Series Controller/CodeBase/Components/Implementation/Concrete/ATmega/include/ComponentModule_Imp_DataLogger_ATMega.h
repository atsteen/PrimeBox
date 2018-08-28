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
#include "..\PreProcDirectives.h"
#include "..\ComponentModule_imp\ComponentModule_Imp_DataLogger.h"

#if defined(TARGET_PLAT_AVR)

#include "..\SharedStructure\TimeSignature.h"
#include "..\..\include\libraries\RTCLib\RTClib.h"
//#include <Wire.h>
#include <Arduino.h>
#include <SD.h>

class ComponentModule_Imp_DataLogger_ATMega :
	public ComponentModule_Imp_DataLogger
{
public:
	ComponentModule_Imp_DataLogger_ATMega();
	virtual ~ComponentModule_Imp_DataLogger_ATMega() override;

	// Inherited via ComponentModule_Imp
	virtual bool DoSelfDiagnostic_Imp() override;

	// Inherited via ComponentModule_Imp_DataLogger
	virtual void LogMessage(const char *, const bool = true, const bool = true) override;
	virtual void LogMessageImmediate(const char *, const bool = true, const bool = true) override;

protected:
	bool _isAvailable = false;
	TimeSignature _lastLogTs = { 0,0,0 };
	File _logFile;
	char * _fileName = "PX4_Logs/YYYY/MM_DD.csv";
	char * _logsDir = "PX4_Logs/YYYY/";
	RTC_DS3231 _rtc;
};

#endif