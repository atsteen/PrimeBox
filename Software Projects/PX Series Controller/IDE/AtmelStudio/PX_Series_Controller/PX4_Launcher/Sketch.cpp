/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

#include "Controller_PX4.h"
#include "PX4_Config.h"
#include "MemoryProbe.h"

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
	Controller_PX4 controller;

	controller.Initialize();
	while (controller.Run());
	controller.Shutdown();
}
