#include <Fri3dBadge.h>

Fri3dBadge badge;

void setup() {}

void loop() {
  if( badge.button_is_pressed() ) {
    badge.rgb_set_color(255, 0, 0);
  } else {
    badge.rgb_set_color(0, 0, 0);
  }
}
