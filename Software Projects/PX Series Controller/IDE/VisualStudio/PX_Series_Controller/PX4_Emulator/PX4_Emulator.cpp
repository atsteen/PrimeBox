// PX4_Emulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\..\..\CodeBase\Platform\include\Controller\Controller_PX4.h"


int main()
{
	Controller_PX4 controller;

	controller.Initialize();
	while (controller.Run());
	controller.Shutdown();

    return 0;
}

