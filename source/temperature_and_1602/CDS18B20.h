// CDS18B20.h

#ifndef _CDS18B20_h
#define _CDS18B20_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class CTemperatureSensor
{
  protected:


  public:
    CTemperatureSensor(int SensorPin);
    bool init();
    float  read();


  protected:
    bool resetCommand();
    void writeCommand(unsigned char cmd);
    uint8_t readValue();

  private:
    int m_SensorPin;
};


#endif

