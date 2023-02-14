#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t BigFont[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41

// Remember to change the model parameter to suit your display module!
UTFT myGLCD(SSD1963_800480,38,39,40,41);  //(byte model, int RS, int WR, int CS, int RST, int SER)

void setup()
{
  randomSeed(analogRead(0));
  
// Setup the LCD
  myGLCD.InitLCD();
 // -------------------------------------------------------------
  pinMode(8, OUTPUT);  //backlight 
  digitalWrite(8, HIGH);//on
// -------------------------------------------------------------
 
  myGLCD.setFont(BigFont);
  // Clear the screen and draw the frame
  myGLCD.clrScr();

  /* Set screen background to white */
  myGLCD.fillScr(255, 255, 255);
  
  /* Draws three buttons on screen (Red, Black, Green) */
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillCircle(250, 400, 50);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillCircle(400, 400, 50);
  myGLCD.setColor(0, 255, 0);
  myGLCD.fillCircle(550, 400, 50);
}

void loop()
{
  delay(5000);

  /* Draws box and prints text for insetion angle box */
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect(250, 200, 550, 300);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("Insertion", 260, 225);
  myGLCD.print("Angle", 260, 255);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(450, 210, 540, 290);

  /* Draws three buttons on screen (Red, Black, Green) */
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillCircle(250, 400, 50);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillCircle(400, 400, 50);
  myGLCD.setColor(0, 255, 0);
  myGLCD.fillCircle(550, 400, 50);

  delay(5000);

  /* Draws box and prints text for insetion angle box */
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect(250, 200, 550, 300);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("Antenna", 260, 225);
  myGLCD.print("Distance", 260, 255);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(450, 210, 540, 290);

  /* Draws three buttons on screen (Red, Black, Green) */
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillCircle(250, 400, 50);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillCircle(400, 400, 50);
  myGLCD.setColor(0, 255, 0);
  myGLCD.fillCircle(550, 400, 50);


}