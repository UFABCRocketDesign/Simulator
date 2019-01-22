#ifndef ARDUINO

#include "simulator.h"

namespace simulator
{
    Pin pins[pinAmount];
}

void simulator::showPinsMode()
{
    cout << "M[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].mode<0) cout << "_";
        else cout << (pins[i].mode);
        cout << (pinAmount-1!=i?", ":"");
    }
    cout << "]" << endl;
}

void simulator::showPinsState()
{
    cout << "S[";
    for(int i = 0; i < pinAmount; i++)
    {
        if (pins[i].state<0) cout << "_";
        else cout << (pins[i].state);
        cout << (pinAmount-1!=i?", ":"");
    }
    cout << "]" << endl;
}

void HardwareSerial::begin(int bd)
{
    baudRate = bd;
}
//println(string S)
void HardwareSerial::println(string p)
{
    cout << p << endl;
}

HardwareSerial Serial;

void pinMode(int pin, int mode)
{
    simulator::pins[pin].mode = mode;
}

void digitalWrite(int pin, int state)
{
    simulator::pins[pin].state = state;
}

void analogWrite(int pin, int value)
{
    simulator::pins[pin].state = value;
}

// Math
template<typename T> T constrain(T x, T a, T b)
{
    if(x < a) return a;
    if(x > b) return b;
    return x;
}

template<typename T> T max(T x, T y)
{
    return (x > y) ? (x) : (y);
}

template<typename T> T min(T x, T y)
{
    return (x < y) ? (x) : (y);
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T> T sq(T x)
{
    return x * x;
}

//Characters
bool IsAlpha(char x)
{
    return isalpha(x);
}
bool isAlphaNumeric(char x)
{
    return isalnum(x);
}
/*bool isAscii(char x)
{

}
*/
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
	//x = ~((~(long(b)) << n) ^ x);

    /*
	 * 000000000000b =         b
     * 0000000b00000 =         b << n
     * 1111111q11111 =       ~(b << n)
     * 1011010101011 =   x
     * 0100101q10100 =   x ^ ~(b << n)
     * 1011010b01011 = ~(x ^ ~(b << n))
     */

	if (b) x |= (0X01 << n);
    else x &= ~(0X01 << n);
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