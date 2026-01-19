# ESP32 LoRa – MQTT Multiprotocol Node & Gateway

Proyek ini adalah firmware ESP32 dengan arsitektur modular yang mendukung dua mode operasi: NODE dan GATEWAY. Sistem ini dirancang untuk komunikasi data jarak jauh menggunakan LoRa dan integrasi cloud menggunakan MQTT melalui WiFi.

---

## Deskripsi Singkat

Firmware ini memungkinkan ESP32 berfungsi sebagai:

* **Node**: membaca data sensor ultrasonic dan mengirimkannya melalui LoRa.
* **Gateway**: menerima data LoRa dari node dan meneruskannya ke broker MQTT.

Mode perangkat disimpan menggunakan Preferences (NVS) sehingga tetap tersimpan meskipun perangkat dimatikan.

---

## Fitur

* Mode NODE dan GATEWAY yang dapat diubah saat runtime
* Penyimpanan mode menggunakan Preferences (Non-Volatile Storage)
* Komunikasi LoRa menggunakan modul RFM95/SX1276
* Komunikasi MQTT menggunakan WiFi
* Forward command dari MQTT ke LoRa
* Auto reconnect WiFi dan MQTT
* Arsitektur kode terstruktur dan modular

---

## Arsitektur Sistem

```
[ESP32 NODE] --LoRa--> [ESP32 GATEWAY] --MQTT--> [MQTT Broker]
     ^                                         |
     |------------------- Command -------------|
```

---

## Struktur Direktori

```
src/
├── main.cpp
├── main_config.h
├── config/
│   └── DeviceConfig.h / DeviceConfig.cpp
├── network/
│   └── MQTTHandler.h / MQTTHandler.cpp
├── radio/
│   └── LoRaHandler.h / LoRaHandler.cpp
├── sensor/
│   └── UltrasonicHandler.h / UltrasonicHandler.cpp
└── logic/
    └── BusinessLogic.h / BusinessLogic.cpp
```

---

## Mode Operasi

### Mode NODE

* Membaca data jarak dari sensor ultrasonic
* Mengirim data secara periodik melalui LoRa dalam format JSON
* Menerima perintah dari gateway melalui LoRa
* Mengirim ACK sebagai respon perintah

Contoh payload:

```json
{
  "node_id": "BPMP-01",
  "counter": 5,
  "distance": 32.4
}
```

---

### Mode GATEWAY

* Menghubungkan ESP32 ke jaringan WiFi
* Menghubungkan ESP32 ke broker MQTT
* Menerima data dari node melalui LoRa
* Mempublikasikan data ke topic MQTT
* Meneruskan command dari MQTT ke node melalui LoRa

---

## Konfigurasi MQTT

* Broker: broker.hivemq.com
* Port: 1883

Topic yang digunakan:

* Publish data:
  `multiprotokol/BPMP/data/LoRa`
* Subscribe command:
  `multiprotokol/BPMP/cmd/LoRa/BPMP-01`

---

## Penyimpanan Mode (Preferences)

Mode perangkat disimpan di NVS dengan konfigurasi:

* Namespace: `config`
* Key: `mode`
* Value:

  * `0` untuk MODE_NODE
  * `1` untuk MODE_GATEWAY

---

## Serial Command

Gunakan Serial Monitor dengan baudrate 115200.

Perintah:

```
MODE NODE
```

Mengubah perangkat ke mode NODE dan melakukan restart.

```
MODE GATEWAY
```

Mengubah perangkat ke mode GATEWAY dan melakukan restart.

---

## Hardware yang Digunakan

* ESP32 Dev Module
* Modul LoRa RFM95 / SX1276
* Sensor Ultrasonic HC-SR04 atau kompatibel
* Antena LoRa 915 MHz

---

## Pengembangan Lanjutan

Firmware ini dapat dikembangkan lebih lanjut untuk:

* Implementasi FreeRTOS
* Penambahan buffer data offline (SPIFFS atau SD Card)
* Integrasi protokol industri seperti RS485 atau Modbus
* Penggunaan MQTT dengan TLS
* Integrasi dashboard monitoring

---

## Lisensi

Proyek ini bersifat open-source dan dapat digunakan untuk keperluan edukasi, riset, dan pengembangan sistem IoT.

---

## Author

Ryadh Dirga
