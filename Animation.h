#include "CharlieCube.h"

#ifndef ANIMATION_H
#define ANIMATION_H


class Animation {
public:
  static void fountian(uint8_t red, uint8_t green, uint8_t blue, uint16_t speed = 100);
  static void static_frame1();
  static void planarSpin(uint8_t red, uint8_t green, uint8_t blue, uint16_t speed = 100);

private:
};

#endif //ANIMATION_H
