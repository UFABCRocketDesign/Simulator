#ifndef _HARDWARESERIAL_H
#define _HARDWARESERIAL_H

#ifndef ARDUINO

#include "Stream.h"

class HardwareSerial : public Stream
{
public:
	HardwareSerial(std::ostream& outStream, std::istream& inStream, unsigned int rxPin, unsigned int txPin);
private:
	unsigned int baudRate;
	const unsigned int pinRX;
	const unsigned int pinTX;
public:
	void begin(int bd);
};

extern HardwareSerial Serial;

#endif
#endif
