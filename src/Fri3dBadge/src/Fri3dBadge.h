#ifndef __FRI3D_BADGE_H
#define __FRI3D_BADGE_H

#include "Arduino.h"

typedef void(*badge_event_handler_t)(void);

class Fri3dBadge {
  public:
    Fri3dBadge();
    void on_button_change(badge_event_handler_t handler);
    void sleep();
    void rgb_set_color(uint8_t red, uint8_t green, uint8_t blue);
    bool button_is_pressed();
};

#endif
