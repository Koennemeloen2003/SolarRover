#include <Wire.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

bool sensorstat[10] = {false, false, false, false, false, false, false, false, false, false};

void linetrackersetup() {
  //Serial.begin(9600);  // Using a higher baud rate for better performance on ESP32

  // Initialize I2C (default ESP32 pins: SDA=21, SCL=22)
  //Wire.begin(16, 17);  // Specify SDA and SCL pins if different from the default

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
    } else {
      sensorstat[0] = false;
  }

  if (sensor1 == LOW) {
      sensorstat[1] = true;
    } else {
      sensorstat[1] = false;
  }

  if (sensor2 == LOW) {
      sensorstat[2] = true;
    } else {
      sensorstat[2] = false;
  }

  if (sensor3 == LOW) {
      sensorstat[3] = true;
    } else {
      sensorstat[3] = false;
  }

  if (sensor4 == LOW) {
      sensorstat[4] = true;
    } else {
      sensorstat[4] = false;
  }

  if (sensor5 == LOW) {
      sensorstat[5] = true;
    } else {
      sensorstat[5] = false;
  }

  if (sensor6 == LOW) {
      sensorstat[6] = true;
    } else {
      sensorstat[6] = false;
  }

  if (sensor7 == LOW) {
      sensorstat[7] = true;
    } else {
      sensorstat[7] = false;
  }

  if (sensor8 == LOW) {
      sensorstat[8] = true;
    } else {
      sensorstat[8] = false;
  }

  if (sensor9 == LOW) {
      sensorstat[9] = true;
    } else {
      sensorstat[9] = false;
  }

  for (int i = 0; i < 10; i++) {
    Serial.print(sensorstat[i] ? "[X]" : "[ ]");
  }
  Serial.println("");


  if ((sensorstat[0] == true && sensorstat[1] == false && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false && sensorstat[8] == false && sensorstat[9] == false)||(sensorstat[1] == true && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false && sensorstat[8] == false && sensorstat[9] == false)) {
    Serial.println("Stuur naar rechts");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 2000);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 500);
      pwm.setPWM(rightFR, 0, 4095);
  }
  else if (sensorstat[2] == true && sensorstat[6] == false && sensorstat[4] == false && sensorstat[5] == false  && sensorstat[7] == false && sensorstat[8] == false && sensorstat[9] == false) {
     Serial.println("Stuur minder ver naar rechts");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 1000);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 500);
      pwm.setPWM(rightFR, 0, 4095);
  }

  else if (sensorstat[7] == true && sensorstat[0] == false && sensorstat[1] == false && sensorstat[2] == false  && sensorstat[4] == false && sensorstat[5] == false && sensorstat[3] == false) {
    Serial.println("Stuur minder ver naar links");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 500);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 1000);
      pwm.setPWM(rightFR, 0, 4095);
  }
  else if (sensorstat[8] == true && sensorstat[0] == false && sensorstat[1] == false && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false) {
    Serial.println("Stuur naar links");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 500);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 2000);
      pwm.setPWM(rightFR, 0, 4095);

  }
  else if (sensorstat[9] == true && sensorstat[0] == false && sensorstat[1] == false && sensorstat[2] == false && sensorstat[3] == false && sensorstat[4] == false && sensorstat[5] == false && sensorstat[6] == false && sensorstat[7] == false && sensorstat[8] == false) {
    Serial.println("Stuur naar links");
    pwm.setPWM(leftEneable, 0, 0);
      pwm.setPWM(rightEneable, 0, 0);
      pwm.setPWM(leftMotor, 0, 500);
      pwm.setPWM(leftFR, 0, 0);
      pwm.setPWM(rightMotor, 0, 2000);
      pwm.setPWM(rightFR, 0, 4095);
  }
  else if ((sensorstat[3] == true || sensorstat[4] == true || sensorstat[5] == true || sensorstat[6] == true) && sensorstat[7] == false && sensorstat[2]== false) { //stuur niet
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
