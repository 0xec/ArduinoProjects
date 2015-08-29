//
//
//

#include "CDS18B20.h"

CTemperatureSensor::CTemperatureSensor(int SensorPin)
{
    m_SensorPin = SensorPin;

}

bool CTemperatureSensor::init()
{
    pinMode(m_SensorPin, OUTPUT);

    bool rst = resetCommand();
    if (rst) {
        writeCommand(0xCC);
        writeCommand(0x44);
    }
    return rst;
}

float CTemperatureSensor::read()
{
    int t = -1;
    uint8_t lsb, msb;
    bool rst = false;

    rst = resetCommand();
    if (!rst) {
        return -1;
    }

    writeCommand(0xCC);
    writeCommand(0x44);

    rst = resetCommand();
    if (!rst) {
        return -1;
    }

    writeCommand(0xCC);
    writeCommand(0xBE);

    lsb = readValue();
    msb = readValue();

    t = (msb << 8) + lsb;

    return t * 0.0625f;
}

bool CTemperatureSensor::resetCommand()
{
    digitalWrite(m_SensorPin, LOW);
    delayMicroseconds(500);
    digitalWrite(m_SensorPin, HIGH);
    delayMicroseconds(60);
    int level = digitalRead(m_SensorPin);
    delayMicroseconds(5000);
    return (level == LOW);
}

void CTemperatureSensor::writeCommand(unsigned char cmd)
{
    unsigned char mask = 0x01;
    for (mask = 0x01; mask != 0; mask <<= 1) {
        digitalWrite(m_SensorPin, LOW);
        delayMicroseconds(2); // delay 2us;
        if ((mask & cmd) == 0) {
            digitalWrite(m_SensorPin, LOW);
        } else {
            digitalWrite(m_SensorPin, HIGH);
        }

        delayMicroseconds(60);
        digitalWrite(m_SensorPin, HIGH);
    }
}

uint8_t CTemperatureSensor::readValue()
{
    uint8_t data = 0;
    uint8_t mask;

    for (mask = 0x01; mask != 0; mask <<= 1) {
        digitalWrite(m_SensorPin, LOW);
        delayMicroseconds(2);
        digitalWrite(m_SensorPin, HIGH);
        delayMicroseconds(2);
        if (HIGH == digitalRead(m_SensorPin)) {
            data |= mask;
        } else {
            data &= ~mask;
        }
        delayMicroseconds(60);
    }

    return data;
}

