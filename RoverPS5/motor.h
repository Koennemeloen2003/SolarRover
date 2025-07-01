#ifndef motor_h
#define motor_h

#include "Controller.h"
#include "Setup.h"

float calcRealSpeed(float volt, float gears, float circumference){
  float speed;
  if (volt == 0){
    return 0;
  }
  else{
    return  (20.35*volt-1.95)/gears*circumference*10/60;
  }
}

void speedCalc(){
  SpeedF= map(SpeedF, 0, 1020, 0, 4095);
  SpeedR = map(SpeedR, 0, 1020, 0, 4095);
  float temp = (SpeedF-SpeedR);
  float temp2 = 5*temp/4095;
  realSpeed = calcRealSpeed(temp2, 3.625, 62.8);
  Serial2.println(realSpeed);
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

void motors(int Speed, int SteerLeft, int SteerRight, bool Forward){
      if (Forward > 0) {
        pwm.setPWM(leftEneable, 0, 0);
        pwm.setPWM(rightEneable, 0, 0);

        pwm.setPWM(leftFR, 0, 0);
        pwm.setPWM(rightFR, 0, 4095);

        pwm.setPWM(leftMotor, 0, (Speed/SteerLeft)*10);
        pwm.setPWM(rightMotor, 0, (Speed/SteerRight)*10);
        
      }
      else{
        pwm.setPWM(leftEneable, 0, 0);
        pwm.setPWM(rightEneable, 0, 0);

        pwm.setPWM(leftFR, 0, 4095);
        pwm.setPWM(rightFR, 0, 0);
        
        pwm.setPWM(leftMotor, 0, (Speed/SteerLeft)*10);
        pwm.setPWM(rightMotor, 0, (Speed/SteerRight)*10);
        
      }
}

void motorSet(){
    // Drive each pin in a 'wave'
    if (SpeedF>0 && SpeedR ==0){
      motors(SpeedF, SteerL, SteerR, true);

    }
    else if (SpeedR > 0 && SpeedF==0){
      motors(SpeedR, SteerL, SteerR, false);
    }
    else if (SpeedF>0 && SpeedR <SpeedF){
      motors(SpeedF - SpeedR, SteerL, SteerR, true);
    }
    else if (SpeedR>0 && SpeedF <SpeedR){
      motors(SpeedR - SpeedF, SteerL, SteerR, false);
    }
    else {
      pwm.setPWM(leftMotor, 0, 0);
      pwm.setPWM(rightMotor, 0, 0);
      pwm.setPWM(leftEneable, 0, 4095);
      pwm.setPWM(rightEneable, 0, 4095);

    }
}


#endif