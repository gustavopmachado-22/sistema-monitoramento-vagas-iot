# Sistema de Monitoramento de Vagas de Estacionamento via IoT (ODS 11)

Este repositório contém a documentação técnica, códigos-fonte e esquemas eletrônicos do protótipo desenvolvido para a disciplina da Faculdade de Computação e Informática da Universidade Presbiteriana Mackenzie. O projeto está alinhado com as metas da ODS 11 da ONU (Cidades e Comunidades Sustentáveis).

## 1. Descrição do Funcionamento e Uso

O protótipo monitora em tempo real a ocupação de uma vaga de estacionamento utilizando ondas ultrassônicas.

* Se um veículo estacionar a uma distância inferior a 30 cm do sensor, o sistema altera seu estado para "OCUPADO" e publica essa informação na nuvem via MQTT.
* Se a vaga for liberada, o estado muda para "LIVRE".
* Através de um painel (Dashboard) na nuvem, o usuário pode enviar comandos remotos para abrir (90°) ou fechar (0°) uma cancela física controlada por um servomotor.

## 2. Componentes de Hardware Utilizados

* **Plataforma de Desenvolvimento:** ESP32 DevKit v1 (Processador Xtensa Dual-Core 32-bit LX6 com Wi-Fi nativo integrado).
* **Sensor de Proximidade:** Sensor Ultrassônico HC-SR04.
* **Atuador Mecânico:** Micro Servomotor TowerPro SG90.
* **Acessórios:** Conexões estruturadas e barramentos simulados via ambiente Wokwi.

## 3. Interfaces, Protocolos e Módulos de Comunicação

O sistema possui comunicação e controle integral via internet (TCP/IP) utilizando o protocolo de mensagens MQTT.

* **Arquitetura:** Modelo Publish/Subscribe (Publicação/Assinatura).
* **Broker MQTT Utilizado:** Adafruit IO (https://adafruit.com).
* **Tópico de Transmissão (Uplink - Status do Sensor):** `GustavoPereiraMachado04/feeds/status` (Payloads enviados: `LIVRE` ou `OCUPADO`).
* **Tópico de Recepção (Downlink - Comando do Atuador):** `GustavoPereiraMachado04/feeds/comando` (Payloads recebidos: `ABRIR` ou `FECHAR`).

## 4. Como Reproduzir o Projeto (Software e Configuração)

1. Instale a Arduino IDE em seu computador.
2. No menu de configurações da IDE, adicione o suporte para placas da família **ESP32**.
3. Vá em **Ferramentas > Gerenciador de Bibliotecas** e instale as seguintes dependências:
   * `PubSubClient` (por Nick O'Leary)
   * `ESP32Servo` (por Kevin Harrington)
4. Abra o código contido na pasta `/src` deste repositório.
5. Altere as variáveis `ssid` e `password` com os dados do seu Wi-Fi local (no Wokwi, utilize `Wokwi-GUEST` e senha vazia).
6. Substitua as credenciais `mqtt_user` e `mqtt_key` com seus dados gerados na plataforma Adafruit IO.
7. Monte o hardware seguindo o diagrama contido na pasta `/hardware` (Pinos utilizados: Trigger no GPIO 12, Echo no GPIO 14 e Servo no GPIO 13).
8. Conecte o ESP32 ao computador via USB e faça o upload do código.
