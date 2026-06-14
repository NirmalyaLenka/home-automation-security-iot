// Smart Home Automation and Security System
// Main firmware for ESP32/Arduino

#include <SPI.h>
#include <MFRC522.h>

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

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  
  pinMode(RELAY_POWER, OUTPUT);
  pinMode(RELAY_AC, OUTPUT);
  // ... other pins
  digitalWrite(RELAY_POWER, HIGH); // Start with power off
}

void loop() {
  // RFID check for door and presence
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      // Check UID and perform actions
      Serial.println("Card detected");
      // Add logic for door open, power on, AC timer etc.
    }
  }
  
  // Gas sensor checks
  int lpg = analogRead(GAS_LPG_PIN);
  if (lpg > 500) {
    // Trigger alert
    digitalWrite(BUZZER, HIGH);
  }
  
  delay(1000);
}