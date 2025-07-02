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
  pwm.setPWMFreq(50);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

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

int right_value;
int solarDif;

int armShoulder;
int armElbow;
int elbowAngle= 90;
int shoulderAngele = 90;

bool useLineTracker = false;
bool useSolarTracker = false;
bool magnetOn = false;
bool detectorOn = false;
bool handmatigArm = false;

int scanCount = 0;
int lastUpdateCount = -2;

int objectStart[2];
int objectEnd[2];
int objectAverage[2];

int PWM_ServoSensor = 15;
float x_sensor = 0.0;
float y_sensor = 0.0;
int Ultradistance;
int pos = 0;    // variable to store the servo position
int servoPos = 0;
int minPos = 0;
int maxPos = 180;
int readToFsensor = 0;
int minRange = 250;
int maxRange = 500;
int maxOutRange = 2000;
int previousDistance;
int previousAngle;
bool previousObjectInRange = 0;
bool objectTooClose = 0;
bool objectInRange = 0;
bool objectOutRange = 0;
bool objectTooFar = 0;
bool objectWasInRange;
int objectCoordinatesDeg;



#define leftMotor 2
#define leftFR 0
#define leftEneable 1

#define stapmotor 11
#define stapFR 9
#define stapEneable 10 

#define rightMotor 5
#define rightFR 3
#define rightEneable 4

#define ldrRight 32
#define ldrLeft 25
#define solarKnopRight 35
#define solarKnopLeft 33

#define magneetTransistor 18
#define detectorTransistor 19

#define trigPin 15
#define echoPin 12

float realSpeed;

int betereJoystick(int Xmax, float x, float Pmax, float p, int Amplitude) {
  return Amplitude * (x * sqrt(sq(Pmax) - sq(p))) / (sqrt(sq(Pmax) * sq(Xmax) - sq(p * x)));
}

void pinSetup(){
  pinMode(magneetTransistor, OUTPUT);
  pinMode(detectorTransistor, OUTPUT);
}

#endif