#include "Display.h"
#include "StroomSensor.h"
#include "Setup.h"
#include "wifi_util.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  timer = millis();
  timerSerial = millis();
  
  INASetup();
  displaySetup();
  
  if (!wifi_init()) {
    Serial.println("Wi-Fi initialisatie mislukt!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    if(ina228_IN.conversionReady()){
    readINA();
    displayLoop();
  }
  
    if (timerSerial + 100 < millis()){
      if(Serial.available()){
        speed =Serial.parseFloat();
        Serial.println(speed);
      }
   timerSerial= millis();
  }
  	
  if (timer + 500 < millis()){
   wifi_send_if_associated(powerIn, speed, 255*voltageOut/30);
   timer= millis();
  }
}
