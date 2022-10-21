#include <FastLED.h>
#define NUM_LEDS 1          // total number of neopixels
#define DATA_PIN 6          // pin for neopixels


void startLED();
void setColor(byte hue);
void dark();
void setMode(byte mode);
void showMode(byte hue, byte seconds);
