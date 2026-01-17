#pragma once
#include "MQTTHandler.h"
#include "LoRaHandler.h"
#include "UltrasonicHandler.h"
#include "DeviceConfig.h"

class BusinessLogic {
public:
    void begin();
    void loop();

private:
    DeviceMode mode;
    DeviceConfig config;
    MQTTHandler mqtt;
    LoRaHandler lora;
    UltrasonicHandler ultrasonic;

    
    int counter = 0;

    void nodeLoop();
    void gatewayLoop();
    void handleSerial();
};
