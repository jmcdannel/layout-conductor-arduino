#include <Adafruit_NeoPixel.h>

#define PIN 6
#define MAX_CONFIGS 8



class StripConfig {
  uint32_t color;      
  uint8_t wait;     
  int startLed;    
  int endLed;
  String action;
  bool init = false;
  
  unsigned long previousMillis; 
  int currentLed;
//  Adafruit_NeoPixel strip;

  public: StripConfig() {
    previousMillis = 0;
  }

  void Start(uint32_t c, uint8_t w, int startIdx,  int endIdx, String a) {
    color = c; 
    wait = w;
    startLed = startIdx;
    endLed = endIdx;
    currentLed = startIdx;
    action = a;
    init = true;
  }
  
  void Loop(Adafruit_NeoPixel strip) {
    unsigned long currentMillis = millis();
//    Serial.println(currentMillis - previousMillis);
//    Serial.println(init);
//    Serial.println(wait);
//    Serial.println(action);
    if (init == true && currentLed <= endLed && currentMillis - previousMillis >= wait) {

      if (action == "solidColor") {
        Serial.println(action);
        Serial.println(currentLed);
        Serial.println(previousMillis);
        strip.setPixelColor(currentLed, color);
//        strip.show(); 
        previousMillis = currentMillis;
        currentLed++;
      }
      
    }

  }
};

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(47, PIN, NEO_GRB + NEO_KHZ800);
//ColorWipe wiper;

StripConfig configs[MAX_CONFIGS];

int currentConfig = 0;
long previousMillis = 0;   

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;
  Serial.println("Setup");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
//  for(uint16_t i = 0; i < MAX_CONFIGS; i++) {
//      configs[i].Setup();
//  }

  
  configs[0].Start(strip.Color(0, 0, 255), 10, 0, 10, "solidColor");
//  configs[1].Start(strip.Color(0, 255, 0), 50, 11, 40, "coflorWipe");
}

void loop() {

//  unsigned long currentMillis = millis();


  
//  String action = "solidColor"; // colorWipe / theaterChase / rainbow / rainbowCycle
//  int startLed = 0;
//  int endLed = 10;
//  uint32_t ledColor = strip.Color(255, 0, 0);
//  uint8_t ledSpeed = 50;
//  
//  if (action == "solidColor") {
//    configs[currentConfig].Start(ledColor, ledSpeed, startLed, endLed);
//      solidColor(ledColor, startLed, endLed);
//      action = "";
//  } else if (action == "colorWipe") {
////      colorWipe(ledColor, ledSpeed);
////      wiper = ColorWipe(strip, ledColor, ledSpeed, startLed, endLed);
//      action = "";
//  }

  
  for(uint16_t i = 0; i < MAX_CONFIGS; i++) {
      configs[i].Loop(strip);
  }
//  wiper.Update();
  
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127,   0,   0), 50); // Red
//  theaterChase(strip.Color(  0,   0, 127), 50); // Blue
//
//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

void solidColor(uint32_t c, int startLed, int endLed) {
  for(uint16_t i = startLed; i < endLed; i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
