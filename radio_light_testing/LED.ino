#include "LED.h"
CRGB leds[NUM_LEDS];          // create neopixel array
byte LEDmode = 0;
void startLED()
{
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  FastLED.setMaxPowerInMilliWatts(1000);
}
void setColor(int hue)
{

  leds[0] = CHSV(hue, 255, 255);
  FastLED.show();

}
void dark()
{
  leds[0] = CRGB::Black;
  FastLED.show();

}
void setMode(byte m)
{
  LEDmode = m;
}
void showMode(byte hue, byte seconds)
{
  if (LEDmode == 0)
  {
    fill_rainbow(leds, NUM_LEDS, hue, 2);
    FastLED.show();
  }
  else if (LEDmode == 1)
  {
    if (seconds % 2 == 0) fill_solid(leds, NUM_LEDS, CRGB::White);

    else fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
  }
  else if (LEDmode == 2)
  {
    if (seconds % 1 == 0)
    {
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
    }
    if (seconds % 2 == 0)
    {
      fill_solid(leds, NUM_LEDS, CRGB::Green);
      FastLED.show();
    }
    else if ( seconds % 3 == 0)
    {
      fill_solid(leds, NUM_LEDS, CRGB::Blue);
      FastLED.show();
    }
  }
}
