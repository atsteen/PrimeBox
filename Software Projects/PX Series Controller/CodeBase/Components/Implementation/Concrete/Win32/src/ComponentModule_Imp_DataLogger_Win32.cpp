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

#include "..\include\ComponentModule_Imp_DataLogger_Win32.h"

#if defined(TARGET_PLAT_WIN32)

#include <time.h>

ComponentModule_Imp_DataLogger_Win32::ComponentModule_Imp_DataLogger_Win32() {}

ComponentModule_Imp_DataLogger_Win32::~ComponentModule_Imp_DataLogger_Win32() {}

bool ComponentModule_Imp_DataLogger_Win32::DoSelfDiagnostic_Imp()
{
	return true;
}

void ComponentModule_Imp_DataLogger_Win32::LogMessage(const char * logText, const bool prependTimeSignature, const bool terminateWithNewline)
{
	// No need to support batch log writing in Win32 environment
	LogMessageImmediate(logText, prependTimeSignature, terminateWithNewline);
}

void ComponentModule_Imp_DataLogger_Win32::LogMessageImmediate(const char * logText, const bool prependTimeSignature, const bool terminateWithNewline)
{
	struct tm _now;
	struct tm _lastLogTime = {};
	time_t _time;
	std::ofstream _ofile;

	time(&_time);
	localtime_s(&_now, &_time);
	//_now = localtime(&_time);

	ostringstream os_logDir, os_FilePath, os_TimeStamp;

	int year = _now.tm_year + 1900;
	int month = _now.tm_mon + 1;
	int day = _now.tm_mday;
	int hour = _now.tm_hour;
	int minute = _now.tm_min;
	int second = _now.tm_sec;

	if (_lastLogTime.tm_mday != day)
	{
		os_logDir << "PX4_Logs\\" << year << "\\"; // 
		_lastLogTime = _now;
	}

	os_FilePath << os_logDir.str() << month << "_" << day << ".csv";

	_ofile.open(os_FilePath.str(), ios::out | ios::app);
	if (_ofile.is_open())
	{
		os_TimeStamp << "[" << hour << ":" << minute << ":" << second << "],";

		if (prependTimeSignature) { _ofile << os_TimeStamp.str(); }
		_ofile << logText;
		if (terminateWithNewline) { _ofile << "\n"; }
	}

	_ofile.close();
}

#endif