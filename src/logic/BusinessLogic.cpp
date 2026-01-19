#include "BusinessLogic.h"
#include "main_config.h"

// Fungsi ini dipanggil sekali saat program dimulai untuk menginisialisasi semua komponen
void BusinessLogic::begin() {
    // Mulai komunikasi serial dengan kecepatan 115200 bps untuk debugging
    Serial.begin(115200);

    // Inisialisasi sensor ultrasonic untuk mengukur jarak
    ultrasonic.begin();
    // Inisialisasi modul LoRa untuk komunikasi nirkabel
    lora.begin();

    // Inisialisasi konfigurasi perangkat
    config.begin();
    // Muat mode perangkat (NODE atau GATEWAY) dari penyimpanan
    mode = config.loadMode();

    // Jika perangkat dalam mode GATEWAY, siapkan MQTT untuk komunikasi internet
    if (mode == MODE_GATEWAY) {
        // Mulai koneksi MQTT
        mqtt.begin();
        // Set callback untuk menerima pesan MQTT dan mengirimkannya via LoRa
        mqtt.setCallback([&](char*, byte* p, unsigned int l) {
            // Buat string dari data yang diterima
            String msg;
            while (l--) msg += (char)*p++;
            // Kirim pesan via LoRa
            lora.send(msg);
        });
    }
}

// Fungsi utama yang dipanggil berulang-ulang dalam loop utama program
void BusinessLogic::loop() {
    // Tangani input dari serial monitor
    handleSerial();

    // Jalankan loop sesuai mode: NODE atau GATEWAY
    if (mode == MODE_NODE) nodeLoop();
    else gatewayLoop();
}

// Loop khusus untuk mode NODE: mengirim data sensor secara berkala
void BusinessLogic::nodeLoop() {
    // Variabel untuk menyimpan perintah yang diterima
    String cmd;
    // Jika menerima perintah via LoRa
    if (lora.receive(cmd)) {
        // Jika perintah adalah SET_INTERVAL, ubah interval pengiriman
        if (cmd.indexOf("SET_INTERVAL") >= 0) {
            // Ambil nilai interval dari perintah
            interval = cmd.substring(cmd.indexOf(":") + 1).toInt();
        }
        // Kirim konfirmasi balik
        lora.send("{\"fbk\":true}");
    }

    // Jika belum waktunya mengirim data, keluar dari fungsi
    if (millis() - lastSend < interval) return;
    // Catat waktu pengiriman terakhir
    lastSend = millis();

    // Baca jarak dari sensor ultrasonic
    float jarak = ultrasonic.read();
    // Buat payload data dalam format JSON
    String payload = "{\"node_id\":\"" NODE_ID "\",\"counter\":" +
                     String(counter++) + ",\"distance\":" + String(jarak) + "}";

    // Kirim data via LoRa
    lora.send(payload);
}

// Loop khusus untuk mode GATEWAY: menerima data dari NODE dan kirim ke MQTT
void BusinessLogic::gatewayLoop() {
    // Jalankan loop MQTT untuk menjaga koneksi
    mqtt.loop();

    // Variabel untuk menyimpan data yang diterima
    String data;
    // Jika menerima data via LoRa dari NODE
    if (lora.receive(data)) {
        // Publikasikan data ke topik MQTT
        mqtt.publish(MQTT_DATA_TOPIC, data);
    }
}

// Fungsi untuk menangani input dari serial monitor (untuk mengubah mode)
void BusinessLogic::handleSerial() {
    // Jika tidak ada data di serial, keluar
    if (!Serial.available()) return;
    // Baca string sampai newline
    String payload = Serial.readStringUntil('\n');
    // Hapus spasi di awal dan akhir
    payload.trim();

    // Jika perintah adalah "MODE NODE", ubah mode dan restart
    if (payload == "MODE NODE") {
        config.saveMode(MODE_NODE);
        ESP.restart();
    }
    // Jika perintah adalah "MODE GATEWAY", ubah mode dan restart
    if (payload == "MODE GATEWAY") {
        config.saveMode(MODE_GATEWAY);
        ESP.restart();
    }
}
