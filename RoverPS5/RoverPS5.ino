#include "Controller.h"
#include "Setup.h"
#include "motor.h"
#include "Linetracker.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ControllerSetup();
  setupPWM();
  Serial.println("test1");
  linetrackersetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  controllerUpdate();

  if ((timer + 100 < millis()) && useLineTracker == false){
    speedCalc();
    steerCalc();
    motorSet();
    timer = millis();
  } 
  if (useLineTracker && (timer2 +1000 < millis())){
    linetracker();
    timer2=millis();
  }
  
  
}
