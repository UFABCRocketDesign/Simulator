#ifndef ARDUINO

#include "simulator.h"

namespace simulator
{
    Pin pins[pinAmount];
}

void simulator::showPinsMode()
{
    cout << "M[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].mode<0) cout << "_";
        else cout << (pins[i].mode);
        cout << (pinAmount-1!=i?", ":"");
    }
    cout << "]" << endl;
}

void simulator::showPinsState()
{
    cout << "S[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].state<0) cout << "_";
        else cout << (pins[i].state);
        cout << (pinAmount-1!=i?", ":"");
    }
    cout << "]" << endl;
}

void HardwareSerial::begin(int bd)
{
    baudRate = bd;
}
void HardwareSerial::println(string S)
{
    cout << S << endl;
}

HardwareSerial Serial;

void pinMode(int pin, int mode)
{
    simulator::pins[pin].mode = mode;
}

void digitalWrite(int pin, int state)
{
    simulator::pins[pin].state = state;
}

void analogWrite(int pin, int value)
{
    simulator::pins[pin].state = value;
}


#endif