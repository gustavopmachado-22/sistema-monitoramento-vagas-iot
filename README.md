# Sistema de Monitoramento de Vagas de Estacionamento via IoT (ODS 11)

Este repositório contém a documentação técnica, códigos-fonte e esquemas eletrônicos do protótipo desenvolvido para a disciplina da Faculdade de Computação e Informática da Universidade Presbiteriana Mackenzie. O projeto está alinhado com as metas da ODS 11 da ONU (Cidades e Comunidades Sustentáveis).

## 1. Descrição do Funcionamento e Uso
O protótipo monitora em tempo real a ocupação de uma vaga de estacionamento utilizando ondas ultrassônicas. 
* Se um veículo estacionar a uma distância inferior a 30 cm do sensor, o sistema altera seu estado para "OCUPADO" e publica essa informação na nuvem via MQTT.
* Se a vaga for liberada, o estado muda para "LIVRE".
* Através de um painel (Dashboard) na nuvem, o usuário pode enviar comandos remotos para abrir (90°) ou fechar (0°) uma cancela física controlada por um servomotor.

## 2. Componentes de Hardware Utilizados
* **Plataforma de Desenvolvimento:** NodeMCU ESP8266 (Módulo Wi-Fi nativo integrado, SoC Tensilica L106 32-bit).
* **Sensor de Proximidade:** Sensor Ultrassônico HC-SR04.
* **Atuador Mecânico:** Micro Servomotor TowerPro SG90.
* **Acessórios:** Matriz de contatos (Protoboard) e cabos jumpers para conexões.

## 3. Interfaces, Protocolos e Módulos de Comunicação
O sistema possui comunicação e controle integral via internet (TCP/IP) utilizando o protocolo de mensagens **MQTT**.
* **Arquitetura:** Modelo Publish/Subscribe (Publicação/Assinatura).
* **Broker MQTT Utilizado:** Adafruit IO (`://adafruit.com`).
* **Tópico de Transmissão (Uplink - Status do Sensor):** `estacionamento/vaga/01/status` (Payloads enviados: `LIVRE` ou `OCUPADO`).
* **Tópico de Recepção (Downlink - Comando do Atuador):** `estacionamento/vaga/01/comando` (Payloads recebidos: `ABRIR` ou `FECHAR`).

## 4. Como Reproduzir o Projeto (Software e Configuração)
1. Instale a **Arduino IDE** em seu computador.
2. No menu de configurações da IDE, adicione o suporte para placas **ESP8266**.
3. Vá em *Ferramentas > Gerenciador de Bibliotecas* e instale as seguintes dependências:
   * **PubSubClient** (por Nick O'Leary)
   * **NewPing** (por Tim Eckel)
4. Abra o código contido na pasta `/src/` deste repositório.
5. Altere as variáveis `ssid` e `password` com os dados do seu Wi-Fi local.
6. Substitua as credenciais `mqtt_user` e `mqtt_key` com seus dados gerados na plataforma Adafruit IO.
7. Monte o hardware seguindo o diagrama contido na pasta `/hardware/`.
8. Conecte o NodeMCU ao computador via USB e faça o upload do código.
