#ifndef arm_h
#define arm_h

#include "Tof.h"
#include "Setup.h"

void moveArm(int joystick, bool elbow){
  if(joystick > 100){
    if(elbow){
      elbowAngle += 5;
      setServoAngleSensor(14, elbowAngle);
    }
    else{
      shoulderAngele += 5;
      setServoAngleSensor(12, shoulderAngele);
    }
  }
  else if(joystick < -100){
        if(elbow){
          elbowAngle -= 5;
          setServoAngleSensor(14, elbowAngle);
        }
    else{
      shoulderAngele -= 5;
      setServoAngleSensor(12, shoulderAngele);
    }
  }
}

#endif