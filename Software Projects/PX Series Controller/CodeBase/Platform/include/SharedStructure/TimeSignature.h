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

// Code derrived from JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

// disable compiler warning (Visual Studio)
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#ifndef _TIMESIGNATURE_H_
#define _TIMESIGNATURE_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SECONDS_PER_DAY 86400L
#define SECONDS_FROM_1970_TO_2000 946684800

class TimeSignature_TimeSpan;

class TimeSignature
{
public:
    TimeSignature (uint32_t t =0);
	TimeSignature (uint16_t year, uint8_t month, uint8_t day, uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
    TimeSignature (const TimeSignature& copy);

    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    uint8_t dayOfTheWeek() const;

    // 32-bit times as seconds since 1/1/2000
    long secondstime() const;
    // 32-bit times as seconds since 1/1/1970
    uint32_t unixtime(void) const;
	// 32-bit time as seconds since midnight
	long secondsInDay() const;

	// Time display text
	void TimeText_YYYY(char *, uint8_t = 0) const;
	void TimeText_MM(char *, uint8_t = 0) const;
	void TimeText_DD(char *, uint8_t = 0) const;
	void TimeText_hh(char *, uint8_t = 0) const;
	void TimeText_mm(char *, uint8_t = 0) const;
	void TimeText_ss(char *, uint8_t = 0) const;

	void TimeText_hhmm(char *, uint8_t = 0) const;
	void TimeText_hhmm_Bracketed(char[8]) const;

    TimeSignature operator+(const TimeSignature_TimeSpan& span);
    TimeSignature operator-(const TimeSignature_TimeSpan& span);
    TimeSignature_TimeSpan operator-(const TimeSignature& right);

	void SetSignature(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
	void SetSignature(const TimeSignature * const);
	void AdjustHH(int HH);
	void AdjustMM(int MM);

protected:
    uint8_t yOff, m, d, hh, mm, ss;
};

class TimeSignature_TimeSpan
{
public:
	TimeSignature_TimeSpan (int32_t seconds = 0);
	TimeSignature_TimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds);
	TimeSignature_TimeSpan (const TimeSignature_TimeSpan& copy);
	int16_t days() const         { return _seconds / 86400L; }
	int8_t  hours() const        { return _seconds / 3600 % 24; }
	int8_t  minutes() const      { return _seconds / 60 % 60; }
	int8_t  seconds() const      { return _seconds % 60; }
	int32_t totalseconds() const { return _seconds; }

	TimeSignature_TimeSpan operator+(const TimeSignature_TimeSpan& right);
	TimeSignature_TimeSpan operator-(const TimeSignature_TimeSpan& right);

protected:
	int32_t _seconds;
};

#endif