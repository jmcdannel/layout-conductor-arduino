#include <FastLED.h>
//#include <Wire.h>
#include <ArduinoJson.h>
#include "LedSection.h"

#define LED_PIN   6
#define NUM_LEDS 46
#define NUM_SECTIONS 3

const bool debugEnabled = true;

/* 
  
{"action":"blink","payload":{"section":1,"speed":1000,"r":255,"g":0,"b":0}}

{"action":"solidColor","payload":{"section":0,"r":202,"g":0,"b":0}}

*/

struct CRGB leds[NUM_LEDS];
LedSection sections[NUM_SECTIONS];
const size_t capacity = 40*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 60;
StaticJsonDocument<capacity> newCommand;

void setup() {
  InitializeSerial();
  InitializeConfig();
  InitializeLeds();
//  SetPinModes();
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("handleInput");
    Serial.println(capacity);
    handleInput();
  }
  
  for (int sectionIdx = 0; sectionIdx < NUM_SECTIONS; sectionIdx++) {
    sections[sectionIdx].loop();
  }  

  
//    for (int ledNum = 20; ledNum < 40; ledNum++) {
//      leds[ledNum] = CRGB::Green;
//    }
//    FastLED.show();
}

void InitializeSerial() {
  Serial.begin(115200);
  while (!Serial) continue;
  Serial.println("Setup"); 
}

void InitializeConfig() {
  // 
  sections[0].startIdx = 0;
  sections[0].endIdx = 10;
  // 
  sections[1].startIdx = 10;
  sections[1].endIdx = 20;
  // 
  sections[2].startIdx = 30;
  sections[2].endIdx = 45;
}

void InitializeLeds() {
//  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
//  FastLED.show();
}

//void SetPinModes() {
//  // 
//}

void handleInput() {
  deserializeJson(newCommand, Serial.readString());
  serializeJsonPretty(newCommand, Serial);
//  sections[newCommand["payload"]["section"].as<int>()].init(newCommand.to<JsonVariant>(), leds);
}
