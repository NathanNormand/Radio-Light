#include<Adafruit_GPS.h>
#define GPSSerial Serial1

void readGPS();
void startGPS();
void DebugGPS();
void readGPS();
long getLon();
long getLat();
byte getGPSs();
byte getGPSm();
byte getGPSh();
byte getGPSd();
void GPSsleep();
boolean gotGPS();
