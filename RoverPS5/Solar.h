#include "esp32-hal-adc.h"
#ifndef solar_h
#define solar_h

#include "Controller.h"
#include "Setup.h"

void solarSetup(){
  while(analogRead(solarKnop) < 1000){
    pwm.setPWM(stapEneable, 0 ,0);
    pwm.setPWM(stapFR, 0 ,0);
    pwm.setPWM(stapmotor, 0, 2045);
  }
  pwm.setPWM(stapEneable, 0 ,4095);
  pwm.setPWM(stapmotor, 0, 0);
  pwm.setPWM(stapEneable, 0 ,0);
  pwm.setPWM(stapFR, 0 ,4095);
  pwm.setPWM(stapmotor, 0, 2045);
  delay(2000);
  pwm.setPWM(stapmotor, 0, 0);
  pwm.setPWM(stapEneable, 0 ,4095);
}

void solarStep(int stepsize, bool right){
  if (right>0){ 
    pwm.setPWM(stapEneable, 0 ,0);
    pwm.setPWM(stapFR, 0 ,0);
    pwm.setPWM(stapmotor, 0, 2045);
    delay(stepsize);
    pwm.setPWM(stapEneable, 0 ,4095);
    pwm.setPWM(stapmotor, 0, 0);
    solarLocation += stepsize;
  }
  else{
    pwm.setPWM(stapEneable, 0 ,0);
    pwm.setPWM(stapFR, 0 ,4095);
    pwm.setPWM(stapmotor, 0, 2045);
    delay(stepsize);
    pwm.setPWM(stapEneable, 0 ,4095);
    pwm.setPWM(stapmotor, 0, 0);
    solarLocation -= stepsize;
  }
  
}

void solarSensor(){
  int solarDif = analogRead(ldrRight)-analogRead(ldrLeft);
  switch (solarDif){
    case -4000 ... -2000:
      solarStep(200, false);
      break;
    case -1999 ... -100:
      solarStep(100, false);
      break;
    case 100 ... 1999:
      solarStep(100, true);
      break;
    case 2000 ... 4000:
      solarStep(200, true);
      break;
  }
  timer4 = millis();
}




void stappenmotor(){
  pwm.setPWM(stapEneable, 0 ,0);
  pwm.setPWM(stapFR, 0 ,0);
  pwm.setPWM(stapmotor, 0, 2045);
  delay(100);
  pwm.setPWM(stapmotor, 0, 0);
  pwm.setPWM(stapEneable, 0 ,4095);
}

void stappenmotorReverse(){
  pwm.setPWM(stapEneable, 0 ,0);
  pwm.setPWM(stapFR, 0 , 4095);
  pwm.setPWM(stapmotor, 0, 2045);
  delay(10);
  pwm.setPWM(stapmotor, 0, 0);
  pwm.setPWM(stapEneable, 0 ,4095);
}
#endif