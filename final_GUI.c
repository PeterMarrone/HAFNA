#include <UTFT.h>

/* Declare which fonts we will be using */
extern uint8_t BigFont[];

/* Remember to change the model parameter to suit your display module! */
UTFT myGLCD(SSD1963_800480,38,39,40,41);  
/* (byte model, int RS, int WR, int CS, int RST, int SER) */

unsigned long previousMillis = 0UL;
unsigned long interval = 10000UL;

int displayCount = 0;
int screenShown = 0;

int antennaSelection = 0;
int testSelection = 0;

void displayAntenna(int );
void displayTest(int );

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  myGLCD.InitLCD();

  pinMode(8, OUTPUT);       //backlight 
  digitalWrite(8, HIGH);    //on

  pinMode(54, INPUT_PULLUP);
  pinMode(55, INPUT_PULLUP);
  pinMode(56, INPUT_PULLUP);

  myGLCD.setFont(BigFont);
}

void loop()
{

  int redButton = digitalRead(54);
  int blackButton = digitalRead(55);
  int greenButton = digitalRead(56);

  if(displayCount == 0) {
    if(screenShown == 1) {
        if(greenButton == LOW) {
          screenShown = 0;
          displayCount = 1;
          antennaSelection = 2;
        }

        if(blackButton == LOW) {
          screenShown = 0;
          displayCount = 1;
          antennaSelection = 1;
        }
        
        if(redButton == LOW) {
          screenShown = 0;
          displayCount = 1;
          antennaSelection = 0;
        }
    }
    else {
      /* Set screen background to white */
      myGLCD.fillScr(255, 255, 255);
  
      /* Draws three buttons on screen (Red, Black, Green) */
      myGLCD.setColor(255, 0, 0);
      myGLCD.fillCircle(250, 400, 50);
      myGLCD.print("Alpha", 210, 325);
      myGLCD.setColor(0, 0, 0);
      myGLCD.fillCircle(400, 400, 50);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("Maverick", 335, 325);      
      myGLCD.setColor(0, 255, 0);
      myGLCD.fillCircle(550, 400, 50);
      myGLCD.print("Bravo", 510, 325);
      screenShown = 1;
    }
  }

  if(displayCount == 1) {
    if(screenShown == 1) {
        if(greenButton == LOW) {
          screenShown = 0;
          displayCount = 2;
          testSelection = 1;
        }

        if(blackButton == LOW) {
          screenShown = 0;
          displayCount = 0;
        }
        
        if(redButton == LOW) {
          screenShown = 0;
          displayCount = 2;
          testSelection = 2;
        }
    }
    else {
      /* Set screen background to white */
      myGLCD.fillScr(255, 255, 255);

      displayAntenna(antennaSelection);

      /* Draws three buttons on screen (Red, Black, Green) */
      myGLCD.setColor(255, 0, 0);
      myGLCD.fillCircle(250, 400, 50);
      myGLCD.print("Insetion Loss", 150, 325);
      myGLCD.setColor(0, 0, 0);
      myGLCD.fillCircle(400, 400, 50);     
       myGLCD.setColor(0, 255, 0);
      myGLCD.fillCircle(550, 400, 50);
      myGLCD.print("Reflection Loss", 440, 325);
      screenShown = 1;
    }
  }

  if(testSelection == 1) {
    if(displayCount == 2) {
      if(screenShown == 1) {    
        if(blackButton == LOW) {
          screenShown = 0;
          displayCount = 1; 
        }
      }
      else {
        myGLCD.fillScr(255, 255, 255);
        
        displayAntenna(antennaSelection);
        displayTest(testSelection);

        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRoundRect(250, 200, 550, 300);
        myGLCD.setColor(255, 255, 255);
        myGLCD.setBackColor(0, 0, 0);
        myGLCD.print("Antenna", 260, 225);
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
        screenShown = 1;
      }
    } 

    if(displayCount == 3) {
      if(screenShown == 1) {
        if(blackButton == LOW) {
          screenShown = 0;
          displayCount = 1;
        }
      }
      else {
        myGLCD.fillScr(255, 255, 255);

        displayAntenna(antennaSelection);
        displayTest(testSelection);

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
        screenShown = 1;
      }
    }
  }

  if(testSelection == 2) {
    if(displayCount == 2) {
      if(screenShown == 1) {
        if(blackButton == LOW) {
          screenShown = 0;
          displayCount = 1;
        } 
      }
      else {
        myGLCD.fillScr(255, 255, 255);

        displayAntenna(antennaSelection);
        displayTest(testSelection);
        
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRoundRect(250, 200, 550, 300);
        myGLCD.setColor(255, 255, 255);
        myGLCD.setBackColor(0, 0, 0);
        myGLCD.print("Antenna", 260, 225);
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
        screenShown = 1;
      }
    } 

    if(displayCount == 3) {
      if(screenShown == 1) {
        if(blackButton == LOW) {
          screenShown = 0;
          displayCount = 1;
        }
      }
      else {
        myGLCD.fillScr(255, 255, 255);

        displayAntenna(antennaSelection);
        displayTest(testSelection);

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
        screenShown = 1;
      }
    }
  }
} 

void displayAntenna(int select) {
  int antenna = select;

  if(antenna == 0) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("Antenna Selected: Alpha", 0, 0);
  } 
      
  if(antenna == 1) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("Antenna Selected: Maverick", 0, 0);
  }

  if(antenna == 2) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("Antenna Selected: Bravo", 0, 0);
  }
}

void displayTest(int select) {
  int test = select;

  if(test == 1){
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("Test Selected: Reflection Loss", 0, 15);
  }

  if(test == 2) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("Test Selected: Insertion Loss", 0, 15);
  }
}