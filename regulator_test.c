#include <UTFT.h>

/* Declare which fonts we will be using */
extern uint8_t BigFont[];

/* Remember to change the model parameter to suit your display module! */
UTFT myGLCD(SSD1963_800480,38,39,40,41);  
/* (byte model, int RS, int WR, int CS, int RST, int SER) */

void setup() {
  // put your setup code here, to run once:
  myGLCD.InitLCD();

  pinMode(8, OUTPUT);       //backlight 
  digitalWrite(8, HIGH);    //on

  pinMode(54, INPUT_PULLUP);
  pinMode(55, INPUT_PULLUP);
  pinMode(56, INPUT_PULLUP);

  pinMode(57, OUTPUT);
  pinMode(58, OUTPUT);
  pinMode(59, OUTPUT);

  myGLCD.setFont(BigFont);

  myGLCD.fillScr(255, 255, 255);
  
  /* Draws three buttons on screen (Red, Black, Green) */
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillCircle(250, 400, 50);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillCircle(400, 400, 50);
  myGLCD.setColor(255, 255, 255);     
  myGLCD.setColor(0, 255, 0);
  myGLCD.fillCircle(550, 400, 50);
}

void loop() {
  // put your main code here, to run repeatedly:
  int redButton = digitalRead(54);
  int blackButton = digitalRead(55);
  int greenButton = digitalRead(56);

  if(redButton == LOW) {
    digitalWrite(57, HIGH);
  }
  else {
    digitalWrite(57, LOW);
  }

  if(blackButton == LOW) {
    digitalWrite(58, HIGH);
  }
  else {
    digitalWrite(58, LOW);
  }

  if(greenButton == LOW) {
    digitalWrite(59, HIGH);
  }
  else {
    digitalWrite(59, LOW);
  }

}