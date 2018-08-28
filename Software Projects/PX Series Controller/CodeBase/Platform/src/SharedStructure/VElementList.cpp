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

#include "..\..\include\SharedStructure\VElementList.h"

VElementList::VElementList(){}
VElementList::~VElementList(){}

void VElementList::AddElement(Viewstate_Element_Text *newElement)
{
	if (!_top) { _top = newElement; }
	else
	{
		Viewstate_Element_Text *currNode(_top);

		if (newElement->imbricationLevel < _top->imbricationLevel)
		{
			newElement->nextElement = _top;
			_top = newElement;
		}
		else
		{
			while (currNode->nextElement && (newElement->imbricationLevel >= currNode->nextElement->imbricationLevel))
			{
				currNode = currNode->nextElement;
			}

			newElement->nextElement = currNode->nextElement;
			currNode->nextElement = newElement;
		}		
	}
}

Viewstate_Element_Text * VElementList::GetTop()
{
	return _top;
}
