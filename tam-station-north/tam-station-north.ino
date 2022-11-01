#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ArduinoJson.h>

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define SERVO_COUNT 16

// {"action":"servo","payload":{"servo":0,"angle":60,"relay":{"relayPin":0,"state":true}}}
// {"action":"servo","payload":{"servo":0,"value":60}}
// [{"action":"servo","payload":{"servo":0,"value":60}}, {"action":"pin","payload":{"pin":43,"value":0}}]
// [{"action":"pin","payload":{"pin":43,"value":0}}]
// [{"action":"pin","payload":{"pin":47,"value":0}},{"action":"pin","payload":{"pin":49,"value":0}}]
// [{"action":"pin","payload":{"pin":43,"value":0}},{"action":"pin","payload":{"pin":45,"value":0}},{"action":"pin","payload":{"pin":47,"value":0}},{"action":"pin","payload":{"pin":49,"value":0}}]
// [{"action":"pin","payload":{"pin":43,"value":1}},{"action":"pin","payload":{"pin":45,"value":1}},{"action":"pin","payload":{"pin":47,"value":1}},{"action":"pin","payload":{"pin":49,"value":1}}]


const size_t capacity = 20*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 60;
DynamicJsonDocument doc(capacity);
Adafruit_PWMServoDriver pwmTSS = Adafruit_PWMServoDriver(0x42);

int outPins [] = {
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31,
  32,
  33,
  34,
  35,
  36,
  37,
  38,
  39,
  40,
  41,
  42,
  43,
  44,
  45,
  46,
  47,
  48,
  49,
  50,
  51,
  52
};

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;
  Serial.println("Setup");
  pwmTSS.begin();
  pwmTSS.setOscillatorFrequency(27000000);
  pwmTSS.setPWMFreq(SERVO_FREQ);
  for (int idx=0; idx<(sizeof(outPins) / sizeof(outPins[0])); idx++) {
    pinMode(outPins[idx], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("handleInput");
    handleInput();
  }
}

void handleInput() {
  String input = Serial.readString();
  Serial.println(input);
  deserializeJson(doc, input);
  JsonArray array = doc.as<JsonArray>();
  for(JsonVariant v : array) {
    handleAction(v);    
  }  
}

void handleAction(JsonVariant v) {
  String action = v["action"];
  JsonObject payload = v["payload"];

  Serial.print("Action: ");
  Serial.println(action);

  if (action == "servo") {
    handleServo(payload);
  } else if (action == "pin") {
    handlePin(payload);
  }
  
}

void handleServo(JsonObject payload) {
  int angle = payload["value"];
  int servo = payload["servo"];
  String pwm = payload["pwm"];
  Serial.print("angle: ");
  Serial.println(angle);
  Serial.print("servo: ");
  Serial.println(servo);
  Serial.print("pwm: ");
  Serial.println(pwm);
  if (pwm == "tss") {
    pwmTSS.setPWM(servo, 0, getPulseWidth(angle));
  }
}

void handlePin(JsonObject payload) {
  int pin = payload["pin"];
  int state = payload["value"];
  Serial.print("pin: ");
  Serial.println(pin);
  Serial.print("state: ");
  Serial.println(state);
  digitalWrite(pin, state);
}

int getPulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * SERVO_FREQ * 4096);
  Serial.println(analog_value);
  return analog_value;
}
