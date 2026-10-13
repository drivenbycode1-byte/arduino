#include "arduino_secrets.h"

#include <Servo.h>

Servo cabeza;

// Pines del sensor
int trigPin = 4;
int echoPin = 7;

// Pines del L298N
int IN1 = 8;   // Motor A
int IN2 = 9;
int IN3 = 10;  // Motor B
int IN4 = 11;

// FunciÃ³n para medir distancia
long medirDistancia() {a 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);
  long distancia = duracion * 0.034 / 2;

  if (distancia > 400) distancia = 400;  // filtro anti-ruido

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

void setup() {
  Serial.begin(9600);

  cabeza.attach(3);   // Servo en D3
  cabeza.write(90);   // Centro

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Robot explorador iniciado...");
}

void loop() {

  // Mirar al centro
  cabeza.write(90);
  delay(500);
  long centro = medirDistancia();
  Serial.print("Centro: ");
  Serial.println(centro);

  // Si hay obstÃ¡culo cerca, detener y decidir
  if (centro < 25) {
    detener();
    delay(300);

    // Mirar izquierda
    cabeza.write(20);
    delay(600);
    long izquierda = medirDistancia();
    Serial.print("Izquierda: ");
    Serial.println(izquierda);

    // Mirar derecha
    cabeza.write(160);
    delay(600);
    long derecha = medirDistancia();
    Serial.print("Derecha: ");
    Serial.println(derecha);

    // Elegir el camino mÃ¡s libre 
    if (izquierda > derecha) {
      Serial.println("Girando a la izquierda...");
      girarIzquierda();
      delay(500);
    } else {
      Serial.println("Girando a la derecha...");
      girarDerecha();
      delay(500);
    }

    detener();
    delay(200);
  } else {
    // Avanzar si no hay obstÃ¡culo
    avanzar();
  }

  delay(100);
}

