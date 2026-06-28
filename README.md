# 🚦 Semáforo de Pedestres Inteligente - IoT

Este projeto consiste em um **Semáforo de Pedestres Inteligente** desenvolvido com o ecossistema **ESP32** e integrado ao **Arduino IoT Cloud**. O sistema monitora a presença de pedestres na calçada através de um sensor ultrassônico, automatiza a abertura/fechamento da via para os veículos e envia métricas em tempo real para um dashboard na nuvem.

## 🧠 Como Funciona a Lógica?
* **Estado Padrão:** A via permanece **Verde** para a passagem contínua de veículos.
* **Detecção:** Quando o sensor ultrassônico detecta um pedestre aguardando na calçada (proximidade menor que 15 cm), o sinal fecha (**Vermelho**) imediatamente para os carros.
* **Métrica de Tráfego:** A cada fechamento gerado por um novo pedestre, o sistema soma `+1` a um contador acumulativo.
* **Travessia Segura:** Após o pedestre sair do campo de visão do sensor, o sistema aguarda um tempo de segurança (3 segundos simulados) para que a travessia termine antes de reabrir a via para o sinal **Verde**.

---

## 🛠️ Componentes Utilizados

* **Microcontrolador:** ESP32 Dev Module
* **Sensor de Proximidade:** Sensor Ultrassônico HC-SR04
* **Indicadores Físicos:** 1x LED Vermelho e 1x LED Verde
* **Plataforma IoT:** Arduino IoT Cloud

### 📌 Pinagem (Mapeamento de GPIOs)

| Componente | Pino no ESP32 | Tipo |
| :--- | :---: | :---: |
| **LED Vermelho** | GPIO 12 | Saída (Output) |
| **LED Verde** | GPIO 14 | Saída (Output) |
| **Sensor Trig** | GPIO 27 | Saída (Output) |
| **Sensor Echo** | GPIO 26 | Entrada (Input) |

---

## ☁️ Integração com Arduino IoT Cloud

O dispositivo se conecta à internet via Wi-Fi e sincroniza três variáveis de nuvem cruciais em tempo real para o monitoramento remoto:

1. `distancia` (*Float*): Monitora a aproximação física do pedestre em centímetros.
2. `semaforoFechado` (*Boolean*): Informa o status atual do sinal da via (Verdadeiro para FECHADO / Falso para ABERTO).
3. `contadorFechamentos` (*Integer*): Armazena a quantidade total de pedestres que solicitaram a travessia.

### 🎛️ Dashboard Visual
O painel de controle na nuvem foi configurado com os seguintes widgets:
* **Status Widget:** Um indicador visual dinâmico que alterna entre as cores **Verde** (Via Liberada) e **Vermelho** (Pedestre Atravessando).
* **Value Widget:** Exibe o contador acumulativo de pedestres.
* **Gauge Widget:** Mostra graficamente a distância do pedestre até o sensor.

---

## 🚀 Como Executar o Projeto

1. Monte o circuito físico seguindo a tabela de pinagem.
2. Acesse o [Arduino IoT Cloud](https://cloud.arduino.cc/) e crie um novo **Device** para o seu ESP32.
3. Crie uma **Thing** e adicione as três variáveis (`distancia`, `semaforoFechado`, `contadorFechamentos`) com a permissão *Read Only*.
4. Configure as credenciais da sua rede Wi-Fi e insira a *Secret Key* gerada pelo seu dispositivo.
5. Copie o código fonte do arquivo principal deste repositório e cole na aba *Sketch* do editor web.
6. Faça o upload do código para a placa utilizando o *Arduino Cloud Agent*.
