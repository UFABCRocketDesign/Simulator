#ifndef _STREAM_H
#define _STREAM_H

#ifndef ARDUINO

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <future>
#include <string>

#include "simulator.h"
#include "Print.h"

class Stream : public Print
{
public:
    Stream(std::ostream& outStream, std::istream& inStream);
    ~Stream();
private:
    std::ostream& output;
    std::istream& input;
    std::stringstream buffer;

    std::future<std::string> future;
    std::string GetInput();
    void inputColector();

    bool threadTerminate = false;
    std::thread inputColectorThread;

public:
    virtual int available();
    virtual int read();
    virtual int peek();
};

#endif
#endif
