#include <math.h>
#include <UTFT.h>
#include <AccelStepper.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <avr/pgmspace.h>

const int red = 54;
const int black = 55;
const int green = 56;

const int lPwnUpper = 7;
const int rPwnUpper = 6;

void extend(const int RPWN, const int LPWN) {
  digitalWrite(RPWN, LOW);
  digitalWrite(LPWN, HIGH);
}

void retract(const int RPWN, const int LPWN) {
  digitalWrite(RPWN, HIGH);
  digitalWrite(LPWN, LOW);
}

void stopActuator(const int RPWN, const int LPWN) {
  digitalWrite(RPWN, LOW);
  digitalWrite(LPWN, LOW);
}

void setup() 
{
  pinMode(red, INPUT_PULLUP);
  pinMode(black, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);

  pinMode(lPwnUpper, OUTPUT);
  pinMode(rPwnUpper, OUTPUT);
  stopActuator(rPwnUpper, lPwnUpper);

}
void loop() 
{
  int redButton = digitalRead(red);
  int blackButton = digitalRead(black);
  int greenButton = digitalRead(green);

  if(redButton == LOW) {
    retract(rPwnUpper, lPwnUpper);
  }
  else if(blackButton == LOW) {
    stopActuator(rPwnUpper, lPwnUpper);
  }
  else if(greenButton == LOW) {
    extend(rPwnUpper, lPwnUpper);
  }
  else {
    stopActuator(rPwnUpper, lPwnUpper);
  }
}