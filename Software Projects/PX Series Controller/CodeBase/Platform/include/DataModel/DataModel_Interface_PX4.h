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
#include "..\SharedStructure\SharedInterface\IModelInterfaceData.h"
#include "..\SharedStructure\Subject.h"

class DataModel_Interface_PX4 :	public IModelInterfaceData, public Subject
{
public:
	DataModel_Interface_PX4() {};
	~DataModel_Interface_PX4() {};

	// Inherited via IModelInterfaceData
	virtual const bool GetPromptInputModalState() override;
	virtual const TimeSignature * LastInputActionTime() override;
	virtual void RegisterUserInputAction(TimeSignature ts) override;
	virtual void SetPromptInputModalState(bool state) override;

protected:
	TimeSignature _lastInputActionTime = { 0,0,0 };

private:
	bool _promptInputModalState = false;
};