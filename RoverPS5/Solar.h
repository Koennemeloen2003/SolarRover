#include "esp32-hal-adc.h"
#ifndef solar_h
#define solar_h

#include "Controller.h"
#include "Setup.h"


void solarStep(int stepsize, bool right, int button){
  if (analogRead(button) < 1000){

    if (right>0){ 
      
      pwm.setPWM(stapEneable, 0 ,0);
      pwm.setPWM(stapFR, 0 ,0);
      pwm.setPWM(stapmotor, 0, 2045);
      delay(stepsize);
      pwm.setPWM(stapEneable, 0 ,4095);
      pwm.setPWM(stapmotor, 0, 0);
      Serial.println("rechts");
    
    }
    else{
      pwm.setPWM(stapEneable, 0 ,0);
      pwm.setPWM(stapFR, 0 ,4095);
      pwm.setPWM(stapmotor, 0, 2045);
      delay(stepsize);
      pwm.setPWM(stapEneable, 0 ,4095);
      pwm.setPWM(stapmotor, 0, 0);
      Serial.println("links");
    }
  }
}

void solarSensor(){
  int solarDif = analogRead(ldrRight)-analogRead(ldrLeft);
  switch (solarDif){
    case -4000 ... -2000:
      solarStep(400, false, solarKnopLeft);
      break;
    case -1999 ... -500:
      solarStep(200, false, solarKnopLeft);
      break;
    case -499 ... -150:
      solarStep(100, false, solarKnopLeft);
      break;
      case 150 ... 499:
      solarStep(100, true, solarKnopRight);
      break;
    case 500 ... 1999:
      solarStep(200, true, solarKnopRight);
      break;
    case 2000 ... 4000:
      solarStep(400, true, solarKnopRight);
      break;
  }
}




void stappenmotor(){
  solarStep(400, true, solarKnopRight);
}

void stappenmotorReverse(){
  solarStep(400, false, solarKnopLeft);
}
#endif