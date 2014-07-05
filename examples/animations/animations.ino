#include "CharlieCube.h"

void setup() {
  Cube::begin();
  fountian(8, 0, 0);
  fountian(0, 0, 0);
  fountian(0, 8, 0);
  fountian(0, 0, 0);
  fountian(0, 0, 8);
  fountian(0, 0, 0);
}

void fountian(uint8_t red, uint8_t green, uint8_t blue) {
  int speed = 100;

  for (int i = 0; i < 4; i++) {
    Cube::drawBox(1,1,i, 2,2,i, red, green, blue);
    Cube::flush();
    delay(speed);
  }
  for (int i = 3; i >= 0; i--) {
    Cube::drawBox(0,0,i, 3,0,i, red, green, blue);
    Cube::drawBox(0,0,i, 0,3,i, red, green, blue);
    Cube::drawBox(3,3,i, 3,0,i, red, green, blue);
    Cube::drawBox(3,3,i, 0,3,i, red, green, blue);
    Cube::flush();
    delay(speed);
  }
}

void loop() {
  uint8_t red = random(9);
  uint8_t green = random(9);
  uint8_t blue = random(9);
  while (!(red+green+blue)) {
    red = random(9);
    green = random(9);
    blue = random(9);
  }
  fountian(red, green, blue);
  fountian(0, 0, 0);
}

