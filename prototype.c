#include <LiquidCrystal.h>
#include <Servo.h>

Servo testServo;
int position = 90; // Initial position of Servo.

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Pins used for LCD1602 screen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the LCD

int leftButton = 10;  // Left button in pin 10
int centerButton = 9; // Center button in pin 9
int rightButton = 8;  // Right button in pin 8

int displaySelect = 0;  // Variable to move between display menus
int ledSelect = 0;  // Variable to control LEDs

void setup() {
  testServo.attach(13); // Servo attached to pin 13
  testServo.write(position);  // Set inital position of servo 
  lcd.begin(16, 2); // Define LCD screen
  pinMode(leftButton, INPUT_PULLUP);  // Set pullup resistors for left button
  pinMode(rightButton, INPUT_PULLUP); // Set pullup resistors for right button
  pinMode(centerButton, INPUT_PULLUP);  // Set pulluo resistors for center button
  pinMode(44, OUTPUT);  // Output pins for blue LED
  pinMode(46, OUTPUT);  // Output pins for red LED
  pinMode(48, OUTPUT);  // Output pins for green LED
}

void loop() {

  if(displaySelect == 0) {    // Main Menu
    lcd.print("Left: Servo");
    lcd.setCursor(0, 1);
    lcd.print("Right: Stepper  ");
    if(digitalRead(leftButton) == LOW) {
      lcd.clear();
      displaySelect = 1;
      delay(200); // Debounce button
    }
    if(digitalRead(rightButton) == LOW) {
      lcd.clear();
      displaySelect = 2;
      delay(200); // Debounce button
    }
  }

  if(displaySelect == 1) {  // Servo Control "Reflection Loss"
    lcd.setCursor(1, 0);
    lcd.print("Reflection Loss");
    if(digitalRead(leftButton) == LOW) {
      if(position >= 0) {
        position--;
        delay(5);
        testServo.write(position);
        if(position >= 0) {
          lcd.setCursor(1, 0);
          lcd.print("Reflection Loss");
          lcd.setCursor(0, 1);
          lcd.print("Servo Angle:");
          lcd.println(position);
        }
      }
    }

    if(digitalRead(rightButton) == LOW) {
      if(position <= 180) {
        position++;
        delay(5);
        testServo.write(position);
        if(position <= 180) {
          lcd.setCursor(1, 0);
          lcd.print("Reflection Loss");
          lcd.setCursor(0, 1);
          lcd.print("Servo Angle:");
          lcd.println(position);
        }
      }
    }

    if(digitalRead(centerButton) == LOW) {  // REturn to Main Menu
      lcd.clear();
      displaySelect = 0;
    }
  }

  if(displaySelect == 2) {  // Stepper Control "Insertion Loss"
    lcd.setCursor(1, 0);
    lcd.print("Insertion Loss");
    if(digitalRead(leftButton) == LOW) {
      if(ledSelect == 0) {
        digitalWrite(44, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Insertion Loss");
        lcd.setCursor(0, 1);
        lcd.print("Stepper: Blue");
        delay(250);
        digitalWrite(44, LOW);
        lcd.clear();
        ledSelect = 1;
      }
      if(ledSelect == 1){
        digitalWrite(46, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Insertion Loss");
        lcd.setCursor(0, 1);
        lcd.print("Stepper: Red");
        delay(250);
        digitalWrite(46, LOW);
        lcd.clear();
        ledSelect = 2;
      }
      if(ledSelect == 2){
        digitalWrite(48, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Insertion Loss");
        lcd.setCursor(0, 1);
        lcd.print("Stepper: Green");
        delay(250);
        digitalWrite(48, LOW);
        lcd.clear();
        ledSelect = 0;
      }
    }

    if(digitalRead(rightButton) == LOW) {
      if(ledSelect == 0) {
        digitalWrite(48, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Insertion Loss");
        lcd.setCursor(0, 1);
        lcd.print("Stepper: Green");
        delay(250);
        digitalWrite(48, LOW);
        lcd.clear();
        ledSelect = 1;
      }
      if(ledSelect == 1){
        digitalWrite(46, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Insertion Loss");
        lcd.setCursor(0, 1);
        lcd.print("Stepper: Red");
        delay(250);
        digitalWrite(46, LOW);
        lcd.clear();
        ledSelect = 2;
      }
      if(ledSelect == 2){
        digitalWrite(44, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Insertion Loss");
        lcd.setCursor(0, 1);
        lcd.print("Stepper: Blue");
        delay(250);
        digitalWrite(44, LOW);
        lcd.clear();
        ledSelect = 0;
      }
    }

    if(digitalRead(centerButton) == LOW) {  // Return to Main Menu
      lcd.clear();
      displaySelect = 0;
    }
  }
}