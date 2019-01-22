#ifndef ARDUINO

#include <iostream>
#include <fstream>
#include "simulator.h"

#include "Simulator.ino"

std::fstream pinsOutput ("pinsOutputLog.log", std::fstream::out);
std::fstream pinsInput  ("pinsInputLog.log", std::fstream::out);
std::fstream pinsMode   ("pinsModeLog.log", std::fstream::out);

int main(int argc, char *argv[])
{
    setup();
    for(unsigned long long i = 0; i < 30; i++)
    //for(;;)
    {
        simulator::showPinsOutput(pinsOutput, i);
        simulator::showPinsInput(pinsInput, i);
        simulator::showPinsMode(pinsMode, i);
        loop();
    }
    return 0;
}

#endif