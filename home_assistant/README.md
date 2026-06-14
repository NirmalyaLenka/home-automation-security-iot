# Home Assistant Integration

This folder contains YAML configurations for integrating the IoT home automation system with Home Assistant.

## Setup Instructions

1. Install Home Assistant (Docker, Supervised, or Core).
2. Enable MQTT integration and configure broker details in secrets.yaml.
3. Copy the files from this directory into your Home Assistant configuration directory.
4. Restart Home Assistant.
5. Ensure your ESP32 firmware publishes/subscribes to the correct MQTT topics.

## Key Entities
- Sensors for gas, water level, door status.
- Switches for all relays and appliances.
- Automations for scheduled tasks, safety responses, and presence-based controls.

For full MQTT topic reference, see the firmware code.