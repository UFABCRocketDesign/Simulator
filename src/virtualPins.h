#ifndef ARDUINO

#include <cstdint>

#if !(defined(ARDUINO_MEGA))

#define NUM_DIGITAL_PINS            20
#define NUM_ANALOG_INPUTS           6
#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 14 : -1)

#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11)

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

#define PIN_WIRE_SDA        (18)
#define PIN_WIRE_SCL        (19)

#elif defined(ARDUINO_MEGA)

#define NUM_DIGITAL_PINS            70
#define NUM_ANALOG_INPUTS           16
#define analogInputToDigitalPin(p)  ((p < 16) ? (p) + 54 : -1)
#define digitalPinHasPWM(p)         (((p) >= 2 && (p) <= 13) || ((p) >= 44 && (p)<= 46))

#define PIN_SPI_SS    (53)
#define PIN_SPI_MOSI  (51)
#define PIN_SPI_MISO  (50)
#define PIN_SPI_SCK   (52)

#define PIN_WIRE_SDA        (20)
#define PIN_WIRE_SCL        (21)

#endif

#if (0<NUM_ANALOG_INPUTS)
#define PIN_A0   (analogInputToDigitalPin(0))
static const uint8_t A0 = PIN_A0;
#endif

#if (1<NUM_ANALOG_INPUTS)
#define PIN_A1   (analogInputToDigitalPin(1))
static const uint8_t A1 = PIN_A1;
#endif

#if (2<NUM_ANALOG_INPUTS)
#define PIN_A2   (analogInputToDigitalPin(2))
static const uint8_t A2 = PIN_A2;
#endif

#if (3<NUM_ANALOG_INPUTS)
#define PIN_A3   (analogInputToDigitalPin(3))
static const uint8_t A3 = PIN_A3;
#endif

#if (4<NUM_ANALOG_INPUTS)
#define PIN_A4   (analogInputToDigitalPin(4))
static const uint8_t A4 = PIN_A4;
#endif

#if (5<NUM_ANALOG_INPUTS)
#define PIN_A5   (analogInputToDigitalPin(5))
static const uint8_t A5 = PIN_A5;
#endif

#if (6<NUM_ANALOG_INPUTS+2)
#define PIN_A6   (analogInputToDigitalPin(6))
static const uint8_t A6 = PIN_A6;
#endif

#if (7<NUM_ANALOG_INPUTS+2)
#define PIN_A7   (analogInputToDigitalPin(7))
static const uint8_t A7 = PIN_A7;
#endif

#if (8<NUM_ANALOG_INPUTS)
#define PIN_A8   (analogInputToDigitalPin(8))
static const uint8_t A8 = PIN_A8;
#endif

#if (9<NUM_ANALOG_INPUTS)
#define PIN_A9   (analogInputToDigitalPin(9))
static const uint8_t A9 = PIN_A9;
#endif

#if (10<NUM_ANALOG_INPUTS)
#define PIN_A10  (analogInputToDigitalPin(10))
static const uint8_t A10 = PIN_A10;
#endif

#if (11<NUM_ANALOG_INPUTS)
#define PIN_A11  (analogInputToDigitalPin(11))
static const uint8_t A11 = PIN_A11;
#endif

#if (12<NUM_ANALOG_INPUTS)
#define PIN_A12  (analogInputToDigitalPin(12))
static const uint8_t A12 = PIN_A12;
#endif

#if (13<NUM_ANALOG_INPUTS)
#define PIN_A13  (analogInputToDigitalPin(13))
static const uint8_t A13 = PIN_A13;
#endif

#if (14<NUM_ANALOG_INPUTS)
#define PIN_A14  (analogInputToDigitalPin(14))
static const uint8_t A14 = PIN_A14;
#endif

#if (15<NUM_ANALOG_INPUTS)
#define PIN_A15  (analogInputToDigitalPin(15))
static const uint8_t A15 = PIN_A15;
#endif


#define LED_BUILTIN 13

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;


#endif