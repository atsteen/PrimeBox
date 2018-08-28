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

#include "..\..\include\SharedStructure\TimeSignature.h"

 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
 const uint8_t daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

TimeSignature::TimeSignature (uint32_t t) {
	t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

	ss = t % 60;
	t /= 60;
	mm = t % 60;
	t /= 60;
	hh = t % 24;
	uint16_t days = t / 24;
	uint8_t leap;
	for (yOff = 0; ; ++yOff) {
		leap = yOff % 4 == 0;
		if (days < 365 + leap)
		break;
		days -= 365 + leap;
	}
	for (m = 1; ; ++m) {
		uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
		if (leap && m == 2)
		++daysPerMonth;
		if (days < daysPerMonth)
		break;
		days -= daysPerMonth;
	}
	d = days + 1;
}

TimeSignature::TimeSignature (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
	SetSignature(year, month, day, hour, min, sec);
}

TimeSignature::TimeSignature (const TimeSignature& copy):
	yOff(copy.yOff),
	m(copy.m),
	d(copy.d),
	hh(copy.hh),
	mm(copy.mm),
	ss(copy.ss)
{}

// number of days since 2000/01/01, valid for 2001..2099
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
	if (y >= 2000)
	y -= 2000;
	uint16_t days = d;
	for (uint8_t i = 1; i < m; ++i)
	days += pgm_read_byte(daysInMonth + i - 1);
	if (m > 2 && y % 4 == 0)
	++days;
	return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
	return ((days * 24L + h) * 60 + m) * 60 + s;
}

uint32_t TimeSignature::unixtime(void) const {
	uint32_t t;
	uint16_t days = date2days(yOff, m, d);
	t = time2long(days, hh, mm, ss);
	t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

	return t;
}

long TimeSignature::secondsInDay() const
{
	return (hh*3600L + mm*60 + ss);
}

void TimeSignature::TimeText_YYYY(char * timeStr, uint8_t offset) const
{
	char buff[5];
	itoa(year(), buff, 10);
	timeStr[0 + offset] = buff[0];
	timeStr[1 + offset] = buff[1];
	timeStr[2 + offset] = buff[2];
	timeStr[3 + offset] = buff[3];
}

void TimeSignature::TimeText_MM(char * timeStr, uint8_t offset) const
{
	char buff[3];
	itoa(m, buff, 10);
	if (m < 10)
	{
		timeStr[0 + offset] = '0';
		timeStr[1 + offset] = buff[0];
	}
	else {
		timeStr[0 + offset] = buff[0];
		timeStr[1 + offset] = buff[1];
	}
}

void TimeSignature::TimeText_DD(char * timeStr, uint8_t offset) const
{
	char buff[3];
	itoa(d, buff, 10);
	if (d < 10)
	{
		timeStr[0 + offset] = '0';
		timeStr[1 + offset] = buff[0];
	}
	else {
		timeStr[0 + offset] = buff[0];
		timeStr[1+ offset] = buff[1];
	}
}

void TimeSignature::TimeText_hh(char * timeStr, uint8_t offset) const
{
	char buff[3];
	itoa(hh, buff, 10);
	if (hh < 10)
	{
		timeStr[0 + offset] = '0';
		timeStr[1 + offset] = buff[0];
	}
	else {
		timeStr[0 + offset] = buff[0];
		timeStr[1 + offset] = buff[1];
	}
}

void TimeSignature::TimeText_mm(char * timeStr, uint8_t offset) const
{
	char buff[3];
	itoa(mm, buff, 10);
	if (mm < 10)
	{
		timeStr[0 + offset] = '0';
		timeStr[1 + offset] = buff[0];
	}
	else {
		timeStr[0 + offset] = buff[0];
		timeStr[1 + offset] = buff[1];
	}
}

void TimeSignature::TimeText_ss(char * timeStr, uint8_t offset) const
{
	char buff[3];
	itoa(ss, buff, 10);

	if (ss < 10)
	{
		timeStr[0 + offset] = '0';
		timeStr[1 + offset] = buff[0];
	}
	else {
		timeStr[0 + offset] = buff[0];
		timeStr[1 + offset] = buff[1];
	}
}

void TimeSignature::TimeText_hhmm(char * timeStr, uint8_t offset) const
{
	TimeText_hh(timeStr, offset);
	timeStr[2 + offset] = ':';
	TimeText_mm(timeStr, 3 + offset);
	timeStr[5 + offset] = '\0';
}

void TimeSignature::TimeText_hhmm_Bracketed(char timeStr[8]) const
{
	TimeText_hhmm(timeStr);
	memmove(timeStr + 1, timeStr, 5);
	timeStr[0] = '[';
	strncat(timeStr, "]\0", 2);
}

long TimeSignature::secondstime(void) const {
	long t;
	uint16_t days = date2days(yOff, m, d);
	t = time2long(days, hh, mm, ss);
	return t;
}

uint8_t TimeSignature::dayOfTheWeek() const {
	uint16_t day = date2days(yOff, m, d);
	return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

TimeSignature TimeSignature::operator+(const TimeSignature_TimeSpan& span) {
	return TimeSignature(unixtime()+span.totalseconds());
}

TimeSignature TimeSignature::operator-(const TimeSignature_TimeSpan& span) {
	return TimeSignature(unixtime()-span.totalseconds());
}

TimeSignature_TimeSpan TimeSignature::operator-(const TimeSignature& right) {
	return TimeSignature_TimeSpan(unixtime()-right.unixtime());
}

void TimeSignature::SetSignature(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
{
	if (year >= 2000)
		year -= 2000;
	yOff = year;
	m = month;
	d = day;
	hh = hour;
	mm = min;
	ss = sec;
}

void TimeSignature::SetSignature(const TimeSignature * const newTime)
{
	yOff = newTime->year();
	m = newTime->month();
	d = newTime->day();
	hh = newTime->hour();
	mm = newTime->minute();
	ss = newTime->second();
}

void TimeSignature::AdjustHH(int HH)
{
	int adjustH = (hh + HH) % 24;
	if(adjustH >= 0){ hh = adjustH; }
	else {hh = 24 + adjustH;}
}

void TimeSignature::AdjustMM(int MM)
{
	int adjustM = (mm + MM) % 60;
	if (adjustM >= 0) { mm = adjustM; }
	else { mm = 60 + adjustM; }
}

TimeSignature_TimeSpan::TimeSignature_TimeSpan (int32_t seconds):
_seconds(seconds)
{}

TimeSignature_TimeSpan::TimeSignature_TimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds):
_seconds((int32_t)days*86400L + (int32_t)hours*3600 + (int32_t)minutes*60 + seconds)
{}

TimeSignature_TimeSpan::TimeSignature_TimeSpan (const TimeSignature_TimeSpan& copy):
_seconds(copy._seconds)
{}

TimeSignature_TimeSpan TimeSignature_TimeSpan::operator+(const TimeSignature_TimeSpan& right) {
	return TimeSignature_TimeSpan(_seconds+right._seconds);
}

TimeSignature_TimeSpan TimeSignature_TimeSpan::operator-(const TimeSignature_TimeSpan& right) {
	return TimeSignature_TimeSpan(_seconds-right._seconds);
}