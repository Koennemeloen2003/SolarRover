#include "esp32-hal-gpio.h"

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
  if (!pwm.begin()){
    Serial.println("PWM bordje wil niet");
  }
  else {
    Serial.println("PWM bordje gevonden");
  }
  pwm.setPWMFreq(1000);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

unsigned int data;
unsigned long previousWatchDogTime;
unsigned long timer = 0;
unsigned long timer2= 0;
unsigned long timer3 = 0;
unsigned long timer4 = 0;

int SpeedF;
int SpeedR;
int Steer;
float SteerL;
float SteerR;

float currentOut;
float voltageOut;
float powerIn;
float powerOut;
float tempIn;
float tempOut;

int solarDif;
int solarLocation = 0;

bool useLineTracker = false;
bool useSolarTracker = false;

#define leftMotor 0
#define leftFR 1
#define leftEneable 2

#define stapmotor 4
#define stapFR 5
#define stapEneable 6

#define rightMotor 8
#define rightFR 9
#define rightEneable 10

#define ldrRight 32
#define ldrLeft 33
#define solarKnop 25

int betereJoystick(int Xmax, float x, float Pmax, float p, int Amplitude) {
  return Amplitude * (x * sqrt(sq(Pmax) - sq(p))) / (sqrt(sq(Pmax) * sq(Xmax) - sq(p * x)));
}

#endif