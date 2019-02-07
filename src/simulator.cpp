#ifndef ARDUINO

#include "simulator.h"

namespace simulator
{
    PinIO pins[pinAmount];

    Terminal terms[] =
    {
        {0,	19, PIN,	21},
        {1,	19, PIN,	21},
        {2,	19, other,  -1},
        {3,	19, GND,	-1},
        {4,	0,  NC,	-1},
        {4,	15,	LED,	13},
        {4,	19, PIN,	13},
        {5,	0,	other,	-1},
        {5,	19, PIN,	12},
        {6,	0,	RS,	-1},
        {6,	19, PIN,	11},
        {7,	0,	V3_3,	-1},
        {7,	19, PIN,	10},
        {8,	0,	V5,	-1},
        {8,	19, PIN,	9},
        {9,	0,	GND,	-1},
        {9,	19, PIN,	8},
        {10,	0,	GND,	-1},
        {11,	0,	RAW,	-1},
        {11,	19,	PIN,	7},
        {12,	19,	PIN,	6},
        {13,	0,	PIN,	54},
        {13,	19,	PIN,	5},
        {14,	0,	PIN,	55},
        {14,	19,	PIN,	4},
        {15,	0,	PIN,	56},
        {15,	19,	PIN,	3},
        {16,	0,	PIN,	57},
        {16,	19,	PIN,	2},
        {17,	0,	PIN,	58},
        {17,	19,	PIN,	1},
        {18,	0,	PIN,	59},
        {18,	9,	RS,	-1},
        {18,	10,	PIN,	52},
        {18,	11,	PIN,	50},
        {18,	19,	PIN,	0},
        {19,	0,	PIN,	60},
        {19,	9,	GND,	-1},
        {19,	10,	PIN,	51},
        {19,	11,	V5,	-1},
        {20,	0,	PIN,	61},
        {20,	19,	PIN,	14},
        {21,	19,	PIN,	15},
        {22,	0,	PIN,	62},
        {22,	19,	PIN,	16},
        {23,	0,	PIN,	63},
        {23,	19,	PIN,	17},
        {24,	0,	PIN,	64},
        {24,	19,	PIN,	18},
        {25,	0,	PIN,	65},
        {25,	19,	PIN,	19},
        {26,	0,	PIN,	66},
        {26,	19,	PIN,	20},
        {27,	0,	PIN,	67},
        {27,	19,	PIN,	21},
        {28,	0,	PIN,	68},
        {29,	0,	PIN,	69},
        {30,	2,	V5,	-1},
        {30,	3,	PIN,	52},
        {30,	4,	PIN,	50},
        {30,	5,	PIN,	48},
        {30,	6,	PIN,	46},
        {30,	7,	PIN,	44},
        {30,	8,	PIN,	42},
        {30,	9,	PIN,	40},
        {30,	10,	PIN,	38},
        {30,	11,	PIN,	36},
        {30,	12,	PIN,	34},
        {30,	13,	PIN,	32},
        {30,	14,	PIN,	30},
        {30,	15,	PIN,	28},
        {30,	16,	PIN,	26},
        {30,	17,	PIN,	24},
        {30,	18,	PIN,	22},
        {30,	19,	GND,	-1},
        {31,	2,	V5,	-1},
        {31,	3,	PIN,	53},
        {31,	4,	PIN,	51},
        {31,	5,	PIN,	49},
        {31,	6,	PIN,	47},
        {31,	7,	PIN,	45},
        {31,	8,	PIN,	43},
        {31,	9,	PIN,	41},
        {31,	10,	PIN,	39},
        {31,	11,	PIN,	37},
        {31,	12,	PIN,	35},
        {31,	13,	PIN,	33},
        {31,	14,	PIN,	31},
        {31,	15,	PIN,	29},
        {31,	16,	PIN,	27},
        {31,	17,	PIN,	25},
        {31,	18,	PIN,	23},
        {31,	19,	GND,	-1},
    };

	std::thread diagramThread;

	std::ostream& simuOut = std::cerr;

    std::chrono::time_point<std::chrono::high_resolution_clock> Ti; // Initial time
    std::chrono::time_point<std::chrono::high_resolution_clock> Tc; // Current time

    std::mutex mtx;
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

void simulator::showPinsDiagram()
{
	simuOut << "\x1b[s";
	for(Terminal t : terms) simuOut << "\x1b[" << t.x+5 << ";" << t.y*2+5 << "fo";
	simuOut << "\x1b[u";
	while(1)
    {
        simuOut << "\x1b[s";
		simuOut << "\x1b[?25l\x1b[H";
		showPinsOutput(simuOut, 0);
		showPinsInput(simuOut, 0);
		showPinsMode(simuOut, 0);
        for(Terminal& t : terms)
        {
            simuOut << "\x1b[" << t.x+5 << ";" << t.y*2+5 << "f";
            switch(t.type)
            {
                case PIN:
                    if(t.lastState != pins[t.pinIO].output)
                    {
                        simuOut << "\x1b[38;2;";
                        switch(pins[t.pinIO].output)
                        {
                            case 1: 	simuOut << "0;255;0"; break;
                            case 0: 	simuOut << "255;0;0"; break;
                            default:	simuOut << "0;0;255";
                        }
                        simuOut << "mo";
						t.lastState = pins[t.pinIO].output;
                    }
                    break;
                case LED:
                    if(t.lastState != pins[t.pinIO].output)
                    {
                        simuOut << "\x1b[38;2;";
                        switch(pins[t.pinIO].output)
                        {
                            case 0: 	simuOut << "255;0;0"; break;
                            case 1: 	simuOut << "0;255;0"; break;
                            default:	simuOut << "0;0;255";
                        }
                        simuOut << "m#";
						t.lastState = pins[t.pinIO].output;
                    }
                    break;
                default:;
            }
            simuOut << "\x1b[m";
        }
        simuOut << "\x1b[u";
    }
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