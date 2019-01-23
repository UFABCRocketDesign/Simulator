#ifndef ARDUINO

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "simulator.h"

#include "Simulator.ino"

std::fstream pinsOutput ("pinsOutputLog.log", std::fstream::out);
std::fstream pinsInput  ("pinsInputLog.log", std::fstream::out);
std::fstream pinsMode   ("pinsModeLog.log", std::fstream::out);

int main(int argc, char *argv[])
{
    simulator::Ti = std::chrono::high_resolution_clock::now();
    simulator::Tc = std::chrono::high_resolution_clock::now();
    setup();
    for(unsigned long long i = 0; i < 300; i++)
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