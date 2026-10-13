#include "arduino_secrets.h"

#include <Servo.h>

Servo MiServo;

int anguloActual = 0;     // Donde estÃ¡ el servo ahora
int anguloObjetivo = 0;   // Donde queremos que llegue

void setup() {
  MiServo.attach(9);
}

void moverSuave(int objetivo) {
  anguloObjetivo = objetivo;

  // Movimiento suave
  while (anguloActual != anguloObjetivo) {
    if (anguloActual < anguloObjetivo) anguloActual++;
    if (anguloActual > anguloObjetivo) anguloActual--;

    MiServo.write(anguloActual);
    delay(10);  // velocidad del movimiento
  }
}

void loop() {
  moverSuave(0);
  delay(1000);

  moverSuave(90);
  delay(1000);

  moverSuave(180);
  delay(1000);

  moverSuave(90);
  delay(1000);
}
