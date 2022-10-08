#include <Arduino.h>
bool testBatt()
{
    float vBatt = analogRead(A9); // battery voltage divider connected to pin A9
    if(vBatt < 500) //  500 is dead battery 650 is full
    {
        Serial.println("asleep");
    }
    else Serial.println("awake");

}