#ifndef Display_h
#define Display_h

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include "StroomSensor.h"

Adafruit_SSD1305 display(128, 64, &Wire);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 0
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 32 
#define LOGO16_GLCD_WIDTH  32 
static const unsigned char PROGMEM logo32bmp[] =
{ B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000011, B11000000,
  B00000000, B00000000, B00000011, B11000000,
  B00000000, B00000000, B00001100, B00110000,
  B00000000, B00000000, B00001100, B00110000,
  B00000000, B00000000, B00110000, B00001100,
  B00000000, B00000000, B00110000, B00001100,
  B00000000, B00000000, B11000011, B00001100,
  B00000000, B00000000, B11000011, B00001100,
  B00000000, B00000011, B00000000, B00001100,
  B00000000, B00000011, B00000000, B00001100,
  B00000000, B00001100, B00000000, B00001100,
  B00000000, B00001100, B00001100, B00001100,
  B00000000, B00110000, B00001100, B00001100,
  B00000000, B00110000, B00000000, B00001100,
  B00000000, B11000000, B00000000, B00001100,
  B00000000, B11000000, B00000000, B00001100,
  B00000011, B00000011, B00000000, B00001100,
  B00000011, B00000011, B00000000, B00001100,
  B00001100, B00110000, B00000000, B00110000,
  B00001100, B00110000, B00000000, B00110000,
  B00110000, B00000000, B00000000, B00110000,
  B00110000, B00000000, B00000000, B00110000,
  B00110000, B00000000, B00000000, B11000000,
  B00110000, B00000000, B00000000, B11000000,
  B00001100, B00000000, B00001111, B00000000,
  B00001100, B00000000, B00001111, B00000000,
  B00000011, B11111111, B11110000, B00000000,
  B00000011, B11111111, B11110000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000 };

void displaySetup(){
  if ( ! display.begin(0x3C) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.drawBitmap(64, 16,  logo32bmp, 32, 32, 1);
  display.display();
  delay(100);
}

void displayLoop(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Power in: ");
  display.print(powerIn);
  display.println(" W");

  display.setCursor(0,10);
  display.print("Power out: ");
  display.print(powerOut);
  display.println(" W");

  display.setCursor(0,20);
  display.print("Voltage out: ");
  display.print(voltageOut);
  display.println(" V");

  display.setCursor(0,30);
  display.print("Current out: ");
  display.print(currentOut);
  display.println(" A");

  display.setCursor(0,40);
  display.print("Temp out: ");
  display.print(tempOut);
  display.println(" *C");

  display.setCursor(0,50);
  display.print("Temp in: ");
  display.print(tempIn);
  display.println(" *C");

  display.display();

}


#endif