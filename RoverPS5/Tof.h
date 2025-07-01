#ifndef tof_h
#define tof_h

#include <Adafruit_VL53L0X.h>
#include "Setup.h"
#include "Ultrasonic.h"
#include "Controller.h"

Adafruit_VL53L0X lox;

void setToF(){
    // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin(0x29)) {
    Serial.println(F("Failed to boot VL53L0X"));
  }
  else{
    Serial.println("Tof sensor is tof");
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
}

void readToF() {
  if (!lox.isRangeComplete()){
    return;
  }

  readToFsensor = lox.readRange();
  Serial.printf("%d \n", readToFsensor);
  objectTooClose = 0;
  objectInRange = 0;
  objectOutRange = 0;
  objectTooFar = 0;

  if (readToFsensor < minRange) {
    objectTooClose = 1;
  } else if (readToFsensor < maxRange) {
    objectInRange = 1;
  } else if (readToFsensor < maxOutRange) {
    objectOutRange = 1;
  } else {
    objectTooFar = 1;
  }

  if (objectInRange && !previousObjectInRange) {
    objectStart[0] = servoPos;
    objectStart[1] = readToFsensor;
  }

  if (!objectInRange && previousObjectInRange) {
    objectEnd[0] = previousAngle;
    objectEnd[1] = previousDistance;
  }

  previousObjectInRange = objectInRange;
  previousDistance = readToFsensor;
  previousAngle = servoPos;

  if (scanCount >= lastUpdateCount + 2) {
    objectWasInRange = objectInRange;
    lastUpdateCount = scanCount;
  }
}

void calcObject() {
  // Gemiddelde berekening van start- en eindpositie van het object
  objectAverage[0] = (objectEnd[0] + objectStart[0]) / 2;  // servohoek
  objectAverage[1] = (objectEnd[1] + objectStart[1]) / 2;  // afstand in mm

  // Conversie naar bruikbare eenheden
  y_sensor = objectAverage[0];                    // richting (graden, niet begrensd)
  x_sensor = objectAverage[1] / 10.0;             // afstand in cm

  // Afronden naar 1 decimaal
  x_sensor = round(x_sensor * 10) / 10.0;
  y_sensor = round(y_sensor * 10) / 10.0;
}

void setServoAngleSensor(int channel, int angle) {
  int pulse = map(angle, 0, 180, 102, 512); // ca. 0.5 ms â 2.5 ms op 12-bit schaal
  pwm.setPWM(channel, 0, pulse);
}

void loopSensor() {
  Ultradistance = calculateDistance();


  if (Ultradistance > 0 && Ultradistance < 50) {
    for (pos = minPos; pos <= maxPos; pos++) {
      setServoAngleSensor(PWM_ServoSensor, pos);
      servoPos = pos;
      readToF();
      delay(15);
    }
    for (pos = maxPos; pos >= minPos; pos--) {
      setServoAngleSensor(PWM_ServoSensor, pos);
      servoPos = pos;
      readToF();
      delay(15);
    }

    scanCount++;
  }

  delay(100);

}

#endif