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

template <class T>
struct T_CircularListNode
{
	const T * const element;
	T_CircularListNode * next;
	T_CircularListNode * last;
	T_CircularListNode(T * e) : element(e), next(nullptr) {}
	~T_CircularListNode() { delete element; }
};

template <class T>
class T_CircularList
{
public:
	T_CircularList() : _cursor(nullptr) {} // constructor
	~T_CircularList() { while (!empty()) remove(); } // destructor
	bool empty() const { return _cursor == nullptr; } // is list empty?
	const T_CircularListNode<T> * front() const { return _cursor->next; } // element at cursor
	const T_CircularListNode<T> * back() const { return _cursor; } // element following cursor
	void advance() { _cursor = _cursor->next; } // advance cursor
	void pushFront(T& e); // add after cursor
	void addBack(T& e); // add after cursor
	void remove(); // remove node after cursor
private:
	T_CircularListNode<T> * _cursor; // the cursor
};

template <class T>
inline void T_CircularList<T>::pushFront(T& e)
{
	T_CircularListNode<T> * v = new T_CircularListNode<T>(&e);

	if (_cursor == nullptr)
	{
		v->next = v;
		v->last = v;
		_cursor = v;
	}
	else
	{
		v->next = _cursor->next;
		v->last = _cursor;
		_cursor->next->last = v;
		_cursor->next = v;
	}
}

template <class T>
inline void T_CircularList<T>::addBack(T& e)
{
	T_CircularListNode<T> * v = new T_CircularListNode<T>(&e);

	if (_cursor == nullptr)
	{
		v->next = v;
		v->last = v;
		_cursor = v;
	}
	else
	{
		v->last = _cursor->last;
		v->next = _cursor;
		_cursor->last->next = v;
		_cursor->last = v;
	}
}

template<class T>
inline void T_CircularList<T>::remove()
{
	T_CircularListNode<T> * old = _cursor->next;
	if (old == _cursor)
	{
		_cursor = nullptr;
	}
	else
	{
		_cursor->next = old->next;
		_cursor->next->last = _cursor;
		delete old;
	}
}
