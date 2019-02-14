#ifndef ARDUINO

#include "simulator.h"

namespace simulator
{
    PinIO pins[pinAmount];

    Terminal terms[] =
    {
        {0,	19, PIN,	PIN_WIRE_SCL},
        {1,	19, PIN,	PIN_WIRE_SDA},
        {2,	19, other,  -1},
        {3,	19, GND,	-1},
        {4,	0,  NC,	-1},
        {4,	15,	LED,	LED_BUILTIN},
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
        {13,	0,	PIN,	PIN_A0},
        {13,	19,	PIN,	5},
        {14,	0,	PIN,	PIN_A1},
        {14,	19,	PIN,	4},
        {15,	0,	PIN,	PIN_A2},
        {15,	19,	PIN,	3},
        {16,	0,	PIN,	PIN_A3},
        {16,	19,	PIN,	2},
        {17,	0,	PIN,	PIN_A4},
        {17,	19,	PIN,	1},
        {18,	0,	PIN,	PIN_A5},
        {18,	9,	RS,	-1},
        {18,	10,	PIN,	PIN_SPI_SCK},
        {18,	11,	PIN,	PIN_SPI_MISO},
        {18,	19,	PIN,	0},
        {19,	0,	PIN,	PIN_A6},
        {19,	9,	GND,	-1},
        {19,	10,	PIN,	PIN_SPI_MOSI},
        {19,	11,	V5,	-1},
        {20,	0,	PIN,	PIN_A7},
#if defined(ARDUINO_MEGA)
        {20,	19,	PIN,	14},
        {21,	19,	PIN,	15},
        {22,	0,	PIN,	PIN_A8},
        {22,	19,	PIN,	16},
        {23,	0,	PIN,	PIN_A9},
        {23,	19,	PIN,	17},
        {24,	0,	PIN,	PIN_A10},
        {24,	19,	PIN,	18},
        {25,	0,	PIN,	PIN_A11},
        {25,	19,	PIN,	19},
        {26,	0,	PIN,	PIN_A12},
        {26,	19,	PIN,	20},
        {27,	0,	PIN,	PIN_A13},
        {27,	19,	PIN,	21},
        {28,	0,	PIN,	PIN_A14},
        {29,	0,	PIN,	PIN_A15},
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
#endif
    };

	std::thread diagramThread;

    unsigned long long iteratarion;

	std::ostream& simuOut = std::cerr;

    std::chrono::time_point<std::chrono::high_resolution_clock> Ti; // Initial time
    std::chrono::time_point<std::chrono::high_resolution_clock> Tc; // Current time

    std::mutex mtx;

	bool kill_threads = false;
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
        else if(!digitalPinHasPWM(i)) out << pins[i].output;
        else out << std::hex << std::uppercase << (pins[i].output)/16 << std::nouppercase << std::dec   ;
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
        else if(analogInputToDigitalPin(0)>i) out << pins[i].input;
        else out << std::hex << std::uppercase << (pins[i].input)/16 << std::nouppercase << std::dec    ;
        out << (pinAmount-1!=i?", ":"");
    }
    out << "]" << std::endl;
}

void simulator::showPinsDiagram()
{
	simuOut << "\x1b[s";
	for(Terminal t : terms) simuOut << "\x1b[" << t.x+5 << ";" << t.y*2+5 << "fo";
	simuOut << "\x1b[u";
	while(!kill_threads)
    {
        simuOut << "\x1b[s";
		simuOut << "\x1b[?25l\x1b[H";
		showPinsOutput(simuOut, iteratarion);
		showPinsInput(simuOut, iteratarion);
		showPinsMode(simuOut, iteratarion);
        for(Terminal& t : terms)
        {
			if(t.lastState != pins[t.pinIO].output)
			{
				t.lastState = pins[t.pinIO].output;
				simuOut << "\x1b[" << t.x+5 << ";" << t.y*2+5 << "f";
				switch(t.type)
				{
					case PIN:
                        if(pins[t.pinIO].output < 0) simuOut << "\x1b[38;5;" << UNDEFINED_STATE_COLOR;
                        else if(digitalPinHasPWM(t.pinIO))
                        {
                            simuOut << "\x1b[38;2;";
                            simuOut << map(pins[t.pinIO].output, 0, 255, 0, 215) << ";";
                            simuOut << map(255-pins[t.pinIO].output, 0, 255, 0, 175) << ";";
                            simuOut << map(255-pins[t.pinIO].output, 0, 255, 0, 255 );
                        }
                        else
                        {
                            simuOut << "\x1b[38;5;";
                            switch(pins[t.pinIO].output)
                            {
                                case 0: simuOut << LOW_STATE_COLOR  ; break;
                                case 1: simuOut << HIGH_STATE_COLOR; break;
                                default: simuOut << UNDEFINED_STATE_COLOR;
                            }
                        }
						simuOut << "mo"; break;
						break;
					case LED:
                        if(!digitalPinHasPWM(t.pinIO)) simuOut << "\x1b[48;2;0;" << pins[t.pinIO].output*255 << ";0m";
                        else if(0<pins[t.pinIO].output) simuOut << "\x1b[48;2;0;" << pins[t.pinIO].output << ";0m";
                        else simuOut << "\x1b[m";
						simuOut << " "; break;
						break;
					case NC:
						simuOut << "x";
						break;
					case GND:
						simuOut << "\x1b[38;5;" << GND_COLOR << "mo";
						break;
					case V5:
						simuOut << "\x1b[38;5;" << V5_COLOR << "mo";
						break;
					case V3_3:
						simuOut << "\x1b[38;5;" << V3_3_COLOR << "mo";
						break;
					case RS:
						simuOut << "\x1b[38;5;" << RS_COLOR << "mo";
						break;
					default:;
				}
				simuOut << "\x1b[m";
			}
		}
        simuOut << "\x1b[u";
    }
}

void simulator::killThreads()
{
	kill_threads = true;
}


bool digitalRead(int pin)
{
    if( -1 != simulator::pins[pin].mode ) return simulator::pins[pin].input;
    return HIGH;
}

void digitalWrite(int pin, int state)
{
    if(digitalPinHasPWM(pin)) simulator::pins[pin].output = ((state>0) * 255);
    else simulator::pins[pin].output = (state > 0);
    if(simulator::pins[pin].mode == OUTPUT) simulator::pins[pin].input = simulator::pins[pin].output > 0;
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
    if(digitalPinHasPWM(pin)) simulator::pins[pin].output = value;
    else simulator::pins[pin].output = value/255;
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