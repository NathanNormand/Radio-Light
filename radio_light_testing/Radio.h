#include <RH_RF69.h>
#define RF69_FREQ 915.0   //radios much match frequency
#define RFM69_CS      8   // Feather 32u4
#define RFM69_INT     7   //
#define RFM69_RST     4



void startRadio();
void transmit(byte mode, byte modeStart, byte hue);
void receive(byte & m, byte & i, byte & h);
boolean timeout();
void radioWake();
void radioSleep();
