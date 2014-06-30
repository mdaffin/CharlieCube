#include "CharlieCube.h"

void setup() {
  Serial.begin(9200);
  Cube::begin();
}

int wait = 500;

void loop() {
  for (int z = 0; z < 4; z++) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        Cube::clear();
        Cube::drawPoint(x, y, z, 1, 0, 0);
        delay(wait);
        Cube::clear();
        Cube::drawPoint(x, y, z, 0, 1, 0);
        delay(wait);
        Cube::clear();
        Cube::drawPoint(x, y, z, 0, 0, 1);
        delay(wait);
      }
    }
  }
}

