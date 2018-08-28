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
struct T_ListNode
{
	T& element;
	T_ListNode<T> * next;
	T_ListNode(T & e) : element(e), next(nullptr) {}
	~T_ListNode() { delete &element; }
};

template <class T>
class T_List
{
public:
	T_List() : _head(nullptr), _tail(nullptr) {} // constructor
	~T_List() { while (!empty()) removeFront(); } // destructor
	bool empty() const { return _head == nullptr; } // is list empty?
	const T_ListNode<T> * front() const { return _head; } // element at head
	void addBack(T& e); // add after cursor
	void removeFront(); // remove node after head
private:
	T_ListNode<T> * _head; // the first node
	T_ListNode<T> * _tail; // the last node
};

template <class T>
inline void T_List<T>::addBack(T& e)
{
	T_ListNode<T> * v = new T_ListNode<T>(e);

	if (!_head)
	{
		_head = _tail = v;
	}
	else
	{
		_tail->next = v;
		_tail = v;
	}
}

template<class T>
inline void T_List<T>::removeFront()
{
	if (!_head) { return; }

	T_ListNode<T> * old = _head;

	if (_tail == _head)
	{
		_head = _tail = nullptr;
	}
	else
	{
		_head = old->next;
	}

	delete old;
}
