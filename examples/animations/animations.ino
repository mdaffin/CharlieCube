#include "CharlieCube.h"
#include "Animation.h"
#include "Arduino.h"

void fountian() {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  for (uint8_t i = 0; i < 5; i++) {
    do {
      red = random(2) ? 0 : 8;
      green = random(2) ? 0 : 8;
      blue = random(2) ? 0 : 8;
    } while (!(red+green+blue));
    Animation::fountian(red, green, blue);
    Animation::fountian(0, 0, 0);
  }
}

void planarSpin() {
  Animation::planarSpin(8, 0, 0);
  Animation::planarSpin(0, 8, 0);
  Animation::planarSpin(0, 0, 8);
}

void setup() {
  Cube::begin();
}

void loop() {
  planarSpin();
  Animation::static_frame1();
  delay(2000);
  fountian();
}


