//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//define the pins used as outputs
#define PIN_TO_READ_BLUE 21  // Pin do odczytu dioda niebieska
#define PIN_TO_READ_RED 22   // Pin do odczytu dioda czerwona 1
#define PIN_TO_READ_GREEN 0   // Pin do odczytu dioda zielona
#define PIN_TO_READ_RED2 4   // Pin do odczytu dioda czerwona 2

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
  pinMode(PIN_TO_READ_BLUE, OUTPUT);
  pinMode(PIN_TO_READ_RED, OUTPUT);
  pinMode(PIN_TO_READ_GREEN, OUTPUT);
  pinMode(PIN_TO_READ_RED2, OUTPUT);
  digitalWrite(PIN_TO_READ_BLUE, LOW); // Zapal pin 21 (dioda niebieska)
  digitalWrite(PIN_TO_READ_RED, LOW);   // Wyłącz pin 22 (dioda czerwona 1)
  digitalWrite(PIN_TO_READ_GREEN, LOW); // Zapal pin 21 (dioda niebieska)
  digitalWrite(PIN_TO_READ_RED2, LOW);   // Wyłącz pin 22 (dioda czerwona 1)



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
        digitalWrite(PIN_TO_READ_BLUE, HIGH); // Zapal pin 21 (dioda niebieska)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoDrive") {
        digitalWrite(PIN_TO_READ_BLUE, LOW);   // Wyłącz pin 21 (dioda niebieska)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "Left") {
        digitalWrite(PIN_TO_READ_RED, HIGH);   // Zapal pin 22 (dioda czerwona1)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoLeft") {
        digitalWrite(PIN_TO_READ_RED, LOW);   // Wyłącz pin 22 (dioda czerwona1)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "Right") {
        digitalWrite(PIN_TO_READ_GREEN, HIGH);   // Zapal pin 0 (dioda zielona)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoRight") {
        digitalWrite(PIN_TO_READ_GREEN, LOW);   // Wyłącz pin 0 (dioda zielona)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "Reverse") {
        digitalWrite(PIN_TO_READ_RED2, HIGH);   // Zapal pin 4 (dioda czerwona2)
        Serial.print(LoRaMessage);
      } else if (LoRaMessage == "NoReverse") {
        digitalWrite(PIN_TO_READ_RED2, LOW);   // Wyłącz pin 4 (dioda czerwona2)
        Serial.print(LoRaMessage);
      }

    // increment packet counter
//    counter++;
//    Serial.print(", Packet number: ");
//    Serial.println(counter);
      }
  
      }
      }

//void loop() {
//  int packetSize = LoRa.parsePacket();
//  if (packetSize) {////////////////////////////////////////
//    String receivedMessage = "";
//
//    while (LoRa.available()) {
//      receivedMessage += (char)LoRa.read();
//    }
//
//    // Wyodrębnij wiadomość "hello" lub "nohello"
//    String message = "";
//    int newLineIndex = receivedMessage.indexOf('\n');
//    if (newLineIndex != -1) {
//      message = receivedMessage.substring(0, newLineIndex);
//    }
//
//    Serial.print("Odebrano wiadomość: ");
//    Serial.println(message);
//
//    // Wyodrębnij numer paczki
//    String packetNumberStr = receivedMessage.substring(newLineIndex + 1);
//    int packetNumber = packetNumberStr.toInt();
//
//    Serial.print("Numer paczki: ");
//    Serial.println(packetNumber);
//
//    // Tutaj możesz dodać kod, który obsłuży odebraną wiadomość lub numer paczki w odpowiedni sposób.
//
//    // Następnie możesz dodać instrukcje warunkowe, aby podejmować działania w zależności od otrzymanej wiadomości lub numeru paczki.
//    // Na przykład:
//    if (message == "hello") {
//      Serial.println("Odebrano wiadomość 'hello'");
//      // Dodaj tutaj kod, który wykonuje się po odebraniu wiadomości 'hello'
//    } else if (message == "nohello") {
//      Serial.println("Odebrano wiadomość 'nohello'");
//      // Dodaj tutaj kod, który wykonuje się po odebraniu wiadomości 'nohello'
//    } else {
//      Serial.println("Nieznana wiadomość");
//      // Dodaj tutaj kod, który wykonuje się w przypadku otrzymania innej wiadomości
//    }
//  }
//}
