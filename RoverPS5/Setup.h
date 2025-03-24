
#ifndef Setup_h
#define Setup_h

#include <Bluepad32.h>
#include "Controller.h"
#include <Wire.h>  //I2C communication library
#include <Adafruit_PWMServoDriver.h>

  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void setupPWM() {
  Serial.println("GPIO test!");
  pwm.begin();
  pwm.setPWMFreq(1000);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

unsigned int data;
unsigned long previousWatchDogTime;
unsigned long timer = millis();
unsigned long timer2= millis();
unsigned long timer3 = millis();

int SpeedF;
int SpeedR;
int Steer;
float SteerL;
float SteerR;

bool useLineTracker = false;

#define leftMotor 0
#define leftFR 1
#define leftEneable 2

#define stapmotor 4
#define stapFR 5
#define stapEneable 6

#define rightMotor 8
#define rightFR 9
#define rightEneable 10

int betereJoystick(int Xmax, float x, float Pmax, float p, int Amplitude) {
  return Amplitude * (x * sqrt(sq(Pmax) - sq(p))) / (sqrt(sq(Pmax) * sq(Xmax) - sq(p * x)));
}

#endif