
#include "Turnout.h"

// Turnout 1 (Red)
#define T1_SERVO_IDX 9
#define T1_BUTTON_PIN 2
#define T1_STRAIGHT_ANGLE 100
#define T1_DIVERGENT_ANGLE 130

// Turnout 2 (Green)
#define T2_SERVO_IDX 11
#define T2_BUTTON_PIN 3
#define T2_STRAIGHT_ANGLE 90
#define T2_DIVERGENT_ANGLE 120

Turnout turnout1 = Turnout(T1_SERVO_IDX, T1_STRAIGHT_ANGLE, T1_DIVERGENT_ANGLE, T1_BUTTON_PIN);
Turnout turnout2 = Turnout(T2_SERVO_IDX, T2_STRAIGHT_ANGLE, T2_DIVERGENT_ANGLE, T2_BUTTON_PIN);

void setup() {
  Serial.begin(9600);
     
  turnout1.setup();
  turnout2.setup();
}

void loop() {
  turnout1.loop();
  turnout2.loop();
}
