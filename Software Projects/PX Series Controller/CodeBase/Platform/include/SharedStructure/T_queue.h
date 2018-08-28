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

//todo... FOR THE LOVE OF GOD, TYPEDEF THIS SHIT PLEASE

template <class T>
class T_queue
{
public:
	T_queue() {};
	~T_queue() {};

	bool Enqueue(T newItem);
	const T * EnqueueTop(T newItem);
	const T * EnqueueAfter(T newItem, const T *afterItem);
	T Dequeue();

private:
	T _items[T_QUEUE_SIZE] = {};
	int _itemCount = 0;
};

template<class T> bool T_queue<T>::Enqueue(T newItem)
{
	if (_itemCount >= T_QUEUE_SIZE) { return false; }
	_items[_itemCount] = newItem;
	++_itemCount;
	return true;
}

template<class T> const T * T_queue<T>::EnqueueTop(T newItem)
{
	if (_itemCount >= T_QUEUE_SIZE) { return nullptr; }

	for (int i = _itemCount; i > 0; --i)
	{
		_items[i] = _items[i - 1];
	}

	_items[0] = newItem;
	++_itemCount;
	return &_items[0];
}

template<class T> const T * T_queue<T>::EnqueueAfter(T newItem, const T *afterItem)
{
	if (_itemCount >= T_QUEUE_SIZE) { return nullptr; }

	for (int i = 0; i < _itemCount; i++)
	{
		if (&_items[i] == afterItem)
		{
			++i;
			for (int j = _itemCount; j > i; --j)
			{
				_items[j] = _items[j - 1];
			}
		}

		_items[i] = newItem;
		++_itemCount;
		return &_items[i];
	}

	return nullptr;
}

template<class T> T T_queue<T>::Dequeue()
{
	int itemIndex = 0;
	if (!_items[itemIndex]) { return nullptr; }
	T temp = _items[itemIndex];

	while (_items[itemIndex+1]) //todo... deal with full item array shift (will miss last element shift if full)
	{
		_items[itemIndex] = _items[itemIndex + 1];
		++itemIndex;
	}

	_items[itemIndex] = nullptr;
	--_itemCount;
	return temp;
}
