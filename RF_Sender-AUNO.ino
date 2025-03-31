#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Definieert welke pins gebruikt worden voor communicatie tussen de Arduino Uno en de NRF24L01, in deze geval Pin 9 en 10.
#define CE_PIN 9
#define CSN_PIN 10

// Legt de link op tussen de Arduino Uno en de NRF24L01.
RF24 radio(CE_PIN, CSN_PIN);
const uint64_t pipe = 0x1;

// Definieert de link tussen zowel de laptop (via Serial) als hoe de NRF24L01 signalen moet uit sturen.
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

// De loop waarbij de commando's ontvangen worden via Serial, en dan door worden gestuurt via RF signalen
void loop() {
  if (Serial.available() > 0) { 
    char command = Serial.read(); 
    Serial.print("Received command: ");
    Serial.println(command);
    radio.write(&command, sizeof(command));
  }
}