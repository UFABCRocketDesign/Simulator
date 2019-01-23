#ifndef _STRAEM_H
#define _STRAEM_H

#ifndef ARDUINO

#include <iostream>

#include "Print.h"

class Stream : public Print
{
public:
    Stream(std::ostream& stream);
private:
    std::ostream& output;
};

#endif
#endif
