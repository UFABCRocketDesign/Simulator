#ifndef ARDUINO
#include "HardwareSerial.h"

void HardwareSerial::begin(int bd)
{
    baudRate = bd;
}

HardwareSerial Serial;
#endif