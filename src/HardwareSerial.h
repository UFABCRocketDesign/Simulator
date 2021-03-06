#ifndef _HARDWARESERIAL_H
#define _HARDWARESERIAL_H

#ifndef ARDUINO

#include "Stream.h"

class HardwareSerial : public Stream
{
public:
    HardwareSerial(std::ostream& outStream, std::istream& inStream);
private:
    int baudRate;
public:
    void begin(int bd);
};

extern HardwareSerial Serial;

#endif
#endif
