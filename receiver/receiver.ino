//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//define the pins used as outputs
#define PIN_TO_READ_BLUE 21  // Pin to read blue diode
#define PIN_TO_READ_RED 22   // Pin to read red diode 1
#define PIN_TO_READ_GREEN 0   // Pin to read diode green
#define PIN_TO_READ_RED2 4   // Pin to read diode red 2

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

#define BAND 868E6

//packet counter
//int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  //defining pins as outputs
  pinMode(PIN_TO_READ_BLUE, OUTPUT);
  pinMode(PIN_TO_READ_RED, OUTPUT);
  pinMode(PIN_TO_READ_GREEN, OUTPUT);
  pinMode(PIN_TO_READ_RED2, OUTPUT);
  //setting initial states to low
  digitalWrite(PIN_TO_READ_BLUE, LOW); // set low pin 21 (blue diode)
  digitalWrite(PIN_TO_READ_RED, LOW);   // set low pin 22 (red diode)
  digitalWrite(PIN_TO_READ_GREEN, LOW); // set low pin 21 (green diode)
  digitalWrite(PIN_TO_READ_RED2, LOW);   // set low pin 22 (red diode 2)



  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  delay(2000);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Receiver Test");
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet: ");

    // read packet
    while (LoRa.available()) {
      String LoRaMessage = LoRa.readString();
      //Serial.print(message);

      // Check the message and control the pins
      if (LoRaMessage == "Drive") {
        digitalWrite(PIN_TO_READ_BLUE, HIGH); // Set High pin 21 (blue diode)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoDrive") {
        digitalWrite(PIN_TO_READ_BLUE, LOW);   // Set Low 21 (blue diode)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "Left") {
        digitalWrite(PIN_TO_READ_RED, HIGH);   // Set High 22 (red diode 1)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoLeft") {
        digitalWrite(PIN_TO_READ_RED, LOW);   // Set Low 22 (red diode 1)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "Right") {
        digitalWrite(PIN_TO_READ_GREEN, HIGH);   // Set High 0 (green diode )
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoRight") {
        digitalWrite(PIN_TO_READ_GREEN, LOW);   // Set Low 0 (green diode)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "Reverse") {
        digitalWrite(PIN_TO_READ_RED2, HIGH);   // Set High 4 (red diode 2)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoReverse") {
        digitalWrite(PIN_TO_READ_RED2, LOW);   // Set Low 4 (red diode 2)
        Serial.print(LoRaMessage);
      }

    // increment packet counter
//    counter++;
//    Serial.print(", Packet number: ");
//    Serial.println(counter);
      }
  
      }
      }
