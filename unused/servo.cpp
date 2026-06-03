#include <Arduino.h>
#include <Servo.h>

const int signalPin = 5;
Servo servo;

void setup() {
  servo.attach(signalPin);
  for (int i = 0; i <= 180; i++) {
    servo.write(i);
    delay(150);
  }
}

void loop() {

}

void moveServo(int angle) {
  int current = servo.read();
  servo.write(angle);
}