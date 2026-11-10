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

---

## Skills & technologies

`Arduino/C++` · `C/C++` · `HTML/CSS`


## How it works

The main firmware sketch is `firmware/blynk_integration.ino`. Open it in Arduino IDE, verify the board, pin mapping and library requirements, then compile and upload. Test hardware behaviour on the real circuit before relying on it.


## Maintenance & Audit

- **Audit date:** 10 November 2026
- **Documentation status:** README reviewed and audit record added on this date.
- **Scope and evidence:** This is a documentation-level maintenance pass. It does not establish that source code compiles, dependencies are current, security has been tested, or hardware/runtime behavior has been verified.
- **Code and tests:** No new functional code changes or test results are claimed by this README update. Run project-specific build, test, and hardware/runtime checks before relying on the project.
- **Maintenance baseline:** Documentation status recorded through 10 November 2026; revisit setup instructions, dependencies, known limitations, and tests when the project changes.
