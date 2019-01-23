#ifndef ARDUINO

#include "simulator.h"

namespace simulator
{
    PinIO pins[pinAmount];

    std::chrono::time_point<std::chrono::high_resolution_clock> Ti; // Initial time
    std::chrono::time_point<std::chrono::high_resolution_clock> Tc; // Current time
}

void simulator::showPinsMode(std::ostream& out, unsigned long long I)
{
    out << I << "\tM[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].mode<0) out << "_";
        else out << (pins[i].mode);
        out << (pinAmount-1!=i?", ":"");
    }
    out << "]" << std::endl;
}

void simulator::showPinsOutput(std::ostream& out, unsigned long long I)
{
    out << I << "\tO[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].output<0) out << "_";
        else out << (pins[i].output);
        out << (pinAmount-1!=i?", ":"");
    }
    out << "]" << std::endl;
}

void simulator::showPinsInput(std::ostream& out, unsigned long long I)
{
    out << I << "\tI[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].input<0) out << "_";
        else out << (pins[i].input);
        out << (pinAmount-1!=i?", ":"");
    }
    out << "]" << std::endl;
}

bool digitalRead(int pin)
{
    if( -1 != simulator::pins[pin].mode ) return simulator::pins[pin].input;
    return HIGH;
}

void digitalWrite(int pin, int state)
{
    simulator::pins[pin].output = state;
    if(simulator::pins[pin].mode == OUTPUT) simulator::pins[pin].input = state;
}

void pinMode(int pin, int mode)
{
    simulator::pins[pin].mode = mode;
    if(mode == INPUT_PULLUP)
    {
        simulator::pins[pin].output = HIGH;
        simulator::pins[pin].input = HIGH;
    }
}

int analogRead(int pin)
{
    if( -1 != simulator::pins[pin].mode ) return simulator::pins[pin].input;
    return HIGH;
}

void analogWrite(int pin, int value)
{
    simulator::pins[pin].output = value;
}

// Time
void delay(unsigned long ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void delayMicroseconds(unsigned long us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
unsigned long micros()
{
    simulator::Tc = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(simulator::Tc - simulator::Ti).count();
}

unsigned long millis()
{
    simulator::Tc = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(simulator::Tc - simulator::Ti).count();
}

// Math
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Characters
bool isAlpha(char x)
{
    return isalpha(x);
}
bool isAlphaNumeric(char x)
{
    return isalnum(x);
}
bool isAscii(char x)
{
    return (0x00 <= x) && (0x7F >= x);
}
bool isControl(char x)
{
    return iscntrl(x);
}
bool isDigit(char x)
{
    return isdigit(x);
}
bool isGraph(char x)
{
    return isgraph(x);
}
bool isHexadecimalDigit(char x)
{
    return isxdigit(x);
}
bool isLowerCase(char x)
{
    return islower(x);
}
bool isPrintable(char x)
{
    return isprint(x);
}
bool isPunct(char x)
{
    return ispunct(x);
}
bool isSpace(char x)
{
    return (x == ' ');
}
bool isUpperCase(char x)
{
    return isupper(x);
}
bool isWhitespace(char x)
{
    return isspace(x);
}

// Random Numbers
long random(long max)
{
    return (rand() % max);
}
long random(long min, long max)
{
    return min + (rand() % (max-min));
}
void randomSeed(unsigned long seed)
{
    srand(seed);
}

//Bits and Bytes
long bit(long n)
{
    return (1 << n);
    // return pow(2,n); jeito simples, porem nao eficiente
}
void bitClear(long &x, int n)
{
    // 0b1 poderia ser 1, mas esta em binario por ser "profissional"
    x &= ~(0b1 << n);
    /*
     * _______1_____ =        0x01 << n
     * _______0_____ =      ~(0X01 << n)
     * 1011010101011 = x
     * 1011010001011 = x &= ~(0X01 << n)
     */
}
bool bitRead(long &x, int n)
{
	return ((x & (0b1 << n)) >> n);
/*
     * _______1_____ =      0x01 << n
     * 1011010#01011 = x
     * _______#_____ = x & (0X01 << n)
     * ____________# = (x & (0X01 << n))>>n
     */

    /* long y;
    y = x;
	y &= (0x01 << n);
    return y == 0x00 ? 0 : 1;

    jeito burro
*/
}
void bitSet(long &x, int n)
{
    x |= (0b1 << n);
    /*
     * _______1_____ =        0x01 << n
     * 0101101001011 = x
     * 0101101101011 = x &= ~(0X01 << n)
     */
}
void bitWrite(long &x, int n, bool b)
{
    x = b ? x|(0X01 << n) : x&~(0X01 << n);
}
char highByte(short x)
{
    return (x >> 8) & 0x00FF;
}
char lowByte(short x)
{
    return x & 0x00FF;
}

#endif