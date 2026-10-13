#include "arduino_secrets.h"

#include <Servo.h>

Servo cabeza;

int trigPin = 9;   // TRIG en D9
int echoPin = 8;   // ECHO en D8

void setup() {
  Serial.begin(9600);

  cabeza.attach(3);   // Servo en D3
  cabeza.write(90);   // Centrado

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Escaneo iniciado...");
}

long medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);
  long distancia = duracion * 0.034 / 2;

  return distancia;
}

void loop() {

  // Centro
  cabeza.write(90);
  delay(400);
  Serial.print("Centro: ");
  Serial.print(medirDistancia());
  Serial.println(" cm");

  // Izquierda
  cabeza.write(20);
  delay(400);
  Serial.print("Izquierda: ");
  Serial.print(medirDistancia());
  Serial.println(" cm");

  // Derecha
  cabeza.write(160);
  delay(400);
  Serial.print("Derecha: ");
  Serial.print(medirDistancia());
  Serial.println(" cm");

  Serial.println("------------------------");
  delay(800);
}
