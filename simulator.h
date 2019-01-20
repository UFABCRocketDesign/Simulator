#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#ifndef ARDUINO

#include <iostream>
#include <string>

#define HIGH 1
#define LOW 0

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

using namespace std;

namespace simulator
{
    const int pinAmount = 10;
    struct Pin
    {
        int state = -1;
        int mode = -1;
    };

    void showPinsState();
    void showPinsMode();
}

class HardwareSerial
{
    int baudRate;
public:
    void begin(int bd);
    void println(string S);
};

extern HardwareSerial Serial;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int state);
void analogWrite(int pin, int value);

#endif
#endif