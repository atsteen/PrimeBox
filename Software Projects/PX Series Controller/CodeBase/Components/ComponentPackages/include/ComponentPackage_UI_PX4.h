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

#include "..\..\..\Platform\include\SharedStructure\SharedInterface\INavigationTones.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IPostTones.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\ITextDisplay.h"
#include "..\..\..\Platform\include\SharedStructure\SharedInterface\IPolledInterfaceControl.h"
#include "..\..\..\Components\ImplementationFactory\include\ComponentModuleImp_Factory_PX4.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_Buzzer_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_ASCIIDisplay_Standard.h"
#include "..\..\..\Components\Abstraction\Refined\include\ComponentModule_RotaryEncoder_Standard.h"

class ComponentPackage_UI_PX4 :
	public INavigationTones,
	public IPostTones,
	public ITextDisplay,
	public IPolledInterfaceControl
{
public:
	ComponentPackage_UI_PX4(ComponentModuleImp_Factory_PX4* componentImpFactory);
	~ComponentPackage_UI_PX4();

	// Inherited via IHasNavigationTones
	virtual void playNavTone() override;
	virtual void playSelectTone() override;
	virtual void playBackSelectTone() override;

	// Inherited via IHasPostTones
	virtual void playSuccessPostTone() override;

	// Inherited via ITextDisplay
	virtual void EnableBacklight() override;
	virtual void DisableBacklight() override;
	virtual void WriteDisplayText(const char *) override;
	virtual const bool BacklightEnabled() override;

	// Inherited via IPolledInterfaceControl
	virtual TaskAlias GetRequestedTask() override;

private:
	ComponentModule_Buzzer_Standard * _buzzer;
	ComponentModule_ASCIIDisplay_Standard * _textDisplay;
	ComponentModule_RotaryEncoder_Standard * _encoderControl;
};