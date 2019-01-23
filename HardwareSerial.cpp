#ifndef ARDUINO
#include "HardwareSerial.h"

HardwareSerial::HardwareSerial(std::ostream& stream) : Stream(stream)
{

}

void HardwareSerial::begin(int bd)
{
    baudRate = bd;
}

HardwareSerial Serial(std::cout);
#endif