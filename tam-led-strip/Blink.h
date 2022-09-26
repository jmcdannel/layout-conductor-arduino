#include "Arduino.h"

class Blink {
  private:
  
  public:
    Blink(){
      // Blank constructor  
    };
    void runPattern(int startLed, int endLed, int red, int green, int blue);
    bool isRunning = false;
    int blinkState = LOW;
    void blink();
    noDelay blinkTimer(1000, blink);
};

void Blink::loop() {
  blinkTimer.update();
}


void Blink::blink() {
  runPattern(startLed, endLed, red, green, blue);
}

void Blink::runPattern(int startLed, int endLed, int red, int green, int blue) {

  Serial.println("run");
  Serial.println(startLed);
  Serial.println(endLed);
  if (this->blinkState == LOW) {
    this->blinkState = HIGH;
    for (int i = startLed; i < endLed; i++) {
      leds[i] = CRGB(red, green, blue);
    }
  } else {
    this->blinkState = LOW;
    for (int i = startLed; i < endLed; i++) {
      leds[i] = CRGB::Black;
    }
  }

  // set the LED with the blinkState of the variable:
  FastLED.show();
}
