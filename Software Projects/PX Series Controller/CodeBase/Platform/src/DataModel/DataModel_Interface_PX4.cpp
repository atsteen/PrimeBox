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

#include "..\..\include\DataModel\DataModel_Interface_PX4.h"

const bool DataModel_Interface_PX4::GetPromptInputModalState()
{
	return _promptInputModalState;
}

const TimeSignature * DataModel_Interface_PX4::LastInputActionTime()
{
	return &_lastInputActionTime;
}

void DataModel_Interface_PX4::RegisterUserInputAction(TimeSignature ts)
{
	_lastInputActionTime = ts;

	//todo... review this notify callback remove if not needed (was forcing pre-render of viewstates prior to event handler execution)
	//this->notifyObservers();
}

void DataModel_Interface_PX4::SetPromptInputModalState(bool state)
{
	_promptInputModalState = state;
	this->notifyObservers();
}
