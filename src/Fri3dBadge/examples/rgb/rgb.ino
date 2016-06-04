#include <Fri3dBadge.h>

Fri3dBadge badge;

void setup() {}
 
void loop() {
  badge.rgb_set_color(255, 0, 0);     // red
  delay(1000);
  badge.rgb_set_color(0, 255, 0);     // green
  delay(1000);
  badge.rgb_set_color(0, 0, 255);     // blue
  delay(1000);
  badge.rgb_set_color(255, 255, 0);   // yellow
  delay(1000);  
  badge.rgb_set_color(80, 0, 80);     // purple
  delay(1000);
  badge.rgb_set_color(0, 255, 255);   // aqua
  delay(1000);
}

