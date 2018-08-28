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
class T_Stack
{
public:
	T_Stack() {};
	~T_Stack() {};

	const bool Push(const T newItem);
	const bool Top(T * newItem);
	const bool Pop();	

private:
	T _stackItems[T_STACK_MAX_SIZE] = {};
	int _stackCount = 0;
};

template<class T> const bool T_Stack<T>::Push(const T newItem)
{
	if (_stackCount >= T_STACK_MAX_SIZE) { return false; }
	else { _stackItems[_stackCount++] = newItem; }

	return true;
}

template<class T> const bool T_Stack<T>::Top(T * newItem)
{
	if (_stackCount < 1){ return false; }
	else{ *newItem = _stackItems[_stackCount - 1]; }

	return true;
}

template<class T> const bool T_Stack<T>::Pop()
{
	if (_stackCount < 1) { return false; }
	
	--_stackCount;
	return true;
}
