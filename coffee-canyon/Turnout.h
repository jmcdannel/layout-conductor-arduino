#ifndef DCTC_TURNOUT_H
#define DCTC_TURNOUT_H

#include <Arduino.h>
#include <Servo.h>
#include <Pushbutton.h>

class Turnout {

  private:
    int index;
    int current;
    int straight;
    int divergent;
    int buttonPin;
    Servo servo;
    Pushbutton button;

  public:
    Turnout(int index, int straight, int divergent, int buttonPin);

    void setup();
    void loop();
    void setStraight();
    void setDivergent();
};

#endif
