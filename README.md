# Home Automation and Security System

An ESP32/MQTT home-automation prototype with separate Home Assistant YAML examples and a static browser demo. The checked-in pieces are **not currently a verified, end-to-end integrated system**. Several topic and payload mismatches, incomplete firmware paths, and security limitations must be resolved before hardware use.

## What is actually present

| Path | Purpose and current status |
|---|---|
| **firmware/main.ino** | ESP32 Wi-Fi/MQTT sketch using PubSubClient and MFRC522. Reads one LPG analog input and publishes status/alerts. It does not implement all features described in the project concept. |
| **firmware/mqtt_config.h** | Wi-Fi placeholders, MQTT broker settings, and topic strings. It currently points to a public broker. |
| **firmware/blynk_integration.ino** | Partial Blynk fragment. It references RELAY_AC without a definition in the tracked configuration and should not be assumed to build independently. |
| **firmware/blynk_config.h** | Blynk template/token placeholders. |
| **home_assistant/configuration.yaml** | Example MQTT sensors, switches, and an inline automation. Topics and payloads do not all match the firmware. |
| **home_assistant/automations.yaml** | Separate automation examples. This file is not included by the checked-in configuration file, and its RFID trigger does not match the firmware's published message. |
| **home_assistant/README.md** | Initial Home Assistant setup notes; verify them against the current YAML before use. |
| **web/index.html** | Static dashboard demonstration. Its buttons show browser alerts; they do not send commands to the ESP32 or Home Assistant. |
| **SENSORS.md** | General sensor descriptions, not a verified wiring diagram or complete implementation record. |
| **docs/User_Manual.docx** | A Word document is present; its contents were not verified during this source review. |

## Current firmware behavior

The main sketch connects to Wi-Fi and an MQTT broker, initializes the RC522 reader, and checks for a new RFID card. It publishes the text **Door unlocked** for any readable card; it does not compare the card UID against an authorized list and does not directly actuate a door-lock output. Do not treat this as access control.

Approximately every five seconds, it publishes **System Active** and reads the LPG analog input. If the raw reading is greater than 500, it publishes **LPG Leak Detected**. The value 500 is a hard-coded threshold, not a calibrated gas concentration. The code defines a CO2 input and an IR input but does not read either one.

The MQTT callback listens on **home/command** and recognizes only **AC_ON**, which writes LOW to the AC relay GPIO. There is no corresponding AC_OFF command in this callback. Other declared relay pins are not fully configured or controlled by the current loop.

## GPIO definitions in firmware/main.ino

These are the values defined in the source, not a verified wiring recommendation.

| Signal | GPIO | Current code status |
|---|---:|---|
| RC522 reset | 22 | Passed to MFRC522 |
| RC522 chip select | 21 | Passed to MFRC522 |
| Main power relay | 25 | Set as output; no control action in the loop |
| AC relay | 26 | Set as output; LOW written for AC_ON |
| Geyser relay | 27 | Defined, but not configured/controlled by the current loop |
| Light relay | 14 | Defined, but not configured/controlled by the current loop |
| Motor relay | 12 | Defined, but not configured/controlled by the current loop |
| Sprinkler relay | 13 | Defined, but not configured/controlled by the current loop |
| Buzzer | 15 | Set as output; no alarm action in the current loop |
| IR input | 34 | Defined but not read |
| LPG analog input | 35 | Read for the raw threshold check |
| CO2 input | 32 | Defined but not read |

No complete schematic or verified bill of materials is included in the root tree. Check the exact board, sensor output voltages, relay module polarity, isolation, and power requirements before wiring anything.

## Known integration mismatches

The Home Assistant examples and the current MQTT sketch do not agree on the protocol:

| Function | Firmware behavior | Home Assistant example |
|---|---|---|
| Door status | Publishes **Door unlocked** to **home/door/status** for any readable card | Expects **OPEN** or **CLOSED** on the same topic |
| Main power | Publishes **System Active** to **home/power/status** | Expects **ON** or **OFF** and sends commands to **home/power/set** |
| LPG alert | Publishes **LPG Leak Detected** to **home/gas/alert** | Listens on **home/alert/gas** and expects **LEAK** or **NORMAL** |
| LPG/CO2 levels | Does not publish numeric readings to **home/gas/lpg** or **home/gas/co2** | Defines sensors on those topics |
| AC control | Listens on **home/command** for **AC_ON** only | Sends AC commands to **home/ac/set** |
| RFID automation | Publishes to **home/door/status** without authorization checking | The separate automation listens on **home/rfid/door** for **AUTHORIZED** |

The current Home Assistant configuration also defines an inline automation, while the separate automations file is not included. Entity IDs and notification services such as **notify.mobile_app_your_phone** require local configuration. The YAML should not be considered a ready-to-load, validated configuration.

## Prerequisites and safe review workflow

The main sketch references the ESP32 Arduino core, PubSubClient, and MFRC522. The separate Blynk fragment additionally references the Blynk library. No dependency lockfile or successful build record is present.

1. Review the source and topic mismatches before attempting a build.
2. For an isolated compile check, use a temporary local sketch folder containing only a copy of **main.ino** and **mqtt_config.h**; the tracked firmware directory contains two Arduino sketches, and the Blynk fragment has unresolved references.
3. Install ESP32 board support and the PubSubClient and MFRC522 libraries in the Arduino environment.
4. Configure a private MQTT broker and credentials in the temporary test copy. Do not use the current public broker for private home-control traffic.
5. Keep the first tests disconnected from locks, heaters, geysers, AC units, pumps, and mains wiring. Use a safe low-voltage test setup and qualified electrical review before any real installation.

The repository has not been compiled or tested on hardware as part of this documentation pass. The steps above are a cautious review path, not a claim that the current integrated project builds or operates correctly.

## Security and safety limitations

- **The configured broker is broker.hivemq.com on port 1883, with empty MQTT username/password values.** Public, unencrypted MQTT is unsuitable for private home automation or access control. Use a private authenticated broker with appropriate topic permissions and encrypted transport before considering any deployment.
- RFID reads are not authenticated against an allowlist. Do not connect this behavior to a real lock.
- The LPG threshold is raw ADC data and is not a calibrated or safety-certified gas alarm. Do not rely on it for life safety.
- Relay output polarity, electrical isolation, load ratings, sensor compatibility, and mains wiring have not been verified.
- The dashboard is a simulation and its alert buttons only show browser dialogs; they do not activate hardware.
- Never test this prototype with exposed mains voltage or unattended appliances.

## Maintenance & Audit

- **Audit date:** 19 November 2026
- **Documentation status:** README reviewed and audit record added on this date.
- **Scope and evidence:** This is a documentation-level maintenance pass. It does not establish that source code compiles, dependencies are current, security has been tested, or hardware/runtime behavior has been verified.
- **Code and tests:** No new functional code changes or test results are claimed by this README update. Run project-specific build, test, and hardware/runtime checks before relying on the project.
- **Maintenance baseline:** Documentation status recorded through 11 November 2026; revisit setup instructions, dependencies, known limitations, and tests when the project changes.
