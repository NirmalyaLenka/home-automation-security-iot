#ifndef MQTT_CONFIG_H
#define MQTT_CONFIG_H

// WiFi and MQTT settings
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_pass = "";

const char* client_id = "esp32_home_automation";

// MQTT Topics
const char* topic_door = "home/door/status";
const char* topic_power = "home/power/status";
const char* topic_ac = "home/ac/status";
const char* topic_gas = "home/gas/alert";
const char* topic_sprinkler = "home/sprinkler/status";
const char* topic_command = "home/command";

#endif