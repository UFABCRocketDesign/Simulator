#ifndef ARDUINO
#include "HardwareSerial.h"
#include "simulator.h"
#endif


void setup() // Eh executada somente uma vez
{
    pinMode(LED_BUILTIN, OUTPUT);
    /*
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);

    //math
    int val = 127;

    Serial.println(val);
    val = map(val, 0, 1023, 0, 255);
    analogWrite(9, val);

    Serial.println(val);

    int a = -127;

    Serial.println(a);
    a = abs(a);
    Serial.println(a);

    float b, c, MAX, MIN, POW, se, co, tg;

    b = sqrt(a);
    Serial.println(b);
    c = sq(b);
    Serial.println(c);
    MAX = max(a, b);
    Serial.println(MAX);
    MIN = min(a, b);
    Serial.println(MIN);
    POW = pow(a, 4);
    Serial.println(POW);
    se = sin(a);
    Serial.println(se);
    co = cos(a);
    Serial.println(co);
    tg = tan(a);
    Serial.println(tg);

    //characters
    char LET;
    bool let;

    LET = 'a';
    let = isAlpha(LET);
    Serial.println(let);
    LET = '1';
    let = isAlphaNumeric(LET);
    Serial.println(let);
    LET = 'a';
    let = isAscii(LET);
    Serial.println(let);
    LET = 'a';
    let = isControl(LET);
    Serial.println(let);
    LET = '1';
    let = isDigit(LET);
    Serial.println(let);
    LET = 'a';
    let = isGraph(LET);
    Serial.println(let);
    LET = '1';
    let = isHexadecimalDigit(LET);
    Serial.println(let);
    LET = 'a';
    let = isLowerCase(LET);
    Serial.println(let);
    LET = 'A';
    let = isUpperCase(LET);
    Serial.println(let);
    LET = 'a';
    let = isPrintable(LET);
    Serial.println(let);
    LET = 'a';
    let = isPunct(LET);
    Serial.println(let);
    LET = 'a';
    let = isWhitespace(LET);
    Serial.println(let);
    LET = ' ';
    let = isSpace(LET);
    Serial.println(let);

    //bit
    Serial.print("bit ");
    Serial.print(141, BIN);
    Serial.print(" = ");
    Serial.println(bit(141), BIN);

    long bruno = 141;
    Serial.println(bruno, BIN);
    bitClear(bruno,3);
    Serial.println(bruno, BIN);

    //random
    Serial.print("Here's a random number between 300 and 981: ");
    Serial.println(random(300, 982));
    Serial.print("Here's the same number again: ");
    Serial.println(random(300, 982));
    randomSeed(26101999);
    Serial.print("Now, this is a (hopefully) different number between 300 and 981: ");
    Serial.println(random(300, 982));
    Serial.println("I was wrong e-e");

    Serial.println("Fim do setup");
    */
}

void loop() // Fica em loop indefinidamente
{
    /*
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5)
    {
        analogWrite(LED_BUILTIN, fadeValue);
        delay(30);
    }

    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5)
    {
        analogWrite(LED_BUILTIN, fadeValue);
        delay(30);
    }*/
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
    /*
    Serial.print("Line++:\t");
    if(Serial.available())
    {
        Serial.write('\"');
        Serial.write(Serial.read());
        Serial.write('\"');
    }
    Serial.println();
    delay(500);
    */
    /*
    static int i = 0;
    i=!i;
    digitalWrite(0,i);
    digitalWrite(2,!i);
    digitalWrite(4,HIGH);

    Serial.print("Iteracao: ");
    Serial.print(i);
    Serial.print("\t Tempo(us):");
    Serial.print(micros());
    Serial.print("\t Tempo(ms):");
    Serial.print(millis());
    Serial.print("\t pin 0:");
    Serial.print(digitalRead(0));
    Serial.print("\t pin 2:");
    Serial.print(digitalRead(2));
    Serial.print("\t pin 4:");
    Serial.println(digitalRead(4));

    while((micros()%500000) != 0);
    */
}