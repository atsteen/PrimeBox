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

#include "..\include\ComponentModule_Imp_DataLogger_ATMega.h"

#if defined(TARGET_PLAT_AVR)

#define SD_SS_Pin 53

ComponentModule_Imp_DataLogger_ATMega::ComponentModule_Imp_DataLogger_ATMega()
{
	if(_rtc.begin() && SD.begin(SD_SS_Pin)){ _isAvailable = true; }
}

ComponentModule_Imp_DataLogger_ATMega::~ComponentModule_Imp_DataLogger_ATMega() {}

bool ComponentModule_Imp_DataLogger_ATMega::DoSelfDiagnostic_Imp()
{
	if(_rtc.begin() && SD.begin(SD_SS_Pin)){ return true; }
	else{ return false; }
}

void ComponentModule_Imp_DataLogger_ATMega::LogMessage(const char * logText, const bool prependTimeSignature, const bool terminateWithNewline)
{
	//Implement batch log write after reducing memory footprint
	LogMessageImmediate(logText);
}

void ComponentModule_Imp_DataLogger_ATMega::LogMessageImmediate(const char * logText, const bool prependTimeSignature, const bool terminateWithNewline)
{
	DateTime dt = _rtc.now();
	const TimeSignature ts = { dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second() };
	char * timeText = "[hh:mm:ss],";
	ts.TimeText_hh(timeText, 1);
	ts.TimeText_mm(timeText, 4);
	ts.TimeText_ss(timeText, 7);

	if(_isAvailable)
	{
		// if the path dir does not exist, create it here	
		ts.TimeText_YYYY(_logsDir, 9);
		if(!SD.exists(_logsDir)){ SD.mkdir(_logsDir); }	

		if (_lastLogTs.day() != ts.day())
		{
			ts.TimeText_YYYY(_fileName, 9);
			ts.TimeText_MM(_fileName, 14);
			ts.TimeText_DD(_fileName, 17);

			_lastLogTs = ts;
		}

		_logFile = SD.open(_fileName, FILE_WRITE);
		if (prependTimeSignature) { _logFile.print(timeText); }
		_logFile.print(logText);
		if (terminateWithNewline){ _logFile.println(); }
		
		_logFile.close();
	}
	
	#if defined(ENABLE_VERBOSE_LOGGING)
	if (prependTimeSignature) { Serial.print(timeText); }
	Serial.print(logText);
	if (terminateWithNewline){ Serial.println(); }
	#endif
}

#endif