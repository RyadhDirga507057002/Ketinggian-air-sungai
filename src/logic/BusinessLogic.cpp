#include "BusinessLogic.h"
#include "main_config.h"

void BusinessLogic::begin() {
    Serial.begin(115200);

    ultrasonic.begin();
    lora.begin();

    config.begin();
    mode = config.loadMode();

    if (mode == MODE_GATEWAY) {
        mqtt.begin();
        mqtt.setCallback([&](char*, byte* p, unsigned int l) {
            String msg;
            while (l--) msg += (char)*p++;
            lora.send(msg);
        });
    }
}

void BusinessLogic::loop() {
    handleSerial();

    if (mode == MODE_NODE) nodeLoop();
    else gatewayLoop();
}

void BusinessLogic::nodeLoop() {
    String cmd;
    if (lora.receive(cmd)) {
        if (cmd.indexOf("SET_INTERVAL") >= 0) {
            interval = cmd.substring(cmd.indexOf(":") + 1).toInt();
        }
        lora.send("{\"ack\":true}");
    }

    if (millis() - lastSend < interval) return;
    lastSend = millis();

    float d = ultrasonic.read();
    String payload = "{\"node_id\":\"" NODE_ID "\",\"counter\":" +
                     String(counter++) + ",\"distance\":" + String(d) + "}";

    lora.send(payload);
}

void BusinessLogic::gatewayLoop() {
    mqtt.loop();

    String data;
    if (lora.receive(data)) {
        mqtt.publish(MQTT_DATA_TOPIC, data);
    }
}

void BusinessLogic::handleSerial() {
    if (!Serial.available()) return;
    String c = Serial.readStringUntil('\n');
    c.trim();

    if (c == "MODE NODE") {
        config.saveMode(MODE_NODE);
        ESP.restart();
    }
    if (c == "MODE GATEWAY") {
        config.saveMode(MODE_GATEWAY);
        ESP.restart();
    }
}
