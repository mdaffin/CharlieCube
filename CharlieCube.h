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
  static void drawPoint(
      uint8_t x, uint8_t y, uint8_t z, 
      uint8_t red, uint8_t green, uint8_t blue
  );
  static void drawBox(
      uint8_t from_x, uint8_t from_y, uint8_t from_z, 
      uint8_t to_x, uint8_t to_y, uint8_t to_z, 
      uint8_t red, uint8_t green, uint8_t blue
  );
  static void drawLine(
      uint8_t from_x, uint8_t from_y, uint8_t from_z, 
      uint8_t to_x, uint8_t to_y, uint8_t to_z,
      uint8_t red, uint8_t green, uint8_t blue);
  static int roundClostest(int numerator, int denominator);
  static void clear();
  static void flush();

private:
  static int current_led;
  static LED draw_frame[cube_size][cube_size][cube_size];
  static LED render_frame[cube_size][cube_size][cube_size];
  static const uint16_t number_leds = cube_size * cube_size * cube_size * 3;
  static const LEDMap led_maps[];
  static uint8_t sweep;
  static const uint8_t pwm_map[];
  static const uint8_t pinsB[];
  static const uint8_t pinsC[];
  static const uint8_t pinsD[];
  static void swap(uint8_t &a, uint8_t &b);

  Cube();
  friend void TIMER2_OVF_vect();
};

#endif

