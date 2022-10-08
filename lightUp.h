#include "Arduino.h"
#include  "FastLED.h"

void lightUp(CRGB leds[], int NUM_LEDS, int m)
{
    switch(m)
  {
    case(0):
    
        fill_rainbow(leds, NUM_LEDS, 0, 7);
        
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

void lightOFF(CRGB leds[], int NUM_LEDS)
{
    fill_solid(leds,NUM_LEDS,CRGB::Black);
}