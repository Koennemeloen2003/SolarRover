#include "Display.h"
#include "StroomSensor.h"
#include "Setup.h"
#include "wifi_util.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  timer = millis();
  /*
  INASetup();
  displaySetup();
  */
  if (!wifi_init()) {
    Serial.println("Wi-Fi initialisatie mislukt!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  /*  if(ina228_IN.conversionReady()){
    readINA();
    displayLoop();
  }
  	*/
  if (timer + 1000 < millis()){
   // wifi_send_if_associated(powerIn, 3141592, voltageOut/30 *100);
   wifi_send_if_associated(27182, 3141592, 55);
   timer= millis();
  }
}
