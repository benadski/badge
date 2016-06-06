#include "Arduino.h"
#include "Fri3dBadge.h"

// RGB LED
#define red_pin      5
#define green_pin   10
#define blue_pin     9

// Button
#define button_pin  12

Fri3dBadge::Fri3dBadge() {
  // prepare RGB LED pin
  pinMode(red_pin,   OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin,  OUTPUT);
  
  // prepare button pin
  pinMode(button_pin, INPUT);
}

void Fri3dBadge::rgb_set_color(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(red_pin,   255 - red);
  analogWrite(green_pin, 255 - green);
  analogWrite(blue_pin,  255 - blue);
}
  
bool Fri3dBadge::button_is_pressed() {
  return digitalRead(button_pin) == HIGH;
}