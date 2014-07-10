#include "Animation.h"
#include "Arduino.h"

void Animation::fountian(uint8_t red, uint8_t green, uint8_t blue, uint16_t speed) {

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

void Animation::static_frame1() {
  Cube::drawBox(0,0,0, 3,3,3, 8, 0, 0);
  Cube::drawBox(1,1,0, 2,2,3, 8, 8, 8);
  Cube::drawBox(0,1,1, 0,2,2, 0, 8, 0);
  Cube::drawBox(1,0,1, 2,0,2, 0, 8, 0);
  Cube::drawBox(3,1,1, 3,2,2, 0, 8, 0);
  Cube::drawBox(1,3,1, 2,3,2, 0, 8, 0);
  Cube::drawBox(1,1,3, 2,2,3, 0, 8, 0);
  Cube::drawBox(1,1,0, 2,2,0, 0, 8, 0);
  Cube::flush();
}

void Animation::planarSpin(uint8_t red, uint8_t green, uint8_t blue, uint16_t speed) {
  int spinsPerColor = 5; // a spin is actually half a revolution
  for (int i = 0; i < spinsPerColor; i++) {
    for (int x = 0; x < 3; x++) {
      Cube::drawLine(x,0,0,3-x,3,0,red,green,blue);
      Cube::drawLine(x,0,1,3-x,3,1,red,green,blue);
      Cube::drawLine(x,0,2,3-x,3,2,red,green,blue);
      Cube::drawLine(x,0,3,3-x,3,3,red,green,blue);
      Cube::flush();
      Cube::clear();
      delay(speed);
    }
    for (int y = 0; y < 3; y++) {
      Cube::drawLine(3,y,0,0,3-y,0,red,green,blue);
      Cube::drawLine(3,y,1,0,3-y,1,red,green,blue);
      Cube::drawLine(3,y,2,0,3-y,2,red,green,blue);
      Cube::drawLine(3,y,3,0,3-y,3,red,green,blue);
      Cube::flush();
      Cube::clear();
      delay(speed);
    }
  }
}

