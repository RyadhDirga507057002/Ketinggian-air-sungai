#pragma once
#include <Preferences.h>
#include "main_config.h"

class DeviceConfig {
public:
    void begin();
    DeviceMode loadMode();
    void saveMode(DeviceMode mode);

private:
    Preferences prefs;
};
