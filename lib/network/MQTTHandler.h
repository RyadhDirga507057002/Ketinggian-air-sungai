#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
public:
    void begin();
    void loop();
    bool connected();
    void publish(const char* topic, const String& payload);

    void setCallback(MQTT_CALLBACK_SIGNATURE);

private:
    WiFiClient espClient;
    PubSubClient mqtt{espClient};

    unsigned long lastAttempt = 0;
    bool wifiReady = false;

    static void WiFiEvent(WiFiEvent_t event);
    String clientId();
    void ensureConnection();
};
