# Home Assistant Integration (example configuration)

This directory contains Home Assistant YAML examples for the home-automation prototype. They are **not a verified drop-in integration**: the checked-in topics and payloads do not consistently match the messages produced or consumed by firmware/main.ino.

## Files

| Path | Contents |
|---|---|
| configuration.yaml | MQTT sensor and switch examples, plus one inline gas-alert automation |
| automations.yaml | Separate automation examples for RFID, presence, AC, sprinkler, and geyser scenarios |

The checked-in configuration does not include automations.yaml with an include directive. Home Assistant will not automatically load that separate file merely because it is present in the repository. Review and validate the YAML with the version of Home Assistant you use before applying it.

## Local prerequisites

1. Install Home Assistant and configure its MQTT integration.
2. Create local secrets for mqtt_broker, mqtt_user, and mqtt_password; the referenced secrets are not supplied by this repository.
3. Replace placeholder entity IDs and notification services, including notify.mobile_app_your_phone, with entities that exist in your installation.
4. Compare every topic and payload with the firmware before enabling an automation.

## Known protocol mismatches

| Item | Firmware example | YAML example |
|---|---|---|
| Door status | Publishes “Door unlocked” to home/door/status when any readable RFID card is detected | Expects OPEN or CLOSED on home/door/status |
| RFID automation | Does not publish an AUTHORIZED event to home/rfid/door | automations.yaml waits for AUTHORIZED on home/rfid/door |
| LPG alert | Publishes “LPG Leak Detected” to home/gas/alert when a raw ADC threshold is crossed | Listens on home/alert/gas for LEAK or NORMAL |
| Numeric gas readings | Does not publish numeric readings to home/gas/lpg or home/gas/co2 | Defines MQTT sensors on those topics |
| Main power | Publishes “System Active” to home/power/status | Expects ON/OFF and sends commands to home/power/set |
| AC control | Listens on home/command for AC_ON only | Sends AC commands to home/ac/set |

These mismatches mean the YAML examples should not be assumed to control the current firmware correctly. The RFID sketch also does not validate card IDs, so it must not be used as a real door-lock authorization system.

## Safe validation

- Validate the YAML in a test Home Assistant instance before loading it into a live configuration.
- Use a private, authenticated MQTT broker. Do not send home-control messages over the public broker currently configured in firmware.
- Start with simulated MQTT messages and non-actuating test entities. Do not connect these examples to locks, heaters, geysers, pumps, or mains-powered appliances.
- No Home Assistant startup, automation execution, MQTT integration, or hardware test is claimed by this documentation.
