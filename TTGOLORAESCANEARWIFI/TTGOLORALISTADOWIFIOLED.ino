#include <WiFi.h>
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"
#include "SSD1306.h"

// TTGO LoRa32-OLED v2.0 and V2.1
// 
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST NOT_A_PIN

SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

// Function to scan and list Wi-Fi networks
void listWiFiNetworks() {
  Serial.println("Scanning for Wi-Fi networks...");

  // Start Wi-Fi scan
  int numNetworks = WiFi.scanNetworks();

  // Check if any networks were found
  if (numNetworks == 0) {
    Serial.println("No networks found.");

  } else {
    Serial.print(numNetworks);
    Serial.println(" networks found:");

    // List the details of each network
    for (int i = 0; i < numNetworks; i++) {
      Serial.print(i + 1);
      display.print(i+1);
      Serial.print(": ");
      display.print(": ");
      Serial.print(WiFi.SSID(i));          // Network name (SSID)
      display.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));          // Signal strength (RSSI)
      display.println(WiFi.RSSI(i));
      Serial.print(" dBm)");
      Serial.print(" [Channel ");
      Serial.print(WiFi.channel(i));       // Wi-Fi channel
      Serial.println("]");
      display.display();
      delay(10); // Small delay between printing each network
    }
  }
  Serial.println();
  delay(5000); // Wait 5 seconds before scanning again
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

    // reset the OLED:
  if (OLED_RST != NOT_A_PIN)
  {
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW); // set GPIO16 low to reset OLED
    delay(50);
    digitalWrite(OLED_RST, HIGH); // while OLED is running, must set GPIO16 in high
  }

  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_10);

  // Initialize Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);

  // Scan and list Wi-Fi networks
  listWiFiNetworks();
}

void loop() {
  // Scan and list Wi-Fi networks every 60 seconds
  listWiFiNetworks();
  delay(10000); // Wait 60 seconds before scanning again
}
