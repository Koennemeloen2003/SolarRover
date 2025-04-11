#include "esp32-hal-adc.h"
#ifndef solar_h
#define solar_h

#include "Controller.h"
#include "Setup.h"


void solarStep(int stepsize, bool left, int button){
  if (analogRead(button) < 1000)
    if (left>0){ 
      
      pwm.setPWM(stapEneable, 0 ,0);
      pwm.setPWM(stapFR, 0 ,0);
      pwm.setPWM(stapmotor, 0, 2045);
      delay(stepsize);
      pwm.setPWM(stapEneable, 0 ,4095);
      pwm.setPWM(stapmotor, 0, 0);
    
    }
    else{
      pwm.setPWM(stapEneable, 0 ,0);
      pwm.setPWM(stapFR, 0 ,4095);
      pwm.setPWM(stapmotor, 0, 2045);
      delay(stepsize);
      pwm.setPWM(stapEneable, 0 ,4095);
      pwm.setPWM(stapmotor, 0, 0);
    }
  
}

void solarSensor(){
  int solarDif = analogRead(ldrRight)-analogRead(ldrLeft);
  switch (solarDif){
    case -4000 ... -2000:
      solarStep(400, true, solarKnopRight);
      break;
    case -1999 ... -1000:
      solarStep(200, true, solarKnopRight);
      break;
    case -999 ... -100:
      solarStep(100, true, solarKnopRight);
      break;
      case 100 ... 999:
      solarStep(100, false, solarKnopLeft);
      break;
    case 1000 ... 1999:
      solarStep(200, false, solarKnopLeft);
      break;
    case 2000 ... 4000:
      solarStep(400, false, solarKnopLeft);
      break;
  }
}




void stappenmotor(){
  solarStep(100, true, solarKnopRight);
}

void stappenmotorReverse(){
  solarStep(100, false, solarKnopLeft);
}
#endif