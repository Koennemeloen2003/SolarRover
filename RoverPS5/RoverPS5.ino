#include "Controller.h"
#include "Setup.h"
#include "motor.h"
#include "Linetracker.h"
#include "Solar.h"
#include <uni.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  pinSetup();
  ControllerSetup();
  setupPWM();
  //linetrackersetup();
  LineTrackSetup2();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  controllerUpdate();
  if ((timer + 100 < millis()) && useLineTracker == false){
    speedCalc();
    steerCalc();
    motorSet();
    timer = millis();
   // Serial.printf("%d \t %d \t %d \t %d\n",analogRead(ldrLeft), analogRead(ldrRight), analogRead(solarKnopRight), analogRead(solarKnopLeft)); 

  } 
  if (useLineTracker == true && (timer2 +1000 < millis())){
    //linetracker();
    LineTrackerMove2();
    swapValues(right_value);
    timer2=millis();
  }

  if (useSolarTracker == true && (timer4 + 100 < millis())){
    solarSensor();
    timer4 = millis();
  }

  
}
