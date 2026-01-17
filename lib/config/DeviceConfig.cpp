#include "DeviceConfig.h"

void DeviceConfig::begin() {
    prefs.begin("config", false);
}

DeviceMode DeviceConfig::loadMode() {
    prefs.begin("config", true);
    DeviceMode mode = (DeviceMode)prefs.getUInt("mode", MODE_NODE);
    prefs.end();
    return mode;
}

void DeviceConfig::saveMode(DeviceMode mode) {
    prefs.begin("config", false);
    prefs.putUInt("mode", mode);
    prefs.end();
}
