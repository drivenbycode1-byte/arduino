#include "arduino_secrets.h"

int trigPin = 9;   // TRIG en D9 (shield)
int echoPin = 8;   // ECHO en D8 (shield)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  long d = medirDistancia();
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.println(" cm");
  delay(300);
}
