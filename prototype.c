#include <LiquidCrystal.h>
#include <Servo.h>
#include <Stepper.h>

Servo testServo;
int position = 0; // Initial position of Servo.

const int stepsPerRev = ;   // Steps per revolution of specific motor
Stepper testStepper(stepsPerRev, , , ,);    // 
int stepCount = 0;

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Fill this in with pins used
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Input pins here

int leftButton = 9; // Pin of button
int rightButton = 8; // Pin of button
int centerButton = ; // Pin of button

void setup() {
  testServo.attach(12); // Insert pin number connected to on board.
  testServo.write(position);
  lcd.begin(16, 2);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(centerButton, INPUT_PULLUP);
}

void loop() {
  lcd.print("HAFNA");
  lcd.print("Left button -> Stepper | Right button -> Servo");

  // Code to determine which motor to contorl

  if(digitalRead(leftButton) == LOW) {
    position--;
    delay(2);
    testServo.write(position);
    lcd.println(position);
  }

  if(digitalRead(rightButton) == LOW) {
    position++;
    delay(2);
    testServo.write(position);
    lcd.println(position);
  }

  if(digitalRead(centerButton) == LOW) {  // Kill switch
    position = 0;
    testServo.write(position);

  }


  if(digitalRead(rightButton) == LOW) {   // Steps the stepper motor a very small amount
    testStepper.step(1);
    lcd.println(stepCount);
    stepCount++;
    delay(500);
  }
}