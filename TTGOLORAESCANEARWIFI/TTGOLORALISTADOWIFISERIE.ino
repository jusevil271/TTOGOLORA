#include <WiFi.h>

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
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));          // Network name (SSID)
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));          // Signal strength (RSSI)
      Serial.print(" dBm)");
      Serial.print(" [Channel ");
      Serial.print(WiFi.channel(i));       // Wi-Fi channel
      Serial.println("]");
      delay(10); // Small delay between printing each network
    }
  }
  Serial.println();
  delay(5000); // Wait 5 seconds before scanning again
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

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
  delay(60000); // Wait 60 seconds before scanning again
}
