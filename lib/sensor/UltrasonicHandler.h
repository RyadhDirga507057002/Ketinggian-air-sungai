#pragma once
#include <Arduino.h>
#include "main_config.h"

class UltrasonicHandler {
public:
    void begin();
    float read(); // cm
};
