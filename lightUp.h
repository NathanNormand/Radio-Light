#include "Arduino.h"
#include  "FastLED.h"
#define NUM_LEDS 64       // total number of neopixels
#define DATA_PIN 6        // pin for neopixels

CRGB leds[NUM_LEDS]; // define neopixel array
int hue = 0;
void setLights()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  FastLED.setMaxPowerInMilliWatts(1000);
}

void lightUp(int m) // these patterns will be changed for final install
{
    switch(m)
  {
    case(0):
    
        fill_rainbow(leds, NUM_LEDS, hue, 7);
        hue+= 5;
        if(hue > 255) hue = 0;
        FastLED.show();
        //fadeToBlackBy(leds, NUM_LEDS, 50);
    break;
    case(1):
        EVERY_N_SECONDS(1)fill_solid(leds, NUM_LEDS, CRGB::White);
        
        EVERY_N_SECONDS(2)fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
    break;
    case(2):
      EVERY_N_SECONDS(1)
      {fill_solid(leds,NUM_LEDS, CRGB::Red); FastLED.show();}
      EVERY_N_SECONDS(2)
      {fill_solid(leds,NUM_LEDS, CRGB::Green); FastLED.show();}
      EVERY_N_SECONDS(3)
      {fill_solid(leds,NUM_LEDS, CRGB::Blue); FastLED.show();}
      
    break;
  }
}

void lightOFF()
{
    fill_solid(leds,NUM_LEDS,CRGB::Black);
}
