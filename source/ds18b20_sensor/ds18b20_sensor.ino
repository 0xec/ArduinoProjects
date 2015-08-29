/*
 Name:      DS18b20.ino
 Created:   2015/8/18 19:37:35
 Author:    xec
*/

// the setup function runs once when you press reset or power the board
#include "CDS18B20.h"

CTemperatureSensor sensor(9);
void setup()
{
    Serial.begin(9600);
    if (!sensor.init()) {
        Serial.println("initialize ds18b20 fail");
    } else {
        Serial.println("initialize completed");
    }
}

// the loop function runs over and over again until power down or reset
void loop()
{
    float v = sensor.read();
    Serial.print("temp=");
    Serial.println(v);
    delay(1000);
}
