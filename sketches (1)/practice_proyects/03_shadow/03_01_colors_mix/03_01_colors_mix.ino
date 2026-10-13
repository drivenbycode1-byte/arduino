#include "arduino_secrets.h"

const int PinLedVerde = 9;
const int PinLedRojo  = 11;
const int PinLedAzul  = 10;

const int PinEntradaLDR_Rojo  = A0;
const int PinEntradaLDR_Verde = A1;
const int PinEntradaLDR_Azul  = A2;

int ValorSensorRojo  = 0;
int ValorSensorVerde = 0;
int ValorSensorAzul  = 0;

int ValorRojo  = 0;
int ValorVerde = 0;
int ValorAzul  = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PinLedVerde, OUTPUT);
  pinMode(PinLedRojo,  OUTPUT);
  pinMode(PinLedAzul,  OUTPUT);
}

void loop() {

  // Lectura de los sensores LDR
  ValorSensorRojo  = analogRead(PinEntradaLDR_Rojo);
  delay(5);
  ValorSensorVerde = analogRead(PinEntradaLDR_Verde);
  delay(5);
  ValorSensorAzul  = analogRead(PinEntradaLDR_Azul);

  // Mostrar valores originales (0â1023)
  Serial.print("Mapa de valores sensores \t Rojo: ");
  Serial.print(ValorSensorRojo);
  Serial.print("\t Verde: ");
  Serial.print(ValorSensorVerde);
  Serial.print("\t Azul: ");
  Serial.println(ValorSensorAzul);

  // Convertir 0â1023 â 0â255
  ValorRojo  = ValorSensorRojo  / 4;
  ValorVerde = ValorSensorVerde / 4;
  ValorAzul  = ValorSensorAzul  / 4;

  // Mostrar valores convertidos (0â255)
  Serial.print("Mapa de valores PWM \t Rojo: ");
  Serial.print(ValorRojo);
  Serial.print("\t Verde: ");
  Serial.print(ValorVerde);
  Serial.print("\t Azul: ");
  Serial.println(ValorAzul);

  // Aplicar PWM a los LEDs
  analogWrite(PinLedRojo,  ValorRojo);
  analogWrite(PinLedVerde, ValorVerde);
    analogWrite(PinLedAzul,  ValorAzul);
}