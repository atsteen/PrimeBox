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

#include "..\include\componentmodule_imp_asciidisplay_hd44780_parallel_atmega.h"

#if defined(TARGET_PLAT_AVR)

#include <Wire.h>
#include <Arduino.h>
#include <string.h>
#include "..\..\..\..\..\Platform\include\Viewstate_String_Generator\Viewstate_String_Generator.h"

ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::ComponentModule_Imp_ASCIIDisplay_ATMega_Direct()
{
	_lcd = new LiquidCrystal(Rs_pin, En_pin, D4_pin, D5_pin, D6_pin, D7_pin);
	_lcd->begin(20, 4);
	pinMode(BACKLIGHT_PIN, OUTPUT);
	analogWrite(BACKLIGHT_PIN, 255);

	//Add special characters
	byte AirTempSymbol[8] = {
		B00010,
		B00101,
		B00111,
		B00101,
		B00000,
		B00111,
		B00010,
		B00010
	};
	_lcd->createChar(0, AirTempSymbol);

	byte ReletiveHumiditySymbol[8] = {
		B00110,
		B00101,
		B00110,
		B00101,
		B00000,
		B00101,
		B00111,
		B00101
	};
	_lcd->createChar(1, ReletiveHumiditySymbol);

	byte WaterTempSymbol[8] = {
		B10001,
		B10001,
		B10101,
		B01010,
		B00000,
		B01110,
		B00100,
		B00100
	};
	_lcd->createChar(2, WaterTempSymbol);

	byte SysModeSymbol[8] = {
		B11111,
		B00000,
		B10001,
		B11011,
		B10101,
		B10001,
		B00000,
		B11111
	};
	_lcd->createChar(3, SysModeSymbol);

	byte SelectArrowRight[8] = {
		B10000,
		B01000,
		B10100,
		B11010,
		B11101,
		B11010,
		B10100,
		B01000
	};
	_lcd->createChar(4, SelectArrowRight);

	byte SelectArrowDown[8] = {
		B11111,
		B11111,
		B11011,
		B11011,
		B11011,
		B01010,
		B10001,
		B11011
	};
	_lcd->createChar(5, SelectArrowDown);

	byte BackSymbol[8] = {
		B00000,
		B00100,
		B01100,
		B11111,
		B11111,
		B01100,
		B00100,
		B00000
	};
	_lcd->createChar(6, BackSymbol);

	byte SelectBackSymbol[8] = {
		B11111,
		B11011,
		B10011,
		B00000,
		B00000,
		B10011,
		B11011,
		B11111
	};
	_lcd->createChar(7, SelectBackSymbol);
}

ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::~ComponentModule_Imp_ASCIIDisplay_ATMega_Direct()
{
	delete &_lcd;
}

bool ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::DoSelfDiagnostic_Imp()
{
	_lcd->clear();
	_lcd->home();
	_lcd->print("Display Self Test");
	return true;
}

void ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::Enable_Imp()
{
	analogWrite(BACKLIGHT_PIN, 255);
}

void ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::Disable_Imp()
{
	analogWrite(BACKLIGHT_PIN, 0);
}

void ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::UpdateDisplay_Imp(const char* str_sptr)
{
	_lcd->clear();
	_lcd->home();

	if(!_specialChars)
	{
		 _lcd->setCursor(0,0);
		 _lcd->print(str_sptr);
		 return;
	}

	char inChar[strlen(str_sptr)+1];
	strcpy(inChar,str_sptr);
	char * pch;
	pch = strtok(inChar, "\n");
	int rowCount = 0;

	while (pch != NULL)
	{
		_lcd->setCursor(0,rowCount);
		_lcd->print(pch);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::airTemperatureSymbol, 0);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::relativeHumiditySymbol, 1);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::waterTemperatureSymbol, 2);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::systemModeSymbol, 3);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::selectArrowRightSymbol, 4);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::selectArrowDownSymbol, 5);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::backSymbol, 6);
		_processSymbol(rowCount, pch, Viewstate_String_Generator::selectBackSymbol, 7);
		pch = strtok (NULL, "\n");
		++rowCount;
	}
}

void ComponentModule_Imp_ASCIIDisplay_ATMega_Direct::_processSymbol(const int rowNum, char * line, const char* searchChar, int replacementCharIndex)
{
    if(!strrchr(line,(int)searchChar[0])){return;}

	for(int i = 0; i < strlen(line); i++)
	{
		if(line[i] == searchChar[0])
		{
			_lcd->setCursor(i,rowNum);
			_lcd->write((uint8_t)replacementCharIndex);
		}
	}
}

#endif
