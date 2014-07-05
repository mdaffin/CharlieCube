#include "CharlieCube.h"
#include <string.h>
#include <Arduino.h>

LED Cube::draw_frame[cube_size][cube_size][cube_size] = {};
LED Cube::render_frame[cube_size][cube_size][cube_size] = {};
int Cube::current_led = 0;
uint8_t pass = 0;
uint8_t sweep = 0;
const LEDPin *Cube::pins = ((LEDPin*)&Cube::led_maps);

uint8_t pwm_map[] = {
  0b00000000,
  0b10000000,
  0b10001000,
  0b10010010,
  0b10101010,
  0b10110110,
  0b11101110,
  0b11111110,
  0b11111111
};

const uint8_t pinsB[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x00};
const uint8_t pinsC[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08};
const uint8_t pinsD[] = {0x04,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void swap(uint8_t &a, uint8_t &b) {
  uint8_t c = a;
  a = b;
  b = c;
}

void Cube::begin()
{
  /* Setup timer 2 */
  TCCR2B = 0b00000001;
  TIMSK2 |=  (1<<TOIE2);

  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
}

void Cube::drawPoint(uint8_t x, uint8_t y, uint8_t z,
                     uint8_t red, uint8_t green, uint8_t blue) {
  draw_frame[x][y][z].red = red;
  draw_frame[x][y][z].green = green;
  draw_frame[x][y][z].blue = blue;
}

void Cube::drawBox(uint8_t from_x, uint8_t from_y, uint8_t from_z, 
                   uint8_t to_x, uint8_t to_y, uint8_t to_z, 
                   uint8_t red, uint8_t green, uint8_t blue) {
  if (from_x >  to_x) { swap(from_x, to_x); }  
  if (from_y >  to_y) { swap(from_y, to_y); }  
  if (from_z >  to_z) { swap(from_z, to_z); }  

  for (int i = from_x; i <= to_x; i++) {
    for (int j = from_y; j <= to_y; j++) {
      for (int k = from_z; k <= to_z; k++) {
        drawPoint(i, j, k, red, green, blue);
      }
    }
  }
}

void Cube::clear() {
  for (int z = 0; z < 4; z++) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        draw_frame[x][y][z].red = 0;
        draw_frame[x][y][z].green = 0;
        draw_frame[x][y][z].blue = 0;
      }
    }
  }
}

void Cube::flush() {
  memcpy(render_frame, draw_frame, sizeof(draw_frame));
}

ISR(TIMER2_OVF_vect) 
{
  // Drawing every update slows down animations, and a higher prescaller causes flicker
  if ((pass) % 2) {
    return;
  }

  uint8_t brightness = pwm_map[((uint8_t*)Cube::render_frame)[Cube::current_led]];

  if (brightness & (1 << sweep)) {
    const LEDPin *pin = &Cube::pins[Cube::current_led];
    DDRB = pinsB[pin->vcc] | pinsB[pin->vss];
    DDRC = pinsC[pin->vcc] | pinsC[pin->vss];
    DDRD = pinsD[pin->vcc] | pinsD[pin->vss];

    PORTB = pinsB[pin->vcc];
    PORTC = pinsC[pin->vcc];
    PORTD = pinsD[pin->vcc]; 
  } else {
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
  }
  
  if (++Cube::current_led >= 192) {
    Cube::current_led = 0;
    ++sweep %= 8;
  }
}
