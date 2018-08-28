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
#include "..\..\..\Configurations\PX4_Config.h"
#include "..\SharedStructure\PersistentDataAlias.h"

template <class T>
struct DataItemListNode
{
	//T value;
	int address = 0;
	PersistentDataAlias dataAlias = PersistentDataAlias::NOT_SET;
	DataItemListNode * nextItem = nullptr;
};

template <class T>
class T_DataItemList
{
public:
	T_DataItemList() {};
	~T_DataItemList();

	unsigned int PushItem(PersistentDataAlias dAlias, const int addy);
	DataItemListNode<T> * GetTop() { return _top; }

private:
	DataItemListNode<T> * _top = nullptr;
	int _itemCount = 0;
};

template <class T>
unsigned int T_DataItemList<T>::PushItem(PersistentDataAlias dAlias, const int addy)
{
	if (_itemCount >= T_LIST_MAXSIZE) { return 0; }
	DataItemListNode<T> * newNode =  new DataItemListNode<T>;
	newNode->address = addy;
	newNode->dataAlias = dAlias;

	if (_top) { newNode->nextItem = _top; }
	_top = newNode;

	return sizeof(T);
}

template <class T>
inline T_DataItemList<T>::~T_DataItemList()
{
	DataItemListNode<T> * next = _top;
	while (next)
	{
		DataItemListNode<T> * old = next;
		next = next->nextItem;
		delete old;
		--_itemCount;
	}

	_top = nullptr;
}
