#include "arduino_secrets.h"

int modo = 0;
int estadoActual = HIGH;
int estadoAnterior = HIGH;

// Variables para animaciones
unsigned long tiempoAnterior = 0;
unsigned long intervalo = 150;  // tiempo base para animaciones
int paso = 0;  // paso dentro de cada animaciÃ³n

void setup() {
  pinMode(3, OUTPUT); // LED azul
  pinMode(4, OUTPUT); // LED rojo 1
  pinMode(5, OUTPUT); // LED rojo 2
  pinMode(2, INPUT_PULLUP); // BotÃ³n

  // AnimaciÃ³n de bienvenida (puede quedar con delay porque solo corre una vez)
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

  // --- LECTURA DEL BOTÃN (flanco descendente) ---
  estadoActual = digitalRead(2);

  if (estadoAnterior == HIGH && estadoActual == LOW) {
    modo++;
    if (modo > 3) modo = 0;
    paso = 0;  // reiniciar animaciÃ³n al cambiar modo
  }

  estadoAnterior = estadoActual;


  // --- ANIMACIONES NO BLOQUEANTES ---
  unsigned long ahora = millis();

  if (ahora - tiempoAnterior >= intervalo) {
    tiempoAnterior = ahora;

    // --- MODO 0: Reposo ---
    if (modo == 0) {
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }

    // --- MODO 1: Alerta (parpadeo rojo alternado) ---
    else if (modo == 1) {
      if (paso == 0) {
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        paso = 1;
      }
      else {
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        paso = 0;
      }
      intervalo = 200;
    }

    // --- MODO 2: Nave espacial (scanner) ---
    else if (modo == 2) {
      if (paso == 0) {
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        paso = 1;
      }
      else if (paso == 1) {
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        paso = 2;
      }
      else {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        paso = 0;
      }
      intervalo = 150;
    }

    // --- MODO 3: Motor warp (rÃ¡pido alternado) ---
    else if (modo == 3) {
      if (paso == 0) {
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        paso = 1;
      }
      else {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        paso = 0;
      }
      intervalo = 80;
    }
  }
}