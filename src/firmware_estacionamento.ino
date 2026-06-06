#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// ===========================
// WIFI WOKWI
// ===========================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ===========================
// ADAFRUIT IO
// ===========================
const char* mqtt_server = "io.adafruit.com";
const int mqtt_port = 1883;

const char* mqtt_user = "GustavoPereiraMachado04";
const char* mqtt_key = "Sua chave adafruit IO;

// ===========================
// FEEDS MQTT
// ===========================
const char* TOPIC_STATUS =
"GustavoPereiraMachado04/feeds/status";

const char* TOPIC_COMMAND =
"GustavoPereiraMachado04/feeds/comando";

// ===========================
// PINOS
// ===========================
#define TRIGGER_PIN 12
#define ECHO_PIN 14
#define SERVO_PIN 13

Servo gateServo;
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

// ===========================
// WIFI
// ===========================
void setup_wifi() {

  Serial.println("Conectando ao WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ===========================
// MQTT CALLBACK
// ===========================
void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Mensagem recebida: ");
  Serial.println(message);

  if (message == "ABRIR") {

    Serial.println("Abrindo cancela");
    gateServo.write(90);

  } else if (message == "FECHAR") {

    Serial.println("Fechando cancela");
    gateServo.write(0);
  }
}

// ===========================
// MQTT RECONNECT
// ===========================
void reconnect() {

  while (!client.connected()) {

    Serial.println("Conectando MQTT...");

    if (client.connect(
          "ESP32SmartParking",
          mqtt_user,
          mqtt_key)) {

      Serial.println("MQTT conectado!");

      client.subscribe(TOPIC_COMMAND);

      Serial.println("Inscrito em:");
      Serial.println(TOPIC_COMMAND);

    } else {

      Serial.print("Erro MQTT: ");
      Serial.println(client.state());

      delay(5000);
    }
  }
}

// ===========================
// SETUP
// ===========================
void setup() {

  Serial.begin(115200);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// ===========================
// LOOP
// ===========================
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  unsigned long currentMillis = millis();

  if (currentMillis - lastMsg > 5000) {

    lastMsg = currentMillis;

    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGGER_PIN, LOW);

    // ALTERAÇÃO AQUI
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    int distance = duration * 0.034 / 2;

    Serial.print("Distancia: ");
    Serial.println(distance);

    bool occupied =
  (distance > 0 && distance < 30);

if (occupied) {

  Serial.println("OCUPADO");

  client.publish(
    TOPIC_STATUS,
    "OCUPADO"
  );

} else {

  Serial.println("LIVRE");

  client.publish(
    TOPIC_STATUS,
    "LIVRE"
  );
}
  
    }
  }