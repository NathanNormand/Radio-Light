//10/7/2022

#include"RTClib.h"
#include "testBatt.h"
#include "lightUp.h"
#include "receive.h"

#define BUTTON 5          // momentary button
#define MODES 2           // total number of led modes minus 1 

RTC_DS3231 rtc;
int mode = 0;

void setup() {
  delay(250);
  Serial.begin(9600);
  
  pinMode(BUTTON, INPUT_PULLUP);
  //DateTime now = rtc.now();
  setLights(); // initialize FastLED
  setRadio(); // initialize Radio

}

void loop() {
  EVERY_N_SECONDS(10) 
  {
    if(!testBatt())
    {
      Conserve();//turn radio off to conserve power
      lightOFF();// turn lights off to conserve power
      Serial.println("asleep");
    }
   else
   {
    Serial.println("awake");
    Ready();
   }
  }
  while(testBatt()) // while battery is charged
  {
    Receive();
    if(! digitalRead(BUTTON)) //read button 
    {
      mode++;// when button is pressed switch modes
      if(mode > MODES) mode = 0; //loop back to beginning of modes list

      Serial.println("Button pressed!");
     Transmit(mode);
    }

    mode = getMode();
    lightUp(mode);

  }
  

}
