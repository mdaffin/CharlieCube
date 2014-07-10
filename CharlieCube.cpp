#include "CharlieCube.h"
#include <string.h>
#include <Arduino.h>

LED Cube::draw_frame[cube_size][cube_size][cube_size] = {};
LED Cube::render_frame[cube_size][cube_size][cube_size] = {};
int Cube::current_led = 0;
uint8_t Cube::sweep = 0;

const uint8_t Cube::pwm_map[] PROGMEM = {
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

const uint8_t Cube::pinsB[] PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x00};
const uint8_t Cube::pinsC[] PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08};
const uint8_t Cube::pinsD[] PROGMEM = {0x04,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void Cube::swap(uint8_t &a, uint8_t &b) {
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

void Cube::drawLine(uint8_t from_x, uint8_t from_y, uint8_t from_z, 
              uint8_t to_x, uint8_t to_y, uint8_t to_z,
              uint8_t red, uint8_t green, uint8_t blue) {
  bool reverseX = false;
  bool reverseY = false;
  bool reverseZ = false;
  if (from_x > to_x) {swap(from_x,to_x);reverseX=true;}
  if (from_y > to_y) {swap(from_y,to_y);reverseY=true;}
  if (from_z > to_z) {swap(from_z,to_z);reverseZ=true;}

  int delx = to_x - from_x;
  int dely = to_y - from_y;
  int delz = to_z - from_z;
  
  int longest = (delx>dely?delx>delz?delx:delz>dely?delz:dely:dely>delz?dely:delz>delx?delz:delx);
  for (int i = 0; i < longest; i++) {
    int xpos;
    if (reverseX) xpos = roundClostest(((longest-i)*delx),longest) + from_x;
    else xpos = roundClostest((i*delx),longest) + from_x;
    
    int ypos;
    if (reverseY) ypos = roundClostest(((longest-i)*dely),longest) + from_y;
    else ypos = roundClostest((i*dely),longest) + from_y;
    
    int zpos;
    if (reverseZ) zpos = roundClostest(((longest-i)*delz),longest) + from_z;
    else zpos = roundClostest((i*delz),longest) + from_z;
    
    drawPoint(xpos,ypos,zpos, red, green, blue);
  }
  
  if (reverseX) swap(from_x,to_x);
  if (reverseY) swap(from_y,to_y);
  if (reverseZ) swap(from_z,to_z);
  drawPoint(to_x,to_y,to_z, red, green, blue);
}

int Cube::roundClostest(int numerator, int denominator) {
  numerator = (numerator << 1)/denominator;
  int output = (numerator>>1) + (numerator % 2);
  return output;
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
  uint8_t brightness = pgm_read_byte(&(Cube::pwm_map[((uint8_t*)Cube::render_frame)[Cube::current_led]]));

  if (brightness & (1 << Cube::sweep)) {
    const uint8_t vcc = pgm_read_byte(&(((LEDPin*)Cube::led_maps)[Cube::current_led].vcc));
    const uint8_t vss = pgm_read_byte(&(((LEDPin*)Cube::led_maps)[Cube::current_led].vss));
    DDRB = pgm_read_byte(&(Cube::pinsB[vcc])) | pgm_read_byte(&(Cube::pinsB[vss]));
    DDRC = pgm_read_byte(&(Cube::pinsC[vcc])) | pgm_read_byte(&(Cube::pinsC[vss]));
    DDRD = pgm_read_byte(&(Cube::pinsD[vcc])) | pgm_read_byte(&(Cube::pinsD[vss]));

    PORTB = pgm_read_byte(&(Cube::pinsB[vcc]));
    PORTC = pgm_read_byte(&(Cube::pinsC[vcc]));
    PORTD = pgm_read_byte(&(Cube::pinsD[vcc])); 
  } else {
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
  }
  
  if (++Cube::current_led >= 192) {
    Cube::current_led = 0;
    ++Cube::sweep %= 8;
  }
}
