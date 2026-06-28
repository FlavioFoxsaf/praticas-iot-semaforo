#include "thingProperties.h"

// Definição dos pinos físicos
const int LED_VERMELHO = 12;
const int LED_VERDE = 14;
const int TRIG_PIN = 27;
const int ECHO_PIN = 26;

// Variáveis locais para o cálculo do sensor
long duracao;
float distancia_cm;

// Garante que o contador só soma 1 por pedestre, mesmo se ele ficar parado lá
bool pedestreJaContado = false;

void setup() {
  Serial.begin(115200);
  delay(1500); 

  // Configuração dos pinos
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializa as propriedades do Arduino Cloud
  initProperties();

  // Conecta ao Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Estado Inicial: Sempre VERDE (Via Aberta)
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
  semaforoFechado = false;
  contadorFechamentos = 0;
}

void loop() {
  // Sincroniza os dados com a nuvem
  ArduinoCloud.update();
  
  // Leitura do Sensor Ultrassônico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duracao = pulseIn(ECHO_PIN, HIGH);
  distancia_cm = duracao * 0.0343 / 2;

  // Atualiza a distância na nuvem em tempo real
  distancia = distancia_cm;

  // LÓGICA DO SEMÁFORO DE PEDESTRE
  // Se detectar alguém a menos de 15cm aguardando na calçada
  if (distancia_cm > 0 && distancia_cm < 15) {
    
    // Altera os LEDs físicos: Fecha o sinal para os carros
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    
    // Avisa a nuvem que o semáforo fechou
    semaforoFechado = true;

    // Se é a primeira vez que ele entra na área, soma no contador
    if (!pedestreJaContado) {
      contadorFechamentos++;
      pedestreJaContado = true; // Trava o contador para não ficar somando em loop
      Serial.print("Pedestre detectado! Fechamentos: ");
      Serial.println(contadorFechamentos);
    }
  } 
  // Se a calçada estiver livre (ninguém esperando)
  else {
    // Se o sinal estava fechado, significa que o pedestre começou a atravessar e saiu da frente do sensor
    if (semaforoFechado == true) {
      Serial.println("Pedestre atravessando... Aguardando tempo de segurança para abrir.");
      
      // Espera 3 segundos (tempo para simular a travessia antes do sinal abrir de novo)
      delay(3000); 
      
      // Abre o sinal novamente para os carros
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_VERDE, HIGH);
      
      // Avisa a nuvem que o sinal abriu
      semaforoFechado = false;
      
      // Libera a trava para o próximo pedestre que chegar
      pedestreJaContado = false; 
    }
  }

  delay(100); 
}
