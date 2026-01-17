#include "LoRaHandler.h"
#include "main_log.h"
bool LoRaHandler::begin() {
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(LORA_BAND)) {
        LoRaError("LoRa init failed");

        return false;
    }

    LoRa.setSyncWord(0xF3);
    LoRa.setTxPower(17);

    LoRaLog("LoRa init succeeded");
    return true;
}

bool LoRaHandler::receive(String &data) {
    int packetSize = LoRa.parsePacket();
    if (!packetSize) return false;

    data = "";
    while (LoRa.available()) {
        data += (char)LoRa.read();
    }
    return true;
}

void LoRaHandler::send(const String &payload) {
    LoRa.beginPacket();
    LoRa.print(payload);
    LoRa.endPacket();

    LoRaLog("LoRa packet sent");
    LoRaLog("Payload: " + payload);
}
