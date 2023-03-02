#include <AccelStepper.h>

#define motorInterfaceType 1

const int red = 54;
const int black = 55;
const int green = 56;
const int stepPin = 1;
const int dirPin = 2;

AccelStepper doubleArmMotor(motorInterfaceType, stepPin, dirPin);

void setup() {
  // put your setup code here, to run once:
  pinMode(red, INPUT_PULLUP);
  pinMode(black, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);

  doubleArmMotor.setMaxSpeed(1000);
  doubleArmMotor.setAcceleration(50);
  doubleArmMotor.setSpeed(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int redButton = digitalRead(red);
  int blackButton = digitalRead(black);
  int greenButton = digitalRead(green);

  if(redButton == LOW) {
    // Move motor backwards
  }

  if(greenButton == LOW) {
    // Move motor forward
  }
}