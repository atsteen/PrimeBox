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
#include "..\..\include\SharedStructure\Observer.h"
#include "..\..\..\Configurations\PX4_Config.h"

class Subject
{
public:
	bool attachObserver(Observer *o);
	void detachObserver(Observer *o);
	void notifyObservers();

protected:
	Observer *_observers[OBSERVER_LIMIT] = { 0 };
};

inline void Subject::notifyObservers()
{
	for (int i = 0; i < OBSERVER_LIMIT; i++)
	{
		if (_observers[i]) { _observers[i]->update(*this); }
	}
}

inline bool Subject::attachObserver(Observer *o)
{
	for (int i = 0; i < OBSERVER_LIMIT; i++)
	{
		if (!_observers[i])
		{
			_observers[i] = o;
			return true;
		}
	}

	return false;
}

inline void Subject::detachObserver(Observer *o)
{
	for (int i = 0; i < OBSERVER_LIMIT; i++)
	{
		if (_observers[i] && _observers[i] == o)
		{
			_observers[i] = nullptr;
		}
	}
}
