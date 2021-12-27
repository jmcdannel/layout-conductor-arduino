#include "Turnout.h"
#include <Servo.h>
#include <Pushbutton.h>

Turnout::Turnout(int index, int straight, int divergent, int buttonPin)
      : button(buttonPin) {
  this->index = index;
  this->straight = straight;
  this->divergent = divergent;
  this->buttonPin = buttonPin;
  
}

void Turnout::setup() {
  this->servo.attach(this->index);
  this->current = this->straight;
}


void Turnout::loop() {
  if (button.getSingleDebouncedPress()) {
    Serial.println("button");
    if (this->current == this->straight) {
      this->setDivergent();
    } else {
      this->setStraight();
    }
  }
}

void Turnout::setStraight() {
  this->servo.write(this->straight);
  this->current = this->straight;
}

void Turnout::setDivergent() {
  this->servo.write(this->divergent);
  this->current = this->divergent;
}
