#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


const int CE_PIN = 5;
const int CSN_PIN = 7;

const int JOYSTICK_X_PIN = A1;
const int JOYSTICK_Y_PIN = A2;
const int JOYSTICK_CLICK = 2;

int velocity = 100;

int xPosition = analogRead(JOYSTICK_X_PIN);
int yPosition = analogRead(JOYSTICK_Y_PIN);
int buttonState = digitalRead(JOYSTICK_CLICK);

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "MaxKr";

struct JoystickState {
    int xPosition;
    int yPosition;
    int buttonState;
};

void setup(){
    
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}

void loop() {
    
    xPosition = analogRead(JOYSTICK_X_PIN);
    yPosition = analogRead(JOYSTICK_Y_PIN);
    buttonState = digitalRead(JOYSTICK_CLICK); //doesnt work

    JoystickState joystickState = {xPosition, yPosition, buttonState};
    radio.write(&joystickState, sizeof(joystickState));
    Serial.println("Sent joystick state: " + String(joystickState.xPosition) + ", " + String(joystickState.yPosition) + ", " + String(joystickState.buttonState));
    delay(100);
}