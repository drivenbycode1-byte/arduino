#include "arduino_secrets.h"

int switchState = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  switchState = digitalRead(2);

  if (switchState == LOW) {
    //El pulsador no estÃ¡ presionado
    digitalWrite(3, HIGH); //LED azul
    digitalWrite(4, LOW); //LED rojo
    digitalWrite(5, LOW); //LED rojo
  }

  else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);

    delay(250); //en pausa 1/4 de segundo - cambiar estado de los LEDs
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(250); //en pausa 1/4 de segundo
  }
} //Volver al comienzo de la instrucciÃ³n loop
