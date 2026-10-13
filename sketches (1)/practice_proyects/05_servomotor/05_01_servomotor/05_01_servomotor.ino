#include "arduino_secrets.h"

#include <Servo.h>

Servo MiServo;

const int PinPot = A0;
int ValorPot;
int Angulo;

void setup() {
  MiServo.attach(9);

  Serial.begin(9600);
}

void loop() {
  ValorPot = analogRead(PinPot);
  Serial.print("PosiciÃ³n del potenciÃ³metro: ");
  Serial.println(ValorPot);

  Angulo = map(ValorPot, 0, 1023, 0, 179);
  Serial.print("Ãngulo: ");
  Serial.println(Angulo);

  MiServo.write(Angulo);
  delay(100);
}