//Librarier for Bluetooth
#include "BluetoothSerial.h"
//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>





//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26


#define BAND 868E6

//Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Bluetooth Serial object
BluetoothSerial SerialBT;



// Handle received and sent messages
String BTmessage = "";
char incomingChar;



void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  delay(1000);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  delay(1000);
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  delay(2000);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Sender Test");
  Serial.println("LoRa Initializing OK!");
  
 
 
 
}
void loop() {
//  Serial.println("Sending packet: ");
//  Serial.println(counter);
  
  // Read received messages (LED control command)
  if (SerialBT.available()){

    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      BTmessage += String(incomingChar);
    }
    else{
      BTmessage = "";
    }
    Serial.write(incomingChar);
    

  };  
  if (BTmessage =="Drive"){
    LoRaSendDrive();
    BTmessage = "";
  }
  else if (BTmessage =="NothingDrive"){
    LoRaSendNoDrive();
    BTmessage = "";
  }
  else if (BTmessage =="Left"){
    LoRaSendLeft();
    BTmessage = "";
  }
  else if (BTmessage =="NothingLeft"){
    LoRaSendNoLeft(); 
    BTmessage = "";
  }
  else if (BTmessage =="Right"){
    LoRaSendRight();
    BTmessage = "";
  }
  else if (BTmessage =="NothingRight"){
    LoRaSendNoRight();
    BTmessage = "";
  }
  else if (BTmessage =="Reverse"){
    
    LoRaSendReverse();
    BTmessage = "";
  }
  else if (BTmessage =="NothingReverse"){
    LoRaSendNoReverse();
    BTmessage = "";
  }

}




////Functions for sending commans by LoRa 
void LoRaSendDrive() {
  String LoRaMessage = "Drive";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendNoDrive() {
  String LoRaMessage = "NoDrive";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendLeft() {
  String LoRaMessage = "Left";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendNoLeft() {
  String LoRaMessage = "NoLeft";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendRight() {
  String LoRaMessage = "Right";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendNoRight() {
  String LoRaMessage = "NoRight";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendReverse() {
  String LoRaMessage = "Reverse";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}

void LoRaSendNoReverse() {
  String LoRaMessage = "NoReverse";
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  Serial.println("Wysłano wiadomość: " + LoRaMessage);
  
}
