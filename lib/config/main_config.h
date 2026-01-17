#pragma once
#include <Arduino.h>

/* ================= ID ================= */
#define NODE_ID "BPMP-01"

/* ================= WIFI ================= */
#define WIFI_SSID "Telkom"
#define WIFI_PASS "12345678"

/* ================= MQTT ================= */
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT   1883

#define MQTT_DATA_TOPIC "multiprotokol/BPMP/data/LoRa"
#define MQTT_CMD_TOPIC  "multiprotokol/BPMP/cmd/LoRa/BPMP-01"

/* ================= MODE ================= */
enum DeviceMode {
    MODE_NODE = 0,
    MODE_GATEWAY = 1
};

/* ================= LORA ================= */
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  33
#define LORA_BAND  915E6

/* ================= ULTRASONIC ================= */
#define TRIG_PIN 27
#define ECHO_PIN 26
