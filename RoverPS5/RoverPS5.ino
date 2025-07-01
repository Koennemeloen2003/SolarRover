#include "Controller.h"
#include "Setup.h"
#include "motor.h"
#include "Linetracker.h"
#include "Solar.h"
#include "Ultrasonic.h"
#include "Tof.h"
#include <uni.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  delay(1000);
  pinSetup();
  ControllerSetup();
  setupPWM();
  setUltrasoon();
  setToF();
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
  if (useLineTracker == true && (timer2 +100 < millis())){
    //linetracker();
    LineTrackerMove2();
    swapValues(right_value);
    timer2=millis();
  }

  if (useSolarTracker == true && (timer4 + 100 < millis())){
    solarSensor();
    timer4 = millis();
  }

  if (detectorOn == true && (timer4 + 500 < millis())){
    setServoAngleSensor(15, 90);
    loopSensor();
    calcObject();
    setServoAngleSensor(15, 90);
    timer4 = millis();
  }
  
  
}
