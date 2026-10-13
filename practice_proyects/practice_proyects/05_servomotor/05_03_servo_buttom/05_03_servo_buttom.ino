#include "arduino_secrets.h"

#include <Servo.h>

Servo MiServo;

const int PinBoton = 2;
int estadoServo = 0;

bool estadoBoton;
bool ultimoEstadoBoton = LOW;

unsigned long ultimoTiempo = 0;
const int debounceDelay = 50;

void setup() {
  MiServo.attach(9);
  pinMode(PinBoton, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool lectura = digitalRead(PinBoton);

  if (lectura != ultimoEstadoBoton) {
    ultimoTiempo = millis();
  }

  if ((millis() - ultimoTiempo) > debounceDelay) {
    if (lectura != estadoBoton) {
      estadoBoton = lectura;

      if (estadoBoton == HIGH) {
        estadoServo++;
        if (estadoServo > 2) estadoServo = 0;

        if (estadoServo == 0) MiServo.write(0);
        if (estadoServo == 1) MiServo.write(90);
        if (estadoServo == 2) MiServo.write(180);

        Serial.print("Estado: ");
        Serial.println(estadoServo);
      }
    }
  }

  ultimoEstadoBoton = lectura;
}