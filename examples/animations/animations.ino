#include "CharlieCube.h"

void setup() {
  Cube::begin();
  fountian(255, 0, 0);
  fountian(0, 255, 0);
  fountian(0, 0, 255);
}

void spinner(uint8_t red, uint8_t green, uint8_t blue) {
  int speed = 50;

}

void fountian(uint8_t red, uint8_t green, uint8_t blue) {
  int speed = 100;

  for (int i = 0; i < 4; i++) {
    Cube::clear();
    Cube::drawBox(0,0,i, 3,3,i, red, green, blue);
    Cube::drawBox(1,1,i, 2,2,i, 0, 0, 0);
    Cube::flush();
    delay(speed);
  }
  for (int i = 3; i >= 0; i--) {
    Cube::clear();
    Cube::drawBox(1,1,i, 2,2,i, red, green, blue);
    Cube::flush();
    delay(speed);
  }
}

void loop() {
  uint8_t red = random(2);
  uint8_t green = random(2);
  uint8_t blue = random(2);
  while (!(red+green+blue)) {
    red = random(2);
    green = random(2);
    blue = random(2);
  }
  fountian(red, green, blue);
}

