#ifndef motor_h
#define motor_h

#include "Controller.h"
#include "Setup.h"

void speedCalc(){
  SpeedF= map(SpeedF, 0, 1020, 0, 4095);
  SpeedR = map(SpeedR, 0, 1020, 0, 4095);
}

void steerCalc(){
  if (Steer > 0){
    SteerR = betereJoystick(512, Steer, 16, 15.99, 512);
    SteerL= 10;
    SteerR = map(SteerR, 0, 512, 10, 100);
  }
  else if (Steer < 0){
    SteerL = betereJoystick(508, -1*Steer, 16, 15.99, 508);
    SteerL= map(SteerL, 0, 508, 10, 100);
    SteerR = 10;
  }
}


void motorSet(){
    // Drive each pin in a 'wave'
    if (SpeedF>0 && SpeedR ==0){
      pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, (SpeedF/SteerL)*10);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, (SpeedF/SteerR)*10);
      pwm.setPWM(rightFR, 0, 4095);
    }
    else if (SpeedR > 0 && SpeedF==0){
      pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, (SpeedR/SteerL)*10);
      pwm.setPWM(leftFR, 0, 4095);
      pwm.setPWM(rightMotor, 0, (SpeedR/SteerR)*10);
      pwm.setPWM(rightFR, 0, 0);
    }
    else if (SpeedF>0 && SpeedR <SpeedF){
      pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, ((SpeedF-SpeedR)/SteerL)*10);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, ((SpeedF-SpeedR)/SteerR)*10);
      pwm.setPWM(rightFR, 0, 4095);
    }
    else if (SpeedR>0 && SpeedF <SpeedR){
      pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, ((SpeedR-SpeedF)/SteerL)*10);
      pwm.setPWM(leftFR, 0, 4095);
      pwm.setPWM(rightMotor, 0, ((SpeedR-SpeedF)/SteerR)*10);
      pwm.setPWM(rightFR, 0, 0);
    }
    else {
      pwm.setPWM(leftMotor, 0, 0);
      pwm.setPWM(rightMotor, 0, 0);
      pwm.setPWM(leftEneable, 0, 4095);
      pwm.setPWM(rightEneable, 0, 4095);

    }
}

#endif