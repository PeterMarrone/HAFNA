#include <AccelStepper.h>

#define motorInterfaceType 1

const int red = 54;
const int black = 55;
const int green = 56;

const int stepsingle = 63;
const int dirSingle = 62;
const int stepPin = 65;
const int dirPin = 64;

int currPosition = 0;
int resetPosition = 0;

AccelStepper doubleArmMotor(motorInterfaceType, stepPin, dirPin);
AccelStepper Single(motorInterfaceType, stepsingle, dirSingle);

void setup() {
  pinMode(red, INPUT_PULLUP);
  pinMode(black, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(stepsingle, OUTPUT);
  pinMode(dirSingle, OUTPUT);

  doubleArmMotor.setMaxSpeed(150);
  doubleArmMotor.setAcceleration(50);

  Single.setMaxSpeed(150);
  Single.setAcceleration(50);

  currPosition = doubleArmMotor.currentPosition();
  resetPosition = doubleArmMotor.currentPosition();
}

void loop() {
  int redButton = digitalRead(red);
  int blackButton = digitalRead(black);
  int greenButton = digitalRead(green);

  if(redButton == LOW) {
    doubleArmMotor.setSpeed(-150);
    Single.setSpeed(-150);
    Single.runSpeed();
    doubleArmMotor.runSpeed();
  }

  if(blackButton == LOW) {
    doubleArmMotor.moveTo(resetPosition);
    doubleArmMotor.run();
  }

  if(greenButton == LOW) {
    doubleArmMotor.setSpeed(150);
    Single.setSpeed(150);
    Single.runSpeed();
    doubleArmMotor.runSpeed();
  }
}