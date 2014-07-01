#include "CharlieCube.h"

LED Cube::leds[cube_size][cube_size][cube_size] = {};
int Cube::current_led = 0;

const uint8_t pinsB[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x00};
const uint8_t pinsC[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08};
const uint8_t pinsD[] = {0x04,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

extern LEDMap led_maps[];

void Cube::begin()
{
  /* Setup timer 2 */
  TCCR2B = 0b00000001;
  TIMSK2 |=  (1<<TOIE2);

  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
}

void Cube::drawPoint(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue) {
  leds[x][y][z].red = red;
  leds[x][y][z].green = green;
  leds[x][y][z].blue = blue;
}

void Cube::clear() {
  for (int z = 0; z < 4; z++) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        leds[x][y][z].red = 0;
        leds[x][y][z].green = 0;
        leds[x][y][z].blue = 0;
      }
    }
  }
}

ISR(TIMER2_OVF_vect) 
{
  LEDPin* pins = (LEDPin *)led_maps + Cube::current_led;

  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;

  if (((bool*)Cube::leds)[Cube::current_led]) {
    DDRB = pinsB[pins->vcc] | pinsB[pins->vss];
    DDRC = pinsC[pins->vcc] | pinsC[pins->vss];
    DDRD = pinsD[pins->vcc] | pinsD[pins->vss];

    PORTB = pinsB[pins->vcc];
    PORTC = pinsC[pins->vcc];
    PORTD = pinsD[pins->vcc]; 
  }
  
  Cube::current_led = (Cube::current_led + 1) % (cube_size * cube_size * cube_size * 3);
}
