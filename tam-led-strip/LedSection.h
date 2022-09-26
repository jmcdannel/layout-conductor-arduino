#include "Arduino.h"
    
class LedSection {
  private:
  
  public:
    LedSection() {
       ts = 0;
       animateSpeed = 0;
       currentState = LOW;
       initialized = false;
       action = "";
    };
    void init(JsonVariant cmd, CRGB _leds);
    void loop();
    void animate();
    
    int startIdx;
    int endIdx;
    int animateSpeed;
    bool initialized;
    int currentState;
    String action;
    JsonVariant configJson;
    CRGB leds;
     uint32_t ts;
     uint32_t cs;
    
};

void LedSection::loop() {
  if (initialized) {
    cs = millis();
    if (animateSpeed > 0 && cs - ts >= animateSpeed) {
        animate();
        ts = cs;
    }
  }
    
    for (int ledNum = 20; ledNum < 40; ledNum++) {
      leds[ledNum] = CRGB::Green;
    }
    FastLED.show();
}

void LedSection::init(JsonVariant cmd, CRGB _leds) {
  Serial.println("init");
  configJson = cmd["payload"];
  action = cmd["action"].as<String>();
  leds = _leds;
//  Serial.println(action);
//  Serial.println(configJson["speed"].as<int>());
//  Serial.println(configJson["r"].as<int>());
  serializeJsonPretty(cmd, Serial);
//  serializeJsonPretty(configJson, Serial);
  if (configJson.containsKey("speed")) {
    animateSpeed = configJson["speed"].as<int>();
//    Serial.println(animateSpeed);
  }
  
  if (action == "solidColor") {
    int red = configJson["r"];
    int green = configJson["g"];
    int blue = configJson["b"];
//    fill_solid(leds[startIdx],(endIdx - startIdx), CRGB( red, green, blue));
//    fill_solid(leds, 10, CRGB( 255, 0, 0));
//    for (int ledNum = startIdx; ledNum < endIdx; ledNum++) {
//      Serial.println(ledNum);
//      leds[ledNum] = CRGB::Red;
//    }
//    FastLED.show();
  }
  initialized = true;
}
//
void LedSection::animate() {
  Serial.println("animate");
//  if (action == "blink") {
//    if (currentState == LOW) {
//    int red = configJson["r"];
//    int green = configJson["g"];
//    int blue = configJson["b"];
//      currentState = HIGH;
////      fill_solid(leds[startIdx],(endIdx - startIdx), CRGB( red, green, blue));
//    } else {
//      currentState = LOW;
////      fill_solid(leds[startIdx],(endIdx - startIdx), CRGB::Black);
//    }
//  }
}
