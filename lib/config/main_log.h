#ifndef MAINLOG_H
#define MAINLOG_H
#include <Arduino.h>

inline void deviceLog(const String &message)   {Serial.println("[Device LOG] " + message);}
inline void deviceError(const String &message) {Serial.println("[Device Error] " + message);}

inline void LoRaLog(const String &message)   {Serial.println("[LoRa LOG] " + message);}
inline void LoRaError(const String &message) {Serial.println("[LoRa Error] " + message);}

inline void WiFiLog(const String &message)   {Serial.println("[WiFi LOG] " + message);}
inline void WiFiError(const String &message) {Serial.println("[WiFi Error] " + message);}

inline void MQTTLog(const String &message)   {Serial.println("[MQTT LOG] " + message);}
inline void MQTTError(const String &message) {Serial.println("[MQTT Error] " + message);}

#endif // LOG_H