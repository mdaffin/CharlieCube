#include "CharlieCube.h"

uint8_t colors[3] = {0};
uint8_t current = 0;

void increase(uint8_t * value) {
  *value = 0;
  while((*value)++ < 8) {
    Cube::drawBox(0,0,0,3,3,3,colors[0],colors[1],colors[2]);
    Cube::flush();
    delay(100);
  }
  *(value) = 8;
}

void decrease(uint8_t * value) {
  *value = 8;
  while((*value)-- > 0) {
    Cube::drawBox(0,0,0,3,3,3,colors[0],colors[1],colors[2]);
    Cube::flush();
    delay(100);
  }
  *(value) = 0;
}

void setup() {
  Cube::begin();
  increase(&(colors[0]));
}

void loop() {
  uint8_t previous = current;
  if (++current > 2) { current = 0; }
  increase(&(colors[current]));
  decrease(&(colors[previous]));
  delay(1000);
}

