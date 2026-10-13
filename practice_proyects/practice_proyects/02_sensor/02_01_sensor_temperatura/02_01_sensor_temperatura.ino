#include "arduino_secrets.h"

const int pin_del_sensor = A0;
const float temperatura_de_referencia = 20.0;  // valor fijo, NO calibraciÃ³n

void setup() {
  Serial.begin(9600); // abrir el puerto serie

  for (int numeroPin = 2; numeroPin < 5; numeroPin++) {
    pinMode(numeroPin, OUTPUT);
    digitalWrite(numeroPin, LOW);
  }
}

void loop() {
  int valor_del_sensor = analogRead(pin_del_sensor);

  Serial.print("Valor del sensor: ");
  Serial.print(valor_del_sensor);

  // convertir la lectura ADC a tensiÃ³n
  float tension = (valor_del_sensor / 1023.0) * 5.0;

  Serial.print(", Voltios: ");
  Serial.print(tension);
  Serial.print(", grados C: ");

  // convertir la tensiÃ³n en temperatura (LM35: 10mV por grado)
  float temperatura = tension * 100.0;

  Serial.println(temperatura);

  if (temperatura < temperatura_de_referencia) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);

  } else if (temperatura >= temperatura_de_referencia + 2 &&
             temperatura < temperatura_de_referencia + 4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);

  } else if (temperatura >= temperatura_de_referencia + 4 &&
             temperatura < temperatura_de_referencia + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);

  } else if (temperatura >= temperatura_de_referencia + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  delay(100);
}

