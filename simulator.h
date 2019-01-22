#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#ifndef ARDUINO

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
//#include <ctime>
#include <cctype>

#define HIGH 1
#define LOW 0

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

using namespace std;

namespace simulator
{
    const int pinAmount = 10;
    struct Pin
    {
        int state = -1;
        int mode = -1;
    };

    void showPinsState();
    void showPinsMode();
}

class HardwareSerial
{
    int baudRate;
public:
    void begin(int bd);
    void println(string p);
};

extern HardwareSerial Serial;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int state);
void analogWrite(int pin, int value);

// Math
// abs() Done by cmath
template<typename T> T constrain(T x, T a, T b);
long map(long x, long in_min, long in_max, long out_min, long out_max);
template<typename T> T max( T x, T y);
template<typename T> T min(T x, T y);
// pow() Done by cmath
template<typename T> T sq(T x);
// sqrt() Done by cmath

/* Trigonometry
    Done by cmath
*/

//Characters
bool IsAlpha(char x);
bool isAlphaNumeric(char x);
//bool isAscii(char x);
bool isControl(char x);
bool isDigit(char x);
bool isGraph(char x);
bool isHexadecimalDigit(char x);
bool isLowerCase(char x);
bool isPrintable(char x);
bool isPunct(char x);
bool isSpace(char x);
bool isUpperCase(char x);
bool isWhitespace(char x);

// Random Numbers
long random(long max);
long random(long min, long max);
void randomSeed(unsigned long seed);

// Bits and Bytes
long bit(long n);
void bitClear(long &x, int n);
bool bitRead(long x, int n);
void bitSet(long &x, int n);
void bitWrite(long &x, int n, bool b);
char highByte(long x);
char lowByte(long x);


#endif
#endif