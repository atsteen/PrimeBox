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

#include "..\..\..\..\Configurations\PX4_Config.h"
#include "..\..\\ComponentModule_Buzzer.h"
#include "..\..\..\..\Platform\include\SharedStructure\ToneItem.h"

class ComponentModule_Buzzer_Standard :
	public ComponentModule_Buzzer
{
public:
	ComponentModule_Buzzer_Standard(ComponentModule_Imp_Buzzer *imp);
	virtual ~ComponentModule_Buzzer_Standard() override;

	void playNavTone();
	void playSelectTone();
	void playBackSelectTone();
	void playSuccessPostTone();

	// Inherited via ComponentModule
	virtual bool DoSelfDiagnostic() override;

	// Inherited via ComponentModule_Buzzer
	virtual void Beep() override;

protected:

	// Tone items are used in tunes { noteFrequency, noteDurationMS }
	ToneItem defaultNavTone = { NOTE_7K, 5 };
	ToneItem selectTune_1 = { NOTE_AS4 , 50 };
	ToneItem selectTune_2 = { NOTE_GS4 , 50 };
	ToneItem selectTune_3 = { NOTE_F5 , 50 };
	ToneItem backSelectTune_1 = { NOTE_B4 , 50 };
	ToneItem backSelectTune_2 = { NOTE_F4 , 50 };
	ToneItem backSelectTune_3 = { NOTE_D4 , 50 };
	ToneItem postSuccessTune_1 = { NOTE_C5 , 50 };
	ToneItem postSuccessTune_2 = { NOTE_D5 , 50 };
	ToneItem postSuccessTune_3 = { NOTE_D6 , 50 };
	ToneItem postSuccessTune_4 = { NOTE_C5 , 50 };
};