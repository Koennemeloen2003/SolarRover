#include "Controller.h"
#include "Setup.h"
#include "motor.h"
#include "Linetracker.h"
#include "Solar.h"
#include "Display.h"
#include "StroomSensor.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  ControllerSetup();
  setupPWM();
  linetrackersetup();
  INASetup();
  displaySetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  controllerUpdate();
  Serial.printf("%d \t %d \t %d \t %d\n",analogRead(ldrLeft), analogRead(ldrRight), analogRead(solarKnopRight), analogRead(solarKnopLeft)); 
  if ((timer + 100 < millis()) && useLineTracker == false){
    speedCalc();
    steerCalc();
    motorSet();
    timer = millis();
  } 
  if (useLineTracker == true && (timer2 +1000 < millis())){
    linetracker();
    timer2=millis();
  }
  if(ina228_IN.conversionReady()){
    readINA();
    displayLoop();
  }
  if (useSolarTracker == true && (timer4 + 100 < millis())){
    solarSensor();
    timer4 = millis();
  }
  
}
