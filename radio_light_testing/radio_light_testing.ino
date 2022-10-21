//10/19/2022
//Nathan Normand
#include "GPS.h"
#include "LED.h"

#define BUTTON 5
#define PPS 12
#define MODES 3
byte mode = 0;
byte hue = 0;
byte s;
byte m;
byte h;
byte startModeTime;
float vBatt;
boolean isAsleep = false;
void testBatt()
{
  vBatt = analogRead(A9);
  if (vBatt < 500)
  {
    radioSleep();
    isAsleep = true;
    dark();
    //Serial.println("Asleep");
  }
  else
  {
    radioWake();
    isAsleep = false;
    //Serial.println("Awake");
  }
}
void setup()
{
  delay(1000);
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(PPS, INPUT);
  startGPS();
  startLED();
  startRadio();
  //Serial.println("got here");
  while (!gotGPS)
  {
    readGPS();
  }
  //Serial.println("got past");
  
}


void loop()
{
  if (millis() % 10000 == 0) { // check battery voltage every 10 seconds
    testBatt();
  }
  
  if (!isAsleep) // while the battery has enough charge
  {
    readGPS(); // read incoming gps signals
    
    if (timeout()) {
      receive(mode, startModeTime, hue);
    }
    
    if (digitalRead(PPS))// GPS pulses every second on the second
    {
      s = getGPSs();
      Serial.print("time = ");Serial.println(s);
      if (s == startModeTime) 
      {
        //Serial.print("pulse ="); Serial.println(pulse);
        
        setMode(mode);
       //Serial.print("hue ="); Serial.println(hue);
       // Serial.print("mode ="); Serial.println(mode);
      }
      showMode(hue, s);
    }
    //Serial.println(digitalRead(PPS));
    checkButton();
  }
}
void checkButton()
{
  if (!digitalRead(BUTTON))
  {
    int s = getGPSs();
    mode++;
    if (mode > MODES) mode = 1;
    startModeTime = (s + 3);
    if(startModeTime > 59) startModeTime -= 60;
    hue = map(s, 1, 60, 1, 255);
    transmit(mode, s, hue);
    //Serial.println("ssss");
    //setColor(hue);
  }
}
