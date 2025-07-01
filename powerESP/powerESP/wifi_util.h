#include <stdint.h>
#ifndef WIFI_UTIL_H
#define WIFI_UTIL_H

#include <WiFi.h>
#include <WiFiUdp.h>

// Wi-Fi configuratie
const char* WIFI_SSID     = "rover";
const char* WIFI_PASSWORD = "$Ol4r-R0v3r";

// Doeladres voor UDP
const char* ROVERHUB_ADDRESS = "10.83.82.254";
const uint16_t ROVERHUB_PORT = 12345;

// Status bijhouden
bool wifiConnected = false;

// UDP object
WiFiUDP udp;

/**
 * Initialiseer Wi-Fi en verbind met access point.
 * Retourneert true als verbinding is gelukt.
 */
bool wifi_init() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Verbinden met Wi-Fi");
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi verbonden!");
    wifiConnected = true;
    return true;
  } else {
    Serial.println("\nVerbinding mislukt.");
    wifiConnected = false;
    return false;
  }
}

/**
 * Verstuur een UDP-pakket naar het dashboard als Wi-Fi verbonden is.
 *
 * @param color 16-bit kleurwaarde
 * @param value 16-bit sensorwaarde (bijv. 12345 voor 123.45)
 * @param value_decplaces Aantal decimalen achter de komma
 * @return true als verzenden is gelukt
 */
bool wifi_send_if_associated(uint16_t vermogen, int32_t speed, uint8_t battery) {
  if (!wifiConnected) {
    Serial.println("Wi-Fi niet verbonden, verzenden mislukt.");
    return false;
  }

  uint8_t message[32] = {0};

  // Header
  message[0] = 'R';
  message[1] = 'V';
  message[2] = 'H';
  message[3] = 'v';

  message[12] = (speed >> 24) & 0xFF;
  message[13] = (speed >> 16) & 0xFF;
  message[14] = (speed >> 8) & 0xFF;
  message[15] = speed & 0xFF;

  // Color (big-endian)
  message[20] = (vermogen >> 8) & 0xFF;
  message[21] = vermogen & 0xFF;

  // Value (big-endian)
//  message[22] = (value >> 8) & 0xFF;
 // message[23] = value & 0xFF;

  // Decimal places
  message[28] = battery;

  // Verstuur via UDP
  udp.beginPacket(ROVERHUB_ADDRESS, ROVERHUB_PORT);
  udp.write(message, 32);
  int result = udp.endPacket();

  if (result == 1) {
    Serial.println("UDP pakket verzonden.");
    return true;
  } else {
    Serial.println("UDP verzenden mislukt.");
    return false;
  }
}

#endif // WIFI_UTIL_H
