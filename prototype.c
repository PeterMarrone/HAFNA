#include <LiquidCrystal.h>
#include <Servo.h>

Servo testServo;
int position = 0; // Initial position of Servo.

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Fill this in with pins used
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Input pins here

int leftButton = 9; // Pin of button
int rightButton = 8; // Pin of button

void setup() {
  testServo.attach(12); // Insert pin number connected to on board.
  lcd.begin(16, 2);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(leftButton) == LOW) {
    position--;
    delay(2);
    testServo.write(position);
    lcd.print("This works lol");
    //lcd.print("Maybe %d", position);
  }

    if(digitalRead(rightButton) == LOW) {
    position++;
    delay(2);
    testServo.write(position);
    lcd.print("This also works");
    //lcd.print("Ayo %d", position);
  }
}