#ifndef ARDUINO
#include "HardwareSerial.h"

HardwareSerial::HardwareSerial(std::ostream& outStream, std::istream& inStream) : Stream(outStream, inStream)
{

}

void HardwareSerial::begin(int bd)
{
    baudRate = bd;
}

HardwareSerial Serial(std::cerr, std::cin);
#endif