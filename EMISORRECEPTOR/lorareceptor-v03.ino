#include <SPI.h>
#include <LoRa.h>

#define SS 18
#define RST 14
#define DI0 26

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  // Configurar pines LoRa
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // Intentar recibir un paquete
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Recibir paquete
    Serial.print("Received packet '");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
