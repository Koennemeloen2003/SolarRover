#include "Controller.h"
#include "Setup.h"
#include "motor.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = millis();
  ControllerSetup();
  setupPWM();
}

void loop() {
  // put your main code here, to run repeatedly:
  controllerUpdate();
  if (timer + 100 < millis()){
    
    speedCalc();
    steerCalc();
    motorSet();
    timer = millis();

  } 
}
