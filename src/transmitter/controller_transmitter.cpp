#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


const int CE_PIN = 5;
const int CSN_PIN = 7;

const int VCC_PIN = 2;

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

void setup(){
    pinMode(VCC_PIN, OUTPUT);
    digitalWrite(VCC_PIN, HIGH);

    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}

void loop() {
    const char text[] = "Testing MK";
    radio.write(&text, sizeof(text));
    Serial.println(text);
    delay(1000);
}