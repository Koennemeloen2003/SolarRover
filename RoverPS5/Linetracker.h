#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#ifndef Linetracker_h
#define Linetracker_h

Adafruit_MCP23X17 mcp;
/*
bool sensorstat[10] = {false, false, false, false, false, false, false, false, false, false};

void linetrackersetup() {
  //Serial.begin(9600);  // Using a higher baud rate for better performance on ESP32

  // Initialize I2C (default ESP32 pins: SDA=21, SCL=22)

  // Initialize MCP23017 with the correct I2C address
  if (!mcp.begin_I2C(0x27)) {  // Updated address
    Serial.println("Failed to initialize MCP23017. Check wiring or I2C address.");
    while (1);
  }

  Serial.println("MCP23017 Ready!");

  // Set MCP23017 pin 0 as input with pull-up enabled
  mcp.pinMode(0, INPUT);
  mcp.pinMode(1, INPUT);
  mcp.pinMode(2, INPUT);
  mcp.pinMode(3, INPUT);
  mcp.pinMode(4, INPUT);
  mcp.pinMode(11, INPUT);
  mcp.pinMode(12, INPUT);
  mcp.pinMode(13, INPUT);
  mcp.pinMode(14, INPUT);
  mcp.pinMode(15, INPUT);
  mcp.digitalWrite(0, HIGH);
  mcp.digitalWrite(1, HIGH);
  mcp.digitalWrite(2, HIGH);
  mcp.digitalWrite(3, HIGH);
  mcp.digitalWrite(4, HIGH);
  mcp.digitalWrite(11, HIGH);
  mcp.digitalWrite(12, HIGH);
  mcp.digitalWrite(13, HIGH);
  mcp.digitalWrite(14, HIGH);
  mcp.digitalWrite(15, HIGH);
}



void linetracker() {
  // Read the state of MCP23017 pin 0
  int sturen;
  int sensor0 = mcp.digitalRead(4);
  int sensor1 = mcp.digitalRead(3);
  int sensor2 = mcp.digitalRead(2);
  int sensor3 = mcp.digitalRead(1);
  int sensor4 = mcp.digitalRead(0);
  int sensor5 = mcp.digitalRead(11);
  int sensor6 = mcp.digitalRead(12);
  int sensor7 = mcp.digitalRead(13);
  int sensor8 = mcp.digitalRead(14);
  int sensor9 = mcp.digitalRead(15);

  if (sensor0 == LOW) {
      sensorstat[0] = true;
      sturen += 15;
    } else {
      sensorstat[0] = false;
  }

  if (sensor1 == LOW) {
      sensorstat[1] = true;
      sturen += 10;
    } else {
      sensorstat[1] = false;
  }

  if (sensor2 == LOW) {
      sensorstat[2] = true;
      sturen += 6;
    } else {
      sensorstat[2] = false;
  }

  if (sensor3 == LOW) {
    sturen += 3;
      sensorstat[3] = true;
    } else {
      sensorstat[3] = false;
  }

  if (sensor4 == LOW) {
      sensorstat[4] = true;
      sturen += 0;
    } else {
      sensorstat[4] = false;
  }

  if (sensor5 == LOW) {
      sturen += 0;
      sensorstat[5] = true;

    } else {
      sensorstat[5] = false;
  }

  if (sensor6 == LOW) {
      sensorstat[6] = true;
      sturen -= 3;
    } else {
      sensorstat[6] = false;
  }

  if (sensor7 == LOW) {
      sensorstat[7] = true;
      sturen -= 6;
    } else {
      sensorstat[7] = false;
  }

  if (sensor8 == LOW) {
      sturen -= 10;
      sensorstat[8] = true;
    } else {
      sensorstat[8] = false;
  }

  if (sensor9 == LOW) {
     sturen -= 15;
      sensorstat[9] = true;
    } else {
      sensorstat[9] = false;
  }

  for (int i = 0; i < 10; i++) {
    Serial.print(sensorstat[i] ? "[X]" : "[ ]");
  }
  Serial.println("");
  if (sturen > 15){

  }
  }
  
  if ((sensorstat[0] == true && sensorstat[1] == false && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false && sensorstat[8] == false && sensorstat[9] == false)||(sensorstat[1] == true && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false && sensorstat[8] == false && sensorstat[9] == false)) {
    Serial.println("Stuur naar rechts");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 2000);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 500);
      pwm.setPWM(rightFR, 0, 4095);
  }
  else if (sensorstat[2] == true && sensorstat[6] == false  && sensorstat[5] == false  && sensorstat[7] == false && sensorstat[8] == false && sensorstat[9] == false) {
     Serial.println("Stuur minder ver naar rechts");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 1000);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 500);
      pwm.setPWM(rightFR, 0, 4095);
  }

  else if (sensorstat[7] == true && sensorstat[0] == false && sensorstat[1] == false && sensorstat[2] == false  && sensorstat[4] == false && sensorstat[3] == false) {
    Serial.println("Stuur minder ver naar links");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 500);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 1000);
      pwm.setPWM(rightFR, 0, 4095);
  }
  else if ((sensorstat[8] == true && sensorstat[0] == false && sensorstat[1] == false && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false) || (sensorstat[9] == true && sensorstat[0] == false && sensorstat[1] == false && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false && sensorstat[8] == false)) {
    Serial.println("Stuur naar links");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 500);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 2000);
      pwm.setPWM(rightFR, 0, 4095);

  }
  else if (((sensorstat[3] == true || sensorstat[4] == true || sensorstat[5] == true || sensorstat[6] == true) && sensorstat[7] == false && sensorstat[2]== false) || (sensorstat[0] == true && sensorstat[1] == true && sensorstat[2] == true && sensorstat[3] == true && sensorstat[4] == true && sensorstat[5] == true && sensorstat[6] == true && sensorstat[7] == true && sensorstat[8] == true && sensorstat[9] == true)) { //stuur niet
  Serial.println("Stuur niet");
      pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 1000);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 1000);
      pwm.setPWM(rightFR, 0, 4095);
  }
  else {
    Serial.println("Doe niks");
    pwm.setPWM(leftMotor, 0, 0);
    pwm.setPWM(rightMotor, 0, 0);
    pwm.setPWM(leftEneable, 0, 4095);
    pwm.setPWM(rightEneable, 0, 4095);
  }



}

*/

void LineTrackSetup2()
{
  delay(1000);
 
  if (!mcp.begin_I2C(0x27)) {
    Serial.println("MCP23017 niet gevonden!");
  }
  else{
    Serial.println("Linetracker doet het");
  }
  
  int sensorPins[] = {0, 1, 2, 3, 4, 15, 13, 12, 11, 10};
  for (int i = 0; i < 10; i++) {
    mcp.pinMode(sensorPins[i], INPUT);
  }

  Serial.println("Setup compleet");

}
static inline int swapValues(int val) {

  return ((val & 0x01) << 4)  |  ((val & 0x02) << 2) | (val & 0x04)  | ((val & 0x08) >> 2) | ((val & 0x10) >> 4) ;

}


inline void LineTrackerMove2() {

  int left_value = 0;
  int right_value = 0;

 
  // Lees linker sensoren (PA0-PA4)

  for (int i = 0; i < 5; i++)
  {

    int sensorState = !mcp.digitalRead(i);
    left_value |= (sensorState << i);

  }

 
  // Lees rechter sensoren (PB3-PB7); hier wordt aangenomen dat deze op pins 11 t/m 15 zitten.
  for (int i = 0; i < 5; i++)
  {

    int sensorState = !mcp.digitalRead(i + 11);
    right_value |= (sensorState << i);

  }


  // Keer de bitvolgorde voor de rechter sensoren om:
  right_value = swapValues(right_value);

 
  // Bereken lijnpositie (verschil)
  int line = right_value - left_value; // bereik -31 tot +31

    if ((right_value & 0b00001) == 0b00001 || (left_value & 0b10000) == 0b10000) {
      line *= 1.8;  // Versterk de correctie als een buitenste sensor geactiveerd is
  }

   if ((left_value & 0b10000) == 0b10000) {

    line *= 1.8;  // Versterk de correctie aan de linkerkant

  }

  line = map(line, -31, 31, -1700, 1700);


  // Bepaal motor PWM-waarden met een basis snelheid
  int baseSpeed = 2048;
  int leftSpeed = constrain(baseSpeed - line, baseSpeed, 4095);
  int rightSpeed = constrain(baseSpeed + line, baseSpeed, 4095);

  if (left_value == 0 && right_value == 0) {

    Serial.println("Geen lijn gedetecteerd, stoppen.");
    pwm.setPWM(leftEneable, 0, 4095);
    pwm.setPWM(rightEneable, 0, 4095);
    delay(100);
    return;

  }




 
  // Motor Control
  pwm.setPWM(leftMotor, 0, leftSpeed);
  pwm.setPWM(rightMotor, 0, rightSpeed);
  pwm.setPWM(leftFR, 0, 0);                                          
  pwm.setPWM(rightFR, 0, 4095);                                        
  pwm.setPWM(leftEneable, 4095, 0);
  pwm.setPWM(rightEneable, 4095, 0);
 

}

#endif
