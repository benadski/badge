#include <Fri3dBadge_IR.h>


// create an instance of the badge
Fri3dBadge badge;

void setup() {
  // prepare randomness with some random reading from an unconnected analog pin
  randomSeed(analogRead(0));
  randomSeed(analogRead(1));
  randomSeed(analogRead(2));
  randomSeed(analogRead(3));
  randomSeed(analogRead(4));
  
  // select our own random color at boot ...
  select_color();
  
  // ... and allow to reselect using the button
  badge.on_button_change(reselect_color);
  
  // start the IR receiver
  badge.on_ir_activity(handle_activity);
  badge.ir_rx_start();
}

uint8_t rb, gb, bb;

void select_color() {
  rb = gb = bb = 0;
  while( (rb == 0) && (gb == 0) && (bb == 0)) {
    rb = random(4) * 32;
    gb = random(4) * 16;
    bb = random(4) * 8;
  }
}

bool select_new_color = false;

void reselect_color() {
  if( ! badge.button_is_pressed() ) {
    select_new_color = true;
  }
}

bool activity_detected = false;

// don't respond to the very first interrupt, but make sure the received pulse
// was part of a pulse train
#define SKIP_ACTIVITY 2
int8_t skip_activity;

// don't respond to our own IR signals ;-)
volatile bool sending = false;

void handle_activity() {
  if(sending) { return; }
  if(skip_activity-- > 0) { return; }
  // set a flag to handle the activity (don't do too much in interrupt handler)
  activity_detected = true;
}

void flash_color() {
  badge.rgb_set_color(rb, gb, bb);
  delay(500);
  badge.rgb_set_color(0, 0, 0);
}

void fade_color() {
  uint16_t rf = rb;
  uint16_t gf = gb;
  uint16_t bf = bb;
  
  for(uint16_t i=0; i<255; i++) {
    badge.rgb_set_color((uint8_t)((rf*i)/256), (uint8_t)((gf*i)/256), (uint8_t)((bf*i)/256));
    delay(4);
  }
  delay(500);
  
  for(uint8_t i=0; i<255; i++) {
     if (rf > 0) rf--;
     if (gf > 0) gf--;
     if (bf > 0) bf--;
     badge.rgb_set_color((uint8_t)(rf),(uint8_t)(gf),(uint8_t)(bf));
     delay(10);
  }
  badge.rgb_set_color(0, 0, 0);
}

void wheel( byte pos ) {
  if(pos < 85) {
   badge.rgb_set_color( pos, 85 - pos, 0 );
  } else if( pos < 170) {
   pos -= 85;
   badge.rgb_set_color( 85 - pos, 0, pos );
  } else {
   pos -= 170;
   badge.rgb_set_color( 0, pos, 85 - pos );
  }
}

void fri3d( byte pos ) {
  if(pos < 64) {
   badge.rgb_set_color( pos * 4, pos / 2, 0 );
  } else if( pos < 128) {
   pos -= 64;
   badge.rgb_set_color( 255 - (pos * 4), 32 - (pos / 2), 0 );
  } else if( pos < 192) {
   pos -= 128;
   badge.rgb_set_color( 0, pos, pos * 4 );
  } else {
   pos -= 192;
   badge.rgb_set_color( 0, 64 - pos, 255 - (pos * 4));
  }
}

void fire ( byte pos ) {
  if(pos < 85) {
   badge.rgb_set_color( pos*3, 0, 0  );
  } else if( pos < 170) {
   pos -= 85;
   badge.rgb_set_color( 255, pos, 0 );
  } else {
   pos -= 170;
   badge.rgb_set_color( 255, 86, pos / 2 );
  }
}

void nature ( byte pos ) {
  if(pos < 85) {
   badge.rgb_set_color( 0, pos * 2, pos / 2  );
  } else if( pos < 170) {
   pos -= 85;
   badge.rgb_set_color( pos * 3, 170, 85 - (pos / 2) );
  } else {
   pos -= 170;
   badge.rgb_set_color( 255 - (pos * 3), 255 - (pos * 2), 0 );
  }
}

void ice ( byte pos ) {
  if(pos < 85) {
   badge.rgb_set_color( pos * 3, pos, 255 - (pos * 2 ));
  } else if( pos < 170) {
   badge.rgb_set_color( 255, 86, 85 );
  } else {
   pos -= 170;
   badge.rgb_set_color( 255 - (pos * 3), 86 - pos, 85 + pos * 2);
  }
}


void reply_with_party_parrot() {
  for(uint8_t i = 0; i < 255; i++) {
    wheel(i);
    delay(8);
  }
  badge.rgb_set_color(0, 0, 0);
}

void reply_with_fri3d() {
  for(uint16_t i = 0; i < 1024; i++) {
    fri3d((uint8_t)(i % 256));
    delay(2);
  }
  badge.rgb_set_color(0, 0, 0);
}

void reply_with_sparkle() {
    uint8_t r;
    for(uint8_t i = 0; i < 255; i++) {
    r = random(255);
    badge.rgb_set_color(r, random(r>>2), random(r>>4));
      delay(8);
  }
  badge.rgb_set_color(0, 0, 0);
}

void reply_with_lightning() {
  uint8_t flash;
  uint8_t bang = 0;
  
  for(uint8_t i = 0; i < 255; i++) {
    flash = random(32);
    if (flash==31){
      badge.rgb_set_color(64, 16, 255);
      bang++;
        if (bang==6){
          badge.rgb_set_color(128, 32, 255); 
          delay(100);            
        }
    }
    delay(4);
    badge.rgb_set_color(0, 0, 0);
  }
  if (bang<6){
    badge.rgb_set_color(128, 32, 255); 
    delay(100);            
    badge.rgb_set_color(0, 0, 0);
  }
}

void reply_with_fire() {
  uint8_t r = random(255);
  int8_t d = 1;
  for(uint8_t i = 0; i < 255; i++) {
    
    if ((i & 0x0F) == 0x0F) d = random(2);
    if (d == 0) d = -1;
     
    if (r > 251) d = -1;
    if (r < 4) d = 1;

    r += (d * 4);
        
    fire(r);
    delay(8);
  }
  while (r > 3){
    r -= 4;
    fire(r);
    delay(8);
  }
  badge.rgb_set_color(0, 0, 0);
}

void reply_with_nature() {
  uint8_t r = random(255);
  int8_t d = 1;
  for(uint8_t i = 0; i < 100; i++) {
    
    if ((i & 0x0F) == 0x0F) d = random(2);
    if (d == 0) d = -1;
     
    if (r > 251) d = -1;
    if (r < 4) d = 1;

    r += (d * 4);
        
    nature(r);
    delay(32);
  }
  badge.rgb_set_color(0, 0, 0);
}

void reply_with_ice() {
  uint8_t b = random(255);
  for(uint8_t i = 0; i < 255; i++) {
    ice(b);
    b += (i / 16);
    delay(8);
  }
  badge.rgb_set_color(0, 0, 0);
}


void reply_with_random() {
  uint8_t rnd = random(7);

  switch(rnd){

    case 0:
      reply_with_party_parrot();  //RGB!
      break;
    case 1:
      reply_with_sparkle();       //Warm gespetter
      break;
    case 2:
      reply_with_lightning();     //Onweer!
      break;
    case 3:
      reply_with_fire();          //Vuurkleurtjes
      break;
    case 4:
      reply_with_nature();        //Mooi groen
      break;
    case 5:
      reply_with_ice();           //Brrr.
      break;
    case 6:
      reply_with_fri3d();         //Fried kleurtjes
  }  
  
}

// timestamp of next dialog (= send pulse train)
uint32_t next_dialog = 0;

// we take a minimal interval of 5s and add a random part of the same length
#define INTERVAL    5000 + (random(6) * 1000) // start dialog every 5s + [0-5]s

// a pulse train of x pulses of pulse length y
#define PULSES        14
#define PULSE_LENGTH  250   // us

void loop() {
  uint32_t now = millis(); // rollover of ~49.7 days ... not gonna happen ;-)

  // start a dialog at INTERVAL
  if( now >= next_dialog ) {
    fade_color();
    
    // send an IR pulse train
    sending = true;
    
    uint8_t troll;
    for (uint8_t repeat=0; repeat<6; repeat++){
      for(uint8_t t=0; t<PULSES; t++) {
        troll = random(2);
        if (troll){
          badge.ir_send_pulse(PULSE_LENGTH);
          delayMicroseconds(PULSE_LENGTH);  //Let's see if TV's or other devices respond to randomly generated RC-5 code 
        }else {
          delayMicroseconds(PULSE_LENGTH); 
          badge.ir_send_pulse(PULSE_LENGTH);
        }
      }
      delay(20);
    }  
    sending = false;

    // schedule the next dialog after interval
    next_dialog = now + INTERVAL;
  }

  // respond to activity
  if(activity_detected) {
    delay(250);
    activity_detected = false;
    reply_with_random();
    skip_activity = SKIP_ACTIVITY;
    next_dialog = now + INTERVAL;
  }

  // handle new color selection request
  if(select_new_color) {
    select_color();
    flash_color();
    select_new_color = false;
    next_dialog = now + INTERVAL;
  }

  delay(5);
}
