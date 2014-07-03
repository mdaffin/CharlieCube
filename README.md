CharlieCube
===========
This is a rewrite of [Asher Glick's charlieplexed RGB LED cube](http://aglick.com/charliecube.html) to be cleaner and easier to understand/use.

It is currently under heavy development and dose not yet have all the features of the original code.

It is designed to run on both the Arduino core as well as the [Cosa core](https://github.com/mikaelpatel/Cosa).

Instalation
===========
Download or checkout this repo into the library directoy of your arduinos sketchbook (ie ~/sketchbook/library/CharlieCube/CharlieCube.h)

    cd ~/sketchbook
    mkdir -p library
    cd library
    git clone https://github.com/james147/CharlieCube.git

Now you can open (or restart) your arduino ide and browse the examples via File->Examples->CharlieCube.

Usage
=====

    Cube::begin();
  
Sets up the cube, shoule only be called once in the setup function.

    Cube::clear();
  
Turns off all of the leds.

    Cube::drawPoint(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue);
  
Turns on/off the red, green and/or blue led at x, y, x.

  Cube::drawBox( uint8_t from_x, uint8_t from_y, uint8_t from_z, uint8_t to_x, uint8_t to_y, uint8_t to_z, uint8_t red, uint8_t green, uint8_t blue
  );

Draws a solid cube between the two points in the given color.

