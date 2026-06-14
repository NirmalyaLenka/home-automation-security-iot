# Home Automation and Security System

This project implements a comprehensive smart home automation and security system using IoT technologies, RFID for access control, various sensors, and development boards like ESP32 and Arduino.

## Features

- RFID-based door authentication and home presence detection.
- Automatic power management based on homeowner presence.
- Climate control with AC activation upon entry.
- Scheduled lighting, geyser, and water motor control.
- Garden sprinkler system with presence detection.
- Gas leak detection (LPG/CNG and CO2) with alerts and safety measures.

## Hardware Components

- ESP32 or Arduino development boards
- RFID RC522 module
- IR sensors
- Gas sensors (MQ-2 for LPG, MQ-135 for CO2)
- Relays for controlling AC, lights, geyser, motor, sprinklers
- Servo or solenoid for door lock
- Buzzer/siren
- Water level sensor
- Presence/motion sensors for garden

## Software

- Arduino IDE for microcontroller programming
- MQTT for IoT communication
- Blynk or similar for mobile notifications

## Project Structure

- firmware/: Microcontroller codes
- docs/: Documentation
- web/: HTML demonstration

For detailed sensor explanations, see SENSORS.md.