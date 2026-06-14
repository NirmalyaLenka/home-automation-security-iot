#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include "mqtt_config.h"

// Pin definitions
#define RST_PIN 22
#define SS_PIN 21
#define RELAY_POWER 25
#define RELAY_AC 26
#define RELAY_GEYSER 27
#define RELAY_LIGHT 14
#define RELAY_MOTOR 12
#define RELAY_SPRINKLER 13
#define BUZZER 15
#define IR_PIN 34
#define GAS_LPG_PIN 35
#define GAS_CO2_PIN 32

WiFiClient espClient;
PubSubClient client(espClient);
MFRC522 rfid(SS_PIN, RST_PIN);

unsigned long lastMsg = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) messageTemp += (char)payload[i];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(messageTemp);
  if (String(topic) == topic_command) {
    if (messageTemp == "AC_ON") digitalWrite(RELAY_AC, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(client_id, mqtt_user, mqtt_pass)) {
      client.subscribe(topic_command);
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(RELAY_POWER, OUTPUT);
  pinMode(RELAY_AC, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    client.publish(topic_door, "Door unlocked");
  }

  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    client.publish(topic_power, "System Active");
    int lpg = analogRead(GAS_LPG_PIN);
    if (lpg > 500) client.publish(topic_gas, "LPG Leak Detected");
  }
  delay(100);
}