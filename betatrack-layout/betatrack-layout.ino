#include <ArduinoJson.h>
#include <TurnoutPulser.h>

int outPins [] = { 2, 3, 4, 5 };

/*
[{"action":"pin","payload":{"pin":43,"value":0}}]
[{"action":"turnout","payload":{"turnout":0,"state":1}}]
 */


TurnoutPulser turnouts[] = {
  TurnoutPulser(6, 7), 
  TurnoutPulser(8, 9)
};

const size_t capacity = 20*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 60;
DynamicJsonDocument doc(capacity);

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;
  Serial.println("Setup");

  for (int idx=0; idx<(sizeof(outPins) / sizeof(outPins[0])); idx++) {
    pinMode(outPins[idx], OUTPUT);
  }

  for (int idx=0; idx<(sizeof(turnouts) / sizeof(turnouts[0])); idx++) {
    turnouts[idx].begin();
  }

}

void loop() {

  for (int idx=0; idx<(sizeof(turnouts) / sizeof(turnouts[0])); idx++) {
    turnouts[idx].loop();
  }
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

  if (action == "pin") {
    handlePin(payload);
  } else if (action == "turnout") {
    handleTurnout(payload);
  }
  
}

void handleTurnout(JsonObject payload) {
  int turnoutIdx = payload["turnout"];
  bool state = payload["state"];
  turnouts[turnoutIdx].set(state);
  Serial.print("turnoutIdx: ");
  Serial.println(turnoutIdx);
  Serial.print("state: ");
  Serial.println(state);
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
