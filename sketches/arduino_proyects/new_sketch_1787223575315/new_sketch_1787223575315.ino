#include "arduino_secrets.h"

#include <Servo.h>

Servo cabeza;

// Pines del sensor
int trigPin = 4;
int echoPin = 7;

// Pines del L298N
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// Variable para comandos Bluetooth
char comando;

// FunciÃ³n para medir distancia
long medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);
  long distancia = duracion * 0.034 / 2;

  if (distancia > 400) distancia = 400;

  return distancia;
}

// Movimiento del robot
void avanzar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void retroceder() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void girarIzquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void girarDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// FunciÃ³n para recibir comandos Bluetooth
void recibirComando() {
  if (Serial.available()) {
    comando = Serial.read();
    Serial.print("Comando recibido: ");
    Serial.println(comando);

    if (comando == 'A') avanzar();
    if (comando == 'R') retroceder();
    if (comando == 'I') girarIzquierda();
    if (comando == 'D') girarDerecha();
    if (comando == 'S') detener();
  }
}

void setup() {
  Serial.begin(9600);

  cabeza.attach(3);
  cabeza.write(90);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Robot con control Bluetooth listo...");
}

void loop() {

  // MODO MANUAL: si hay comandos Bluetooth, obedecer
  recibirComando();

  // Si no hay comandos, seguir en modo autÃ³nomo
  if (!Serial.available()) {

    cabeza.write(90);
    delay(500);
    long centro = medirDistancia();

    if (centro < 25) {
      detener();
      delay(300);

      cabeza.write(20);
      delay(600);
      long izquierda = medirDistancia();

      cabeza.write(160);
      delay(600);
      long derecha = medirDistancia();

      if (izquierda > derecha) {
        girarIzquierda();
        delay(500);
      } else {
        girarDerecha();
        delay(500);
      }

      detener();
      delay(200);

      cabeza.write(90);
      delay(500);
      long nuevoCentro = medirDistancia();

      if (nuevoCentro < 25) {
        girarIzquierda();
        delay(700);
        detener();
      }

    } else {
      avanzar();
    }
  }

  delay(50);
}
