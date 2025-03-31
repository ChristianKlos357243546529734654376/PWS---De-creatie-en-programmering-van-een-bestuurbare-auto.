#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

// Legt de pins neer waar de radio signalen worden ontvangen (Bij deze Arduino Nano bord is dat Pin 7 en 8)
RF24 radio(7, 8);
// Legt communicatie neer tussen de Arduino Nano en de Arduino Uno met de naam 'rfSerial', deze zet de RF signalen automatisch terug in iets wat de auto kan gebruiken
SoftwareSerial rfSerial(0, 1);
const uint64_t pipe = 0x1;

// Definieert de link tussen de Arduino Nano en de Arduino van de Auto (met 'rfSerial'), en definieert welke radio signalen de ingebouwde NRF24L01 moet lezen.
void setup() {
  rfSerial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, pipe);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

// // De loop waarbij de RF golven ontvangen worden via de gestuurde signalen, en dan omgezet en door gestuurt worden naar de auto met rfSerial.
void loop() {
  if (radio.available()) {
    char command;
    radio.read(&command, sizeof(command));
    rfSerial.write(command);
  }
}