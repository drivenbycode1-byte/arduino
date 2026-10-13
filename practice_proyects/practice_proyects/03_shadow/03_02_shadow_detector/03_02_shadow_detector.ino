#include "arduino_secrets.h"

// Pines del LED RGB
const int PinLedVerde = 9;
const int PinLedRojo  = 11;
const int PinLedAzul  = 10;

// Pines de los LDR
const int PinEntradaLDR_Rojo  = A0;
const int PinEntradaLDR_Verde = A1;
const int PinEntradaLDR_Azul  = A2;

// Variables para lecturas
int ValorSensorRojo  = 0;
int ValorSensorVerde = 0;
int ValorSensorAzul  = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PinLedVerde, OUTPUT);
  pinMode(PinLedRojo,  OUTPUT);
  pinMode(PinLedAzul,  OUTPUT);
}

void loop() {

  // 1. Leer los sensores
  ValorSensorRojo  = analogRead(PinEntradaLDR_Rojo);
  ValorSensorVerde = analogRead(PinEntradaLDR_Verde);
  ValorSensorAzul  = analogRead(PinEntradaLDR_Azul);

  // 2. Mostrar valores en el monitor serial
  Serial.print("Rojo: ");
  Serial.print(ValorSensorRojo);
  Serial.print("  Verde: ");
  Serial.print(ValorSensorVerde);
  Serial.print("  Azul: ");
  Serial.println(ValorSensorAzul);

  // 3. Definir umbral de sombra
  int umbral = 400;   // Ajusta segÃºn tu ambiente

  // 4. Detectar si hay sombra en cada LDR
  bool sombraRojo  = ValorSensorRojo  < umbral;
  bool sombraVerde = ValorSensorVerde < umbral;
  bool sombraAzul  = ValorSensorAzul  < umbral;

  // 5. Inicializar colores del LED
  int R = 0;
  int G = 0;
  int B = 0;

  // 6. Asignar colores segÃºn la sombra detectada
  if (sombraRojo)  R = 255;   // Sombra en LDR rojo â LED rojo
  if (sombraVerde) G = 255;   // Sombra en LDR verde â LED verde
  if (sombraAzul)  B = 255;   // Sombra en LDR azul â LED azul

  // 7. Aplicar color al LED RGB
  analogWrite(PinLedRojo,  R);
  analogWrite(PinLedVerde, G);
  analogWrite(PinLedAzul,  B);

  delay(50); // Suaviza la lectura
}
