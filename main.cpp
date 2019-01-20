#ifndef ARDUINO

#include "simulator.h"

#include "Simulator.ino"

int main(int argc, char *argv[])
{
    setup();
    for(int i = 0; i < 11; i++)
    //for(;;)
    {
        simulator::showPinsState();
        //simulator::showPinsMode();
        loop();
    }
    return 0;
}

#endif