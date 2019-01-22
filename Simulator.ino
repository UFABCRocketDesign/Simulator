void setup() // Eh executada somente uma vez
{
    Serial.begin(9600);
    Serial.println("Hello World!");
    pinMode(0,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);

    int val = 127;
    val = map(val, 0, 1023, 0, 255);
    analogWrite(9, val);

}

void loop() // Fica em loop indefinidamente
{
    static int i = 0;
    digitalWrite(0,i);
    digitalWrite(2,!i);
    digitalWrite(4,HIGH);
    i=!i;
}