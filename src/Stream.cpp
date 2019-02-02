#ifndef ARDUINO

#include "Stream.h"

Stream::Stream(std::ostream& outStream, std::istream& inStream) : Print(outStream), output(outStream), input(inStream)
{
    future = std::async(std::launch::async, &Stream::GetInput, this);
    inputColectorThread = std::thread(&Stream::inputColector, this);
}

std::string Stream::GetInput()
{
    std::string S;
    std::getline(input, S);
    return S;
}

void Stream::inputColector()
{
    while(1)
    {
        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            simulator::mtx.lock();
            buffer << future.get();
            simulator::mtx.unlock();
            future = std::async(std::launch::async, &Stream::GetInput, this);
        }
    }
}

int Stream::available()
{
    return buffer.rdbuf()->in_avail();
}

int Stream::read()
{
    int ret = -1;
    simulator::mtx.lock();
    if(buffer.rdbuf()->in_avail()>0) ret = buffer.get();
    else buffer.str("");
    simulator::mtx.unlock();
    return ret;
}

int Stream::peek()
{
    int ret = -1;
    simulator::mtx.lock();
    if(buffer.rdbuf()->in_avail()>0) ret = buffer.peek();
    simulator::mtx.unlock();
    return ret;
}

#endif