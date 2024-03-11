#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <HardwareSerial.h>

#define RESPONSE_MAXDELAY 400
#define INCOMING_QUEUE_SIZE 100

typedef struct {
  char id[32];
  char payload[64];
  int battery_level; // 4bytes
} struct_message; // total: 32+64+4=100 (max 250 bytes)

typedef struct {
    bool handled;
} struct_response;

typedef struct {
    uint8_t mac[ESP_NOW_ETH_ALEN];
    struct_message message;
} incoming_message_event;