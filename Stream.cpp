#ifndef ARDUINO

#include "Stream.h"

Stream::Stream(std::ostream& stream) : Print(stream), output(stream)
{

}

#endif