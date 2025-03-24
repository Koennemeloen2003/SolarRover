#include "Controller.h"
#include "Setup.h"
#include "motor.h"
#include "Linetracker.h"

bool linetrackerbool = true; // tijdelijk permanent op true

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = millis();
 // ControllerSetup();
  setupPWM();
  Serial.println("test1");
  linetrackersetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  //controllerUpdate();

  // dit zou aangesloten worden aan die knop op het afstrandsbediening die de linetracker aan of uit zet.
  //if (linetrackerbool == false) {
  if (timer + 100 < millis()){
    Serial.println("test2");
   // speedCalc();
    //steerCalc();
    //motorSet();
    timer = millis();
  } 
  Serial.println("test3");
  
  linetracker();
  
}
