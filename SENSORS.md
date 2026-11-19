# Sensor Notes and Implementation Status

This document describes the project's intended sensor roles and distinguishes them from what the current example firmware actually implements. It is **not a wiring diagram, calibrated measurement guide, or safety-certified alarm design**.

## RFID reader (MFRC522 / RC522)

The main sketch initializes an MFRC522 reader on SPI using GPIO 21 as chip select and GPIO 22 as reset. When it reads any new card, it publishes the text “Door unlocked” to the MQTT topic home/door/status.

The current code does not compare the card UID against an authorized-card list and does not directly operate a lock output. Do not treat this as authenticated access control.

## LPG / combustible-gas sensor (MQ-2 example)

The main sketch reads the raw analog input defined as GPIO 35. If the ADC reading is greater than 500, it publishes “LPG Leak Detected” to home/gas/alert.

The threshold is a hard-coded raw reading, not a calibrated concentration. Sensor warm-up, calibration, ADC characteristics, sensor placement, and electrical compatibility are not documented or verified here. This prototype must not replace a certified gas alarm.

## Other sensor concepts

| Sensor or function | Intended role in the project | Status in firmware/main.ino |
|---|---|---|
| IR presence sensor | Presence detection | GPIO 34 is defined, but the input is not read |
| MQ-135 / CO2-related measurement | Air-quality or gas monitoring | GPIO 32 is defined, but the input is not read and no numeric reading is published |
| Water-level sensor | Tank-level monitoring | No corresponding pin or read routine is implemented in main.ino |
| Garden PIR / motion sensor | Presence-aware sprinkler control | No corresponding pin or read routine is implemented in main.ino |

An MQ-135 is a broad gas-sensitive device; a raw sensor reading should not be presented as calibrated CO2 ppm without a suitable measurement design and calibration.

## GPIO values defined by the main sketch

| Signal | GPIO |
|---|---:|
| RC522 chip select | 21 |
| RC522 reset | 22 |
| LPG analog input | 35 |
| IR input (defined, unused) | 34 |
| CO2-related input (defined, unused) | 32 |

These are source definitions only. The repository does not include a complete verified sensor wiring diagram or bill of materials. Check the exact module datasheets, supply voltage, output voltage, grounding, and board pin capabilities before connecting hardware. Do not connect sensor outputs that may exceed the ESP32's permitted input voltage.

## Verification status

The notes above were compared with firmware/main.ino. No sensor calibration, electrical measurement, hardware test, or safety certification was performed.
