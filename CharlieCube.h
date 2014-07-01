#ifndef CHARLIECUBE_H
#define CHARLIECUBE_H

#include <avr/io.h> 
#include <avr/interrupt.h>

const uint8_t cube_size = 4; // 4x4x4 cube

struct LEDPin {
  uint8_t vcc;
  uint8_t vss;
};

struct LEDMap {
  LEDPin red;
  LEDPin green;
  LEDPin blue;
};

struct LED {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

ISR(TIMER2_OVF_vect);

class Cube {
public:
  /**
   * Initiate the tone player.
   */
  static void begin();
  static void drawPoint(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue);
  static void clear();

private:
  static int current_led;
  static LED leds[cube_size][cube_size][cube_size];

  Cube();
  friend void TIMER2_OVF_vect();
};

#endif

