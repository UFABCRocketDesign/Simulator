#ifndef ARDUINO
#include "HardwareSerial.h"

HardwareSerial::HardwareSerial(std::ostream& outStream, std::istream& inStream, unsigned int rxPin, unsigned int txPin) : Stream(outStream, inStream), pinRX(rxPin), pinTX(txPin)
{

}

void HardwareSerial::begin(int bd)
{
	baudRate = bd;
	pinMode(pinRX, INPUT);
	pinMode(pinTX, OUTPUT);

}

// HardwareSerial Serial(std::cerr, std::cin);
HardwareSerial Serial(simulator::serial0fOutput, std::cin, 0, 1);
#endif