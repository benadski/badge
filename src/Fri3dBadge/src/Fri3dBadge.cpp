#include <avr/sleep.h>

#include "Arduino.h"
#include "Fri3dBadge.h"

// RGB LED
#define red_pin      5
#define green_pin   10
#define blue_pin     9

// Button
#define button_pin  0

Fri3dBadge::Fri3dBadge() {
  // prepare RGB LED pin
  pinMode(red_pin,   OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin,  OUTPUT);
  // initialize to black
  this->rgb_set_color(0, 0, 0);
  
  // prepare button pin
  pinMode(button_pin, INPUT);
}

void Fri3dBadge::on_button_change(badge_event_handler_t handler) {
  attachInterrupt(digitalPinToInterrupt(button_pin), handler, CHANGE);
}

void Fri3dBadge::sleep() {
  // via: http://arduino.stackexchange.com/questions/10408
  // disable USB
  USBCON |= _BV(FRZCLK);  // freeze USB clock
  PLLCSR &= ~_BV(PLLE);   // turn off USB PLL
  USBCON &= ~_BV(USBE);   // disable USB

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  // wake up procedure
  sleep_disable();
  delay(100);
  USBDevice.attach();
  delay(100);
}

void Fri3dBadge::sleep_for(uint8_t sec) {
  // compute actual sleep time (aka prescaler) and remainder
  uint8_t prescaler = 0,
          left      = 0;
  if(sec >= 8) {
    prescaler = (1<<WDP3)                        | (1<<WDP0);
    left      = sec - 8;
  } else if(sec >= 4) {
    prescaler = (1<<WDP3);
    left      = sec - 4;
  } else if(sec >= 2) {
    prescaler =            (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
    left      = sec - 2;
  } else {
    prescaler =            (1<<WDP2) | (1<<WDP1);
    left      = sec - 1;
  }

  // don't reset, we just use it as an interrupt when sleeping deeply
  MCUSR &= ~(1<<WDRF);

  // to change WDE or the prescaler, we need to set WDCE
  // WDCE: Watchdog Change Enable
  // WDE: Watchdog System Reset Enable
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  // set new watchdog timeout prescaler value
  // resets all other bits
  WDTCSR = prescaler;

  // only enable the interrupt
  WDTCSR |= (1<<WDIE);

  this->sleep();

  // disable the interrupt
  WDTCSR &= ~(1<<WDIE);

  // recurse until no sleep time is left
  if(left) { this->sleep_for(left); }
}

// watchdog interrupt is just used to get out of power down sleep
ISR(WDT_vect) {}

void Fri3dBadge::rgb_set_color(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(red_pin,   255 - red);
  analogWrite(green_pin, 255 - green);
  analogWrite(blue_pin,  255 - blue);
}
  
bool Fri3dBadge::button_is_pressed() {
  return digitalRead(button_pin) == HIGH;
}
