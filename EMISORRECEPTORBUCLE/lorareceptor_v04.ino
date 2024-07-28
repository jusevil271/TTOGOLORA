#include <SPI.h>
#include <LoRa.h>


#define SS 18
#define RST 14
#define DI0 26

//pantalla
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"
#include "SSD1306.h"
// TTGO LoRa32-OLED V1
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST NOT_A_PIN

SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);


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

  //pantalla
  // reset the OLED:
  if (OLED_RST != NOT_A_PIN)
  {
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW); // set GPIO16 low to reset OLED
    delay(50);
    digitalWrite(OLED_RST, HIGH); // while OLED is running, must set GPIO16 in high
  }
  //pantalla
  display.init();
  display.flipScreenVertically();

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Pantalla inicializada");
  display.display();
}

void loop() {
  // Intentar recibir un paquete
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Recibir paquete
    Serial.print("Received packet '");
    
    //while (LoRa.available()) {
    //  Serial.print((char)LoRa.read());
    //}
    String numero;//variable declarado fuera
    while (LoRa.available()) {
    //  Serial.print((char)LoRa.read());
        //String numero="i="+(char)LoRa.read();
        numero=LoRa.readString();
        Serial.print(numero);
    }

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

  //pantalla
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "i="+numero);
  display.display();

  }
}
