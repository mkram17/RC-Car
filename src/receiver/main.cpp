#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>
#include <Servo.h>

const int DCMOTOR_ENA_PIN = 3;
const int DCMOTOR_IN1_PIN = 6;
const int DCMOTOR_IN2_PIN = 7;
const int CSN_PIN = 9;
const int CE_PIN = 10;
const int SERVO_SIGNAL_PIN = 5;

//MO D11, MI D12, SCK D13
RF24 radio(CE_PIN, CSN_PIN);
Servo servo;

const byte address[6] = "MaxKr";

unsigned long previousTime = 0;

struct JoystickState {
    int xPosition;
    int yPosition;
    int buttonState;
};

JoystickState joystickState = {0, 0, 0};

void moveServo(int velocity) {
  int current = servo.read();
  Serial.println("current servo angle: " + String(current) + ", angle velocity: " + String(velocity));
  servo.write(current + velocity);
}

void moveBackWheels(int velocity) {
  int speed = abs(velocity);
  // Serial.println("speed: " + String(speed));
  if(velocity > 0) {
    digitalWrite(DCMOTOR_IN1_PIN, HIGH);
    digitalWrite(DCMOTOR_IN2_PIN, LOW);
    analogWrite(DCMOTOR_ENA_PIN, speed);
    // Serial.println("moving motor forward by speed " + String(speed));
  } else if(velocity < 0) {
    digitalWrite(DCMOTOR_IN1_PIN, LOW);
    digitalWrite(DCMOTOR_IN2_PIN, HIGH);
    analogWrite(DCMOTOR_ENA_PIN, speed);
    // Serial.println("moving motor backward by speed " + String(speed));
  } else {
    digitalWrite(DCMOTOR_IN1_PIN, LOW);
    digitalWrite(DCMOTOR_IN2_PIN, LOW);
    analogWrite(DCMOTOR_ENA_PIN, 0);
    // Serial.println("stopping motor");
  }
}

int mapJoystickTo10bit(int joystickValue) {
  int normalizedVelocity = joystickValue - 355;
  int maxSpeed = 1023;
  int deadZone = 50;

  double velocityDouble = (double)normalizedVelocity * (double)maxSpeed / 355.0;
  int velocity = round(velocityDouble);

  if (abs(velocity) < deadZone) {
    velocity = 0;
  }
  return velocity;
}

void setup() {
    pinMode(DCMOTOR_ENA_PIN, OUTPUT);
    pinMode(DCMOTOR_IN1_PIN, OUTPUT);
    pinMode(DCMOTOR_IN2_PIN, OUTPUT);

    servo.attach(SERVO_SIGNAL_PIN);
      
    Serial.begin(9600);

    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
}

void loop() {
  unsigned long now = millis();

  if (radio.available()) {
    radio.read(&joystickState, sizeof(joystickState));
    Serial.println("Read joystick state: " + String(joystickState.xPosition) + ", " + String(joystickState.yPosition) + ", " + String(joystickState.buttonState));
  } 

  if((now - previousTime) >= 10) {
    previousTime = now;

    int maxForwardVelocity = 255;
    int forwardVelocity = mapJoystickTo10bit(joystickState.yPosition) * (maxForwardVelocity / 1023.0);
    moveBackWheels(forwardVelocity);

    int maxSteeringAngleVelocity = 10;
    int steeringAngleVelocity = mapJoystickTo10bit(joystickState.xPosition) * (maxSteeringAngleVelocity / 1023.0);
    moveServo(steeringAngleVelocity);
  }
}

