#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#ifndef ARDUINO

#include <iostream>
#include <streambuf>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <chrono>
#include <future>
#include <cctype>
#include <thread>
#include <cmath>
#include <mutex>


#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

namespace simulator
{
    constexpr int pinAmount = 10;
    struct PinIO
    {
        int output = -1; // O
        int input = -1; // I
        int mode = -1;
    };

    extern PinIO pins[];

    extern std::chrono::time_point<std::chrono::high_resolution_clock> Ti; // Initial time
    extern std::chrono::time_point<std::chrono::high_resolution_clock> Tc; // Current time

    extern std::mutex mtx;

    void showPinsMode(std::ostream& out, unsigned long long I);
    void showPinsOutput(std::ostream& out, unsigned long long I);
    void showPinsInput(std::ostream& out, unsigned long long I);
}

// Digital I/O
bool digitalRead(int pin);
void digitalWrite(int pin, int state);
void pinMode(int pin, int mode);

// Analog I/O
int analogRead(int pin);
void analogWrite(int pin, int value);

// Time
void delay(unsigned long ms);
void delayMicroseconds(unsigned long us);
unsigned long micros();
unsigned long millis();

// Math
// abs() // Done by cmath
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
long map(long x, long in_min, long in_max, long out_min, long out_max);
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
// pow() // Done by cmath
#define sq(x) ((x)*(x))
// sqrt() // Done by cmath

// Trigonometry
// cos() // Done by cmath
// sin() // Done by cmath
// tan() // Done by cmath

//Characters
bool isAlpha(char x);
bool isAlphaNumeric(char x);
bool isAscii(char x);
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