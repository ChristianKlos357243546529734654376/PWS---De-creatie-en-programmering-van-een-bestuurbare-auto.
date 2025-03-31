#include <AFMotor.h>
#include <SoftwareSerial.h>

// Legt communicatie neer tussen de Arduino Nano en de Arduino Uno met de naam 'rfSerial', deze zet de RF signalen automatisch terug in iets wat de auto kan gebruiken
SoftwareSerial rfSerial(15, 16);

// Stelt in de L283 Motor driver Shield welke motoren aan te voeren zijn met welke pins (overgenomen van Alicja Zurek's Code)
AF_DCMotor motor1(1); 
AF_DCMotor motor3(3);

// Variabelen voor timing
unsigned long previousMillis = 0;
unsigned long interval = 1; // 1 ms interval voor motor3 PWM controle
bool motor3On = false;
char currentCommand = '0';

// Begint communicatie met de Arduino Nano
void setup() { 
  rfSerial.begin(9600);
  rfSerial.println("Motor test");

  motor1.setSpeed(200); 
  motor1.run(RELEASE); 
  motor3.setSpeed(255); 
  motor3.run(RELEASE);
}

// deze loop kijkt constant of er signalen via rfSerial zijn binnengekomen, als dat zo is, zet het via een 'Switch Case' statement (Een soort if-else) de signalen om in de drijving van de motoren.
void loop() {
  if (rfSerial.available() > 0) { 
    char command = rfSerial.read(); 
    Serial.print("Received command: ");
    Serial.println(command);
    currentCommand = command;
    
    switch (command) {
      case '0':
        motor1.run(RELEASE);
        motor3.run(RELEASE);
        break;
      case '1':
        motor1.run(FORWARD);
        break;
      case '2':
        motor1.run(FORWARD);
        break;
      case '3':
        motor1.run(FORWARD);
        break;
      case '4':
        motor1.run(BACKWARD);
        break;
      case '5':
        motor1.run(BACKWARD);
        break;
      case '6':
        motor1.run(BACKWARD);
        break;
      case '7':
        motor1.run(RELEASE);
        break;
      case '8':
        motor1.run(RELEASE);
        break;
    }
  }

  // PWM controle voor motor3
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (currentCommand == '1' || currentCommand == '4' || currentCommand == '7') {
      motor3On = !motor3On;
      motor3.run(motor3On ? FORWARD : RELEASE);
    } else if (currentCommand == '2' || currentCommand == '5' || currentCommand == '8') {
      motor3On = !motor3On;
      motor3.run(motor3On ? BACKWARD : RELEASE);
    } else {
      motor3.run(RELEASE);
    }
  }
}