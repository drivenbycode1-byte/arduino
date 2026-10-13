#include "arduino_secrets.h"

int modo = 0;
int estadoActual = HIGH;
int estadoAnterior = HIGH;

void setup() {
  pinMode(3, OUTPUT); // LED azul
  pinMode(4, OUTPUT); // LED rojo 1
  pinMode(5, OUTPUT); // LED rojo 2
  pinMode(2, INPUT_PULLUP); // BotÃ³n con pull-up interno

  // AnimaciÃ³n de bienvenida
  for (int i = 0; i < 2; i++) {
    digitalWrite(4, HIGH);
    delay(150);
    digitalWrite(5, HIGH);
    delay(150);
    digitalWrite(3, HIGH);
    delay(150);

    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
    delay(150);
  }
}

void loop() {
  estadoActual = digitalRead(2);

  // Detectar pulsaciÃ³n (flanco descendente)
  if (estadoAnterior == HIGH && estadoActual == LOW) {
    modo++;
    if (modo > 3) modo = 0;
    delay(200); // anti-rebote
  }

  estadoAnterior = estadoActual;

  // --- MODOS ---

  if (modo == 0) {
    // MODO 0: Reposo
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

  else if (modo == 1) {
    // MODO 1: Alerta (parpadeo rojo)
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(200);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(200);
  }

  else if (modo == 2) {
    // MODO 2: Nave espacial (secuencia tipo scanner)
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(150);

    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(150);

    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(150);
  }

  else if (modo == 3) {
    // MODO 3: Motor warp (parpadeo rÃ¡pido alternado)
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(80);

    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(80);
  }
}