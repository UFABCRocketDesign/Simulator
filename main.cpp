#ifndef ARDUINO

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>

#include "src/simulator.h"
#include "src/HardwareSerial.h"

#define _TARGET_INO "Target/Target.ino"

#include _TARGET_INO

std::fstream pinsOutput ("pinsOutputLog.log", std::fstream::out);
std::fstream pinsInput  ("pinsInputLog.log", std::fstream::out);
std::fstream pinsMode   ("pinsModeLog.log", std::fstream::out);

int main(int argc, char *argv[])
{
    std::cerr << "\x1b[2J";
    simulator::diagramThread = std::thread(simulator::showPinsDiagram);
    simulator::Ti = std::chrono::high_resolution_clock::now();
    simulator::Tc = std::chrono::high_resolution_clock::now();
    setup();
    for(simulator::iteratarion = 0; simulator::iteratarion < 50 && !std::cin.eof(); simulator::iteratarion++)
    //for(;;)
    {
        // simulator::showPinsOutput(pinsOutput, simulator::iteratarion);
        // simulator::showPinsInput(pinsInput, simulator::iteratarion);
        // simulator::showPinsMode(pinsMode, simulator::iteratarion);
        loop();
    }
    simulator::killThreads();
    simulator::diagramThread.join();
    std::cerr << "\x1b[2J";
    if(!std::cin.eof()) std::cerr << "Press \x1b[1mEnter\x1b[m no finish";
    return 0;
}

#endif