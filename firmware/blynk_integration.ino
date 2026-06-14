#include <BlynkSimpleEsp32.h>
#include "mqtt_config.h"
#include "blynk_config.h"

// Virtual pins for Blynk
#define VPIN_DOOR V0
#define VPIN_AC V1
#define VPIN_GEYSER V2

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(VPIN_AC) {
  int value = param.asInt();
  digitalWrite(RELAY_AC, value ? LOW : HIGH);
}

// Add more virtual pins for controls
