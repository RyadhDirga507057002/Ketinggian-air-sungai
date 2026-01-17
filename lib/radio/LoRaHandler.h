#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "main_config.h"

class LoRaHandler {
public:
    bool begin();
    bool receive(String &data);
    void send(const String &payload);
};
