#include <AccelStepper.h>

#define motorInterfaceType 1

const int red = 54;
const int black = 55;
const int green = 56;
const int stepPin = 62;
const int dirPin = 63;

int currPosition = 0;
int resetPosition = 0;

AccelStepper doubleArmMotor(motorInterfaceType, stepPin, dirPin);

void setup() {
  pinMode(red, INPUT_PULLUP);
  pinMode(black, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);

  doubleArmMotor.setMaxSpeed(100);
  doubleArmMotor.setAcceleration(50);
  doubleArmMotor.setSpeed(100);

  currPosition = doubleArmMotor.currentPosition();
  resetPosition = doubleArmMotor.currentPosition();
}

void loop() {
  int redButton = digitalRead(red);
  int blackButton = digitalRead(black);
  int greenButton = digitalRead(green);

  if(redButton == LOW) {
    currPosition -= 1;
    doubleArmMotor.moveTo(currPosition);
    doubleArmMotor.run();
  }

  if(blackButton == LOW) {
    doubleArmMotor.moveTo(resetPosition);
    doubleArmMotor.run();
  }

  if(greenButton == LOW) {
    currPosition += 1;
    doubleArmMotor.moveTo(currPosition);
    doubleArmMotor.run();
  }
}