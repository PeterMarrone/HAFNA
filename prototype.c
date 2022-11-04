#include <LiquidCrystal.h>
#include <Servo.h>
//#include <Stepper.h>

Servo testServo;
int position = 90; // Initial position of Servo.

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Fill this in with pins used
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Input pins here

int leftButton = 10;  // Pin of button
int centerButton = 9; // Pin of button
int rightButton = 8;  // Pin of button

int displayCount = 0;

void setup() {
  testServo.attach(11); // Insert pin number connected to on board.
  testServo.write(position);
  lcd.begin(16, 2);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(centerButton, INPUT_PULLUP);
  pinMode(44, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
}

void loop() {
  if(displayCount == 0) {
    lcd.print("Left: Servo");
    lcd.setCursor(0, 1);
    lcd.print("Right: Stepper  ");
    if(digitalRead(leftButton) == LOW) {
      displayCount = 1;
    }
    if(digitalRead(rightButton) == LOW) {
      displayCount = 2;
    }
  }

  if(displayCount == 1) {
    if(digitalRead(leftButton) == LOW) {
      position--;
      delay(2);
      testServo.write(position);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.println(position);
      lcd.print("               ");
    }

    if(digitalRead(rightButton) == LOW) {
      position++;
      delay(2);
      testServo.write(position);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.println(position);
      lcd.print("               ");
    }

    if(digitalRead(centerButton) == LOW) {
      displayCount = 0;
    }
  }

  if(displayCount == 2) {
    if(digitalRead(centerButton) == HIGH) {
      digitalWrite(44, HIGH);
      delay(100);
      digitalWrite(44, LOW);
      digitalWrite(46, HIGH);
      delay(100);
      digitalWrite(46, LOW);
      digitalWrite(48, HIGH);
      delay(100);
      digitalWrite(48, LOW);
    } 
    if(digitalRead(centerButton) == LOW) {
      displayCount = 0;
    } 
  }
}