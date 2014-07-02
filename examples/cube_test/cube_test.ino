#include "CharlieCube.h"

void setup() {
  Cube::begin();
}

int wait = 500;

void loop() {
  Cube::drawBox(0,0,0, 3,3,3, 255, 0, 0);
  Cube::drawBox(1,1,0, 2,2,3, 255, 255, 255);
  Cube::drawBox(0,1,1, 0,2,2, 0, 255, 0);
  Cube::drawBox(1,0,1, 2,0,2, 0, 255, 0);
  Cube::drawBox(3,1,1, 3,2,2, 0, 255, 0);
  Cube::drawBox(1,3,1, 2,3,2, 0, 255, 0);
  Cube::drawBox(1,1,3, 2,2,3, 0, 255, 0);
  Cube::drawBox(1,1,0, 2,2,0, 0, 255, 0);
  Cube::flush();
  delay(500);
}

