//10/7/2022
#include "Arduino.h"
#include "RH_RF69.h"
#include "Wire.h"
#include"RTClib.h"
#include "FastLED.h"
#include "testBatt.h"
#include "lightUp.h"



#define RF69_FREQ 915.0   //radios much match frequency
#define RFM69_CS      8   // Feather 32u4
#define RFM69_INT     7   //
#define RFM69_RST     4
#define NUM_LEDS 64       // total number of neopixels
#define DATA_PIN 6        // pin for neopixels
#define BUTTON 5          // momentary button
#define MODES 2           // total number of led modes minus 1 



CRGB leds[NUM_LEDS]; // define neopixel array
RH_RF69 rf69(RFM69_CS, RFM69_INT); // define radio, pins will always be the same
RTC_DS3231 rtc;

uint8_t buf[RH_RF69_MAX_MESSAGE_LEN]; // variables that will be used in receive 
uint8_t len = sizeof(buf); // variables that will be used in receive

int mode = 0;

void setup() {
  delay(250);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  FastLED.setMaxPowerInMilliWatts(1000);
  pinMode(BUTTON, INPUT_PULLUP);

  DateTime now = rtc.now();

  digitalWrite(RFM69_RST,HIGH);// reset radio on pin 4
  delay(10);
  digitalWrite(RFM69_RST,LOW);// reset radio on pin 4
  delay(10);


  if(!rf69.init())
  {
    Serial.println("RFM69 radio init failed");
  } 
  Serial.println("RFM radio init OK!");

  if(!rf69.setFrequency(RF69_FREQ))
  {
    Serial.println("setFrequency failed");
  }
  rf69.setTxPower(14,true);

  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);//key must match between all used boards
  
}

void loop() {
  EVERY_N_SECONDS(10) 
  {
    if(!testBatt())
    {
      rf69.sleep(); // put the radio to sleep to conserve power
      lightOFF(leds, NUM_LEDS);// tuen lights off to conserve power
    }
   else rf69.available(); // make radio available to receive messages
  }
  while(testBatt()) // while battery is charged
  {
    if(rf69.waitAvailableTimeout(100)) 
    {
     if(! rf69.recv(buf, &len))
     {
      Serial.println("Receive failed ");
      return;
     }
     rf69.printBuffer("Received: ", buf, len);
     buf[len] = 0; // set last variable to 0
     Serial.print((char*)buf); Serial.println("*");
     Serial.print("Got: "); Serial.println((char*)buf);
     Serial.print("RSSI: "); Serial.println(rf69.lastRssi(), DEC);
     mode = buf[0]; // the first variable is our light mode
     //need to add times to this!!!!
    }
    if(! digitalRead(BUTTON)) //read button 
    {
      mode++;// when button is pressed switch modes
      if(mode > MODES) mode = 0; //loop back to beginning of modes list

      Serial.println("Button pressed!");
      char radiopacket[2]; // this will have to be bigger once time is implemented
      radiopacket[0] = mode; // set first variable to led mode
      radiopacket[1] = 0; // make LAST variable blank
      //this needs to be updated to add time!!!
      Serial.print("Sending "); Serial.println(radiopacket);
      rf69.send((uint8_t*)radiopacket,strlen(radiopacket));
      rf69.waitPacketSent(); // wait until the radio is done transmitting
    }


    lightUp(leds,  NUM_LEDS,  mode);

  }
  

}