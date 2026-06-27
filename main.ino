#include "thingProperties.h"

#define LED_VERMELHO_1 25
#define LED_VERMELHO_2 26
#define LED_VERDE 27

unsigned long tempoAnterior = 0;
int etapa = 0;

const unsigned long TEMPO_VERMELHO_1 = 2000;
const unsigned long TEMPO_VERMELHO_2 = 2000;
const unsigned long TEMPO_VERDE = 2000;
const unsigned long TEMPO_DOIS_VERMELHOS = 2000;
const unsigned long TEMPO_TODOS = 2000;
const unsigned long TEMPO_DESLIGADOS = 2000;

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(LED_VERMELHO_1, OUTPUT);
  pinMode(LED_VERMELHO_2, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  digitalWrite(LED_VERMELHO_1, LOW);
  digitalWrite(LED_VERMELHO_2, LOW);
  digitalWrite(LED_VERDE, LOW);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Serial.println("=================================");
  Serial.println("Teste dos 3 LEDs iniciado - Arduino Cloud");
  Serial.println("LED vermelho 1: GPIO 25");
  Serial.println("LED vermelho 2: GPIO 26");
  Serial.println("LED verde: GPIO 27");
  Serial.println("=================================");

  tempoAnterior = millis();
}

void loop() {
  ArduinoCloud.update();

  unsigned long tempoAtual = millis();

  switch (etapa) {
    case 0:
      Serial.println("Ligando LED VERMELHO 1 - GPIO 25");

      digitalWrite(LED_VERMELHO_1, HIGH);
      digitalWrite(LED_VERMELHO_2, LOW);
      digitalWrite(LED_VERDE, LOW);

      etapa = 1;
      tempoAnterior = tempoAtual;
      break;

    case 1:
      if (tempoAtual - tempoAnterior >= TEMPO_VERMELHO_1) {
        Serial.println("Ligando LED VERMELHO 2 - GPIO 26");

        digitalWrite(LED_VERMELHO_1, LOW);
        digitalWrite(LED_VERMELHO_2, HIGH);
        digitalWrite(LED_VERDE, LOW);

        etapa = 2;
        tempoAnterior = tempoAtual;
      }
      break;

    case 2:
      if (tempoAtual - tempoAnterior >= TEMPO_VERMELHO_2) {
        Serial.println("Ligando LED VERDE - GPIO 27");

        digitalWrite(LED_VERMELHO_1, LOW);
        digitalWrite(LED_VERMELHO_2, LOW);
        digitalWrite(LED_VERDE, HIGH);

        etapa = 3;
        tempoAnterior = tempoAtual;
      }
      break;

    case 3:
      if (tempoAtual - tempoAnterior >= TEMPO_VERDE) {
        Serial.println("Ligando os DOIS VERMELHOS");

        digitalWrite(LED_VERMELHO_1, HIGH);
        digitalWrite(LED_VERMELHO_2, HIGH);
        digitalWrite(LED_VERDE, LOW);

        etapa = 4;
        tempoAnterior = tempoAtual;
      }
      break;

    case 4:
      if (tempoAtual - tempoAnterior >= TEMPO_DOIS_VERMELHOS) {
        Serial.println("Ligando TODOS os LEDs");

        digitalWrite(LED_VERMELHO_1, HIGH);
        digitalWrite(LED_VERMELHO_2, HIGH);
        digitalWrite(LED_VERDE, HIGH);

        etapa = 5;
        tempoAnterior = tempoAtual;
      }
      break;

    case 5:
      if (tempoAtual - tempoAnterior >= TEMPO_TODOS) {
        Serial.println("Desligando TODOS os LEDs");

        digitalWrite(LED_VERMELHO_1, LOW);
        digitalWrite(LED_VERMELHO_2, LOW);
        digitalWrite(LED_VERDE, LOW);

        etapa = 6;
        tempoAnterior = tempoAtual;
      }
      break;

    case 6:
      if (tempoAtual - tempoAnterior >= TEMPO_DESLIGADOS) {
        Serial.println("---------------------------------");

        etapa = 0;
        tempoAnterior = tempoAtual;
      }
      break;
  }
}
