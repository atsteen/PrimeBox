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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_SelectArrowDownRow.h"

Viewstate_Element_Text_SelectArrowDownRow::Viewstate_Element_Text_SelectArrowDownRow(const int start_index, const int imbricationLevel) : Viewstate_Element_Text(start_index, imbricationLevel){}
Viewstate_Element_Text_SelectArrowDownRow::~Viewstate_Element_Text_SelectArrowDownRow(){}

int Viewstate_Element_Text_SelectArrowDownRow::emplace(char * target, const int targetlen)
{
		char arrowStr[21];
		
		for(int i = 0; i < _arrowCount; ++i)
		{
			arrowStr[i] = Viewstate_String_Generator::selectArrowDownSymbol[0];
		}

		arrowStr[_arrowCount] = '\0';
		return _emplace(target, targetlen, arrowStr);
}

int Viewstate_Element_Text_SelectArrowDownRow::emplaceAbove(char * target, const int targetlen, Viewstate_Element_Text *et)
{
	_arrowCount = et->emplace(target, targetlen);
	_startIndex = et->_startIndex - 21;

	if(_startIndex < 0){ return 0; }
	else{ return emplace(target, targetlen); }	
}

int Viewstate_Element_Text_SelectArrowDownRow::emplaceOver(char * target, const int targetlen, Viewstate_Element_Text * et)
{
	_arrowCount = et->emplace(target, targetlen);
	_startIndex = et->_startIndex;
	return emplace(target, targetlen);
}

int Viewstate_Element_Text_SelectArrowDownRow::emplaceAround(char * target, const int targetlen, Viewstate_Element_Text *et)
{	
	_arrowCount = 1;
	_startIndex = et->_startIndex-1;
	emplace(target, targetlen); //emplace left arrow
	int firstStartIndex = _startIndex;
	_startIndex = _startIndex + et->emplace(target, targetlen) + 1;
	emplace(target, targetlen); //emplace right arrow
	return _startIndex - firstStartIndex;
}
