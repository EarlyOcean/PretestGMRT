#include <Servo.h>

int buttonPin = 2;

Servo servos[4];

volatile bool shouldSpin = true;

int initialAngle = 0;
int currentAngle[4] = {0, 0, 0, 0};

int timeDelay = 1000; // adjust time based on servo speed

void setup() {
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);

  servos[0].attach(9);
  servos[1].attach(10);
  servos[2].attach(11);
  servos[3].attach(12);

  servos[0].write(initialAngle);
  servos[1].write(initialAngle);
  servos[2].write(initialAngle);
  servos[3].write(initialAngle);

  delay(timeDelay);
}

void loop() {
  for(int i = 0; i < 4; i++){
    if(!shouldSpin) break;
    servo1.write(currentAngle[i] + 135);
    currentAngle[i] += 135;
    delay(timeDelay);
  }
}

void handleButtonPress() {
  shouldSpin = !shouldSpin;
}
