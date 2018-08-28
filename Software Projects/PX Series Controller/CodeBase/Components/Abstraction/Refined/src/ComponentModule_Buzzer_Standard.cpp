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

#include "..\include\ComponentModule_Buzzer_Standard.h"

ComponentModule_Buzzer_Standard::ComponentModule_Buzzer_Standard(ComponentModule_Imp_Buzzer* imp) : ComponentModule_Buzzer(imp){}

ComponentModule_Buzzer_Standard::~ComponentModule_Buzzer_Standard(){}

void ComponentModule_Buzzer_Standard::playNavTone()
{
	_imp->MakeTone(&defaultNavTone);
}

void ComponentModule_Buzzer_Standard::playSelectTone()
{
	T_queue<ToneItem *> tones;
	tones.Enqueue(&selectTune_1);
	tones.Enqueue(&selectTune_2);
	tones.Enqueue(&selectTune_3);

	_imp->MakeTune(tones);
}

void ComponentModule_Buzzer_Standard::playBackSelectTone()
{
	T_queue<ToneItem *> tones;
	tones.Enqueue(&backSelectTune_1);
	tones.Enqueue(&backSelectTune_2);
	tones.Enqueue(&backSelectTune_3);

	_imp->MakeTune(tones);
}

void ComponentModule_Buzzer_Standard::playSuccessPostTone()
{
	T_queue<ToneItem *> tones;
	tones.Enqueue(&postSuccessTune_1);
	tones.Enqueue(&postSuccessTune_2);
	tones.Enqueue(&postSuccessTune_3);
	tones.Enqueue(&postSuccessTune_4);

	_imp->MakeTune(tones);
}

bool ComponentModule_Buzzer_Standard::DoSelfDiagnostic()
{
	return _imp->DoSelfDiagnostic_Imp();
}

void ComponentModule_Buzzer_Standard::Beep()
{
	_imp->MakeTone(&defaultNavTone);
}
