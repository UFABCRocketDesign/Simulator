#ifndef _PRINT_H
#define _PRINT_H

#ifndef ARDUINO

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <string>

#define HEX 16
#define DEC 10
#define OCT 8
#define BIN 2

typedef std::string String;

class Print
{
  private:
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);
public:

    virtual size_t write(uint8_t c);
    size_t write(const char *buffer, size_t size);

    virtual size_t write(const uint8_t *buffer, size_t size);
    size_t write(const char *str);



    // size_t print(const __FlashStringHelper *);
    size_t print(const String &);
    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);
    // size_t print(const Printable&);

    // size_t println(const __FlashStringHelper *);
    size_t println(const String &s);
    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
    // size_t println(const Printable&);
    size_t println(void);

};

#endif
#endif
