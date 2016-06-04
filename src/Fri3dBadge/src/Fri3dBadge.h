#ifndef __FRI3D_BADGE_H
#define __FRI3D_BADGE_H

#include "Arduino.h"

class Fri3dBadge {
  public:
    Fri3dBadge();
    void rgb_set_color(uint8_t red, uint8_t green, uint8_t blue);
};

#endif