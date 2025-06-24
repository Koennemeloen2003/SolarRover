#ifndef StroomSensor_h
#define StroomSensor_h

#include "Setup.h"
#include <Adafruit_INA228.h>

Adafruit_INA228 ina228_IN = Adafruit_INA228();
Adafruit_INA228 ina228_OUT = Adafruit_INA228();

void INASetup(){
    if (!ina228_IN.begin(0x41)) {
    Serial.println("Couldn't find INA228 input chip");
    while (1);
  }
  Serial.println("Found INA228 input chip");
  // set shunt resistance and max current
  ina228_IN.setShunt(0.015, 10.0);

     if (!ina228_OUT.begin(0x44)) {
    Serial.println("Couldn't find INA228 output chip");
    while (1);
  }
  Serial.println("Found INA228 output chip");
  // set shunt resistance and max current
  ina228_OUT.setShunt(0.015, 10.0);

  ina228_IN.setAveragingCount(INA228_COUNT_16);
  ina228_OUT.setAveragingCount(INA228_COUNT_16);

  ina228_IN.setVoltageConversionTime(INA228_TIME_150_us);
  ina228_OUT.setVoltageConversionTime(INA228_TIME_150_us);

  ina228_IN.setCurrentConversionTime(INA228_TIME_280_us);
  ina228_OUT.setCurrentConversionTime(INA228_TIME_280_us);
}

void readINA(){

  currentOut = ina228_OUT.readCurrent()/1000;
  voltageOut = ina228_OUT.readBusVoltage()/1000000;
  powerIn = ina228_IN.readPower()/1000;
  powerOut = ina228_OUT.readPower()/1000;
  tempIn = ina228_IN.readDieTemp();
  tempOut = ina228_OUT.readDieTemp();

  Serial.printf("%f \t %f \t %f \t %f\n", currentOut, voltageOut, powerIn, powerOut);
}

#endif