#ifndef ultrasonic_h
#define ultrasonic_h

#include "Setup.h"


void setUltrasoon(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long calculateDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);  // Voeg timeout toe
  if (duration == 0) return -1;              // Geen object gedetecteerd
  distance = (duration / 2) / 29.1;
  return distance;
}

#endif