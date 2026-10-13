#include "arduino_secrets.h"

#include <Servo.h>

Servo MiServo;

const int PinLDR = A0;
int ValorLuz = 0;
int Angulo;

void setup() {
  MiServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  int lectura = analogRead(PinLDR);

  // Filtro para suavizar la lectura
  ValorLuz = (ValorLuz * 0.7) + (lectura * 0.3);

  Serial.print("Luz: ");
  Serial.println(ValorLuz);

  // CalibraciÃ³n real segÃºn tus mediciones
  Angulo = map(ValorLuz, 2, 200, 0, 179);

  MiServo.write(Angulo);
  delay(50);
}
