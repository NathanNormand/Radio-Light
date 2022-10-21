#include"GPS.h"
Adafruit_GPS GPS(&GPSSerial);

//GPS.read() needs to be read very often to get gps signals
//GPS is 7 hours ahead of west coast
byte sec;
void startGPS()
{
  GPS.begin(9600);//9600 is default for the gps serial port approx 1Hz
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // 
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  
  
  //Serial.println("GPS start success");
}
void DebugGPS()
{
  char c = GPS.read();
  //if(c) Serial.print(c);
}

void readGPS()//fix this
{
  char c = GPS.read();
  if (GPS.newNMEAreceived())
  {
    
    if (!GPS.parse(GPS.lastNMEA())) return;
   // Serial.print(GPS.lastNMEA());
  }
}

long getLon()
{
  //Serial.println(GPS.longitude);
  return(GPS.longitude);
}

long getLat()
{
  return(GPS.latitude);
}

byte getGPSs()
{
  sec = GPS.seconds + GPS.milliseconds / 1000. + GPS.secondsSinceTime();
  sec = sec%60;
  //s++;
  return(sec);
}

byte getGPSm()
{
  return GPS.minute;
}

byte getGPSh()
{
  return GPS.hour;
}

byte getGPSd()
{
  return GPS.day;
}

void GPSsleep()//make gps sleep
{
  
}
boolean gotGPS()
{
  //Serial.println("TESTING GPS SIGNAL");
  readGPS();
  if(getLon() > 1) return true;
  else return false;
}
