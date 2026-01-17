#include "MQTTHandler.h"
#include "main_config.h"
#include "main_log.h"

static MQTTHandler* self;

void MQTTHandler::WiFiEvent(WiFiEvent_t event) {
    if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) {
        self->wifiReady = true;
    }
    if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
        self->wifiReady = false;
        WiFi.begin(WIFI_SSID, WIFI_PASS);
    }
}

String MQTTHandler::clientId() {
    return "ESP32-GW-" + WiFi.macAddress();
}

void MQTTHandler::begin() {
    self = this;
    WiFi.mode(WIFI_STA);
    WiFi.onEvent(WiFiEvent);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
}

void MQTTHandler::setCallback(MQTT_CALLBACK_SIGNATURE) {
    mqtt.setCallback(callback);
}

bool MQTTHandler::connected() {
    return mqtt.connected();
}

void MQTTHandler::ensureConnection() {
    if (!wifiReady) return;
    if (mqtt.connected()) return;
    if (millis() - lastAttempt < 5000) return;

    lastAttempt = millis();
    mqtt.connect(clientId().c_str());
    if (mqtt.connected()) {
        mqtt.subscribe(MQTT_CMD_TOPIC);
    }
}

void MQTTHandler::loop() {
    ensureConnection();
    mqtt.loop();
}

void MQTTHandler::publish(const char* topic, const String& payload) {
    if (mqtt.connected()) {
        mqtt.publish(topic, payload.c_str());
    }
}
