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

#include "..\include\ComponentPackage_UI_PX4.h"

ComponentPackage_UI_PX4::ComponentPackage_UI_PX4(ComponentModuleImp_Factory_PX4* componentImpFactory)
{
	_buzzer = new ComponentModule_Buzzer_Standard(componentImpFactory->Make_Buzzer());
	_textDisplay = new ComponentModule_ASCIIDisplay_Standard(componentImpFactory->Make_ASCIIDisplay());
	_encoderControl = new ComponentModule_RotaryEncoder_Standard(componentImpFactory->Make_Control_RotaryEncoder());
}

ComponentPackage_UI_PX4::~ComponentPackage_UI_PX4()
{
	delete _buzzer;
	delete _textDisplay;
	delete _encoderControl;
}

void ComponentPackage_UI_PX4::playNavTone()
{
	_buzzer->playNavTone();
}

void ComponentPackage_UI_PX4::playSelectTone()
{
	_buzzer->playSelectTone();
}

void ComponentPackage_UI_PX4::playBackSelectTone()
{
	_buzzer->playBackSelectTone();
}

void ComponentPackage_UI_PX4::playSuccessPostTone()
{
	_buzzer->playSuccessPostTone();
}

void ComponentPackage_UI_PX4::EnableBacklight()
{
	_textDisplay->Enable();
}

void ComponentPackage_UI_PX4::DisableBacklight()
{
	_textDisplay->Disable();
}

void ComponentPackage_UI_PX4::WriteDisplayText(const char * text)
{
	_textDisplay->UpdateDisplay(text);
}

const bool ComponentPackage_UI_PX4::BacklightEnabled()
{
	return _textDisplay->isEnabled();
}

TaskAlias ComponentPackage_UI_PX4::GetRequestedTask()
{
	return _encoderControl->GetFlaggedTask();
}
