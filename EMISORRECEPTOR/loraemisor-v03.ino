#include <SPI.h>
#include <LoRa.h>

#define SS 18
#define RST 14
#define DI0 26

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  // Configurar pines LoRa
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println("Hello World!");

  // Enviar paquete
  LoRa.beginPacket();
  LoRa.print("Hello World!");
  LoRa.endPacket();

  delay(1000);
}
