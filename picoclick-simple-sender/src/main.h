#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <FastLED.h>

// Picoclick C3 hardware definitions
#define ADC_ENABLE_PIN  3
#define APA102_SDI_PIN  7
#define APA102_CLK_PIN  6
#define ADC_PIN         4
#define BUTTON_PIN      5

#define FPC_IO_1        2
#define FPC_IO_2        8
#define FPC_IO_BTN      BUTTON_PIN

#define SDA_PIN         FPC_IO_1
#define SCL_PIN         FPC_IO_2

#define NUM_LEDS        2
CRGB leds[NUM_LEDS];

#define BAT_VOLT_MULTIPLIER   1.43
#define BAT_VOLT_OFFSET       0

typedef struct {
  char id[32];
  char payload[64];
  int battery_level; // 4bytes
} struct_message; // total: 32+64+4=100 (max 250 bytes)

typedef struct {
    bool handled;
} struct_response;

void set_fastled(CRGB c0, CRGB c1){
    leds[0] = c0;
    leds[1] = c1;
    FastLED.show();
}

void set_fastled(CRGB c0){
    leds[0] = c0;
    leds[1] = c0;
    FastLED.show();
}

void switch_colors_fastled(){
    CRGB c_tmp = leds[1];
    leds[1] = leds[0];
    leds[0] = c_tmp;
    FastLED.show();
}

float get_battery_voltage(){
  digitalWrite(ADC_ENABLE_PIN, LOW);
  delayMicroseconds(10);
  int sum = 0;
  for(int i=0; i<100; i++){
    sum = sum + analogRead(ADC_PIN);
  }
  float result = sum/100.0;
  digitalWrite(ADC_ENABLE_PIN, HIGH);
  return int(float(result) * BAT_VOLT_MULTIPLIER + BAT_VOLT_OFFSET);
}