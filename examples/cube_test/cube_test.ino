#include "CharlieCube.h"

void setup() {
  Cube::begin();
}

int wait = 500;

void loop() {
  Cube::drawBox(0,0,0, 3,3,3, 0, 255, 0);
  Cube::drawBox(1,1,0, 2,2,3, 255, 255, 255);
  Cube::drawBox(0,0,3, 3,3,3, 255, 0, 0);
  delay(500);
}

