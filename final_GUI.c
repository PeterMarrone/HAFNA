#include <UTFT.h>
#include <AccelStepper.h>
#include <NewPing.h>

#define motorInterfaceType 1
#define MAX_DISTANCE 200
#define L_PRESS 1000 //1 seconds
#define H_PRESS 3000 //3 seconds

/* Arduino pin declarations */
const int backLight = 8;

const int lPwnUpper = 7;
const int rPwnUpper = 6;
const int lPwnLower = 5;
const int rPwnLower = 4;
const int lPwnSingle = 3;
const int rPwnSingle = 2;

const int red = 54;
const int black = 55;
const int green = 56;

const int trigPinDoubleArm = 57;
const int echoPinDoubleArm = 58;
const int trigPinSingleArm = 59;
const int echoPinSingleArm = 60;

const int dirPinDoubleArm = 62;
const int stepPinDoubleArm = 63;
const int dirPinSingleArm = 64;
const int stepPinSingleArm = 65;

unsigned long previousMillis = 0UL;
unsigned long interval = 10000UL;

int displayCount = 0;
int screenShown = 0;

int antennaSelection = 0;
int testSelection = 0;

int resetPositionDoubleArm = 0;
int resetPositionSingleArm = 0;

unsigned int pingSpeed = 50;
unsigned long pingTimer;

unsigned long pressedTime = 0;
unsigned long releasedTime = 0;
long pressDuration = 0;

/* Declare which fonts we will be using */
extern uint8_t BigFont[];

/* Remember to change the model parameter to suit your display module! */
UTFT myGLCD(SSD1963_800480, 38, 39, 40, 41);  
/* (byte model, int RS, int WR, int CS, int RST, int SER) */

AccelStepper doubleArmMotor(motorInterfaceType, stepPinDoubleArm, dirPinDoubleArm);
AccelStepper singleArmMotor(motorInterfaceType, stepPinSingleArm, dirPinSingleArm);

NewPing doubleArmDistance(trigPinDoubleArm, echoPinDoubleArm, MAX_DISTANCE);
NewPing singleArmDistance(trigPinSingleArm, echoPinSingleArm, MAX_DISTANCE);

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

void posDirStepperDouble(AccelStepper motor) {
  motor.setSpeed(150);
  motor.runSpeed();
}

void negDirStepperDouble(AccelStepper motor) {
  motor.setSpeed(-150);
  motor.runSpeed();
}

double getAntennaDistance(NewPing sensor) {
  if(sensor.check_timer()) {
    return(sensor.ping_result / US_ROUNDTRIP_CM);
  }
}

void extend(const int RPWN, const int LPWN) {
  digitalWrite(RPWN, HIGH);
  digitalWrite(LPWN, LOW);
}

void retract(const int RPWN, const int LPWN) {
  digitalWrite(RPWN, LOW);
  digitalWrite(LPWN, HIGH);
}

void stopActuator(const int RPWN, const int LPWN) {
  digitalWrite(RPWN, LOW);
  digitalWrite(LPWN, LOW);
}

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  myGLCD.InitLCD();
  myGLCD.setFont(BigFont);
  pinMode(backLight, OUTPUT); 
  digitalWrite(backLight, HIGH);

  pinMode(red, INPUT_PULLUP);
  pinMode(black, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);

  pinMode(trigPinDoubleArm, OUTPUT);
  pinMode(echoPinDoubleArm, INPUT);
  pinMode(trigPinSingleArm, OUTPUT);
  pinMode(echoPinSingleArm, INPUT);

  resetPositionDoubleArm = doubleArmMotor.currentPosition();
  resetPositionSingleArm = singleArmMotor.currentPosition();
  
  pingTimer = millis(); //start pings

  stopActuator(rPwnUpper, lPwnUpper);
  stopActuator(rPwnLower, lPwnLower);
  stopActuator(rPwnSingle, lPwnSingle);
}

void loop()
{
  int redButton = digitalRead(red);
  int blackButton = digitalRead(black);
  int greenButton = digitalRead(green);

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
        if(blackButton == LOW) {
          pressedTime = millis();
        }
        else {
          releasedTime = millis();
        }

        pressDuration = releasedTime - pressedTime;

        if(pressDuration > L_PRESS && pressDuration < H_PRESS) {
          screenShown = 0;
          displayCount = 0;
        }

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
        if(blackButton == LOW) {
          pressedTime = millis();
        }
        else {
          releasedTime = millis();
        }

        pressDuration = releasedTime - pressedTime;

        if(pressDuration > L_PRESS && pressDuration < H_PRESS) {
          screenShown = 0;
          displayCount = 0;
        }

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
        if(blackButton == LOW) {
          pressedTime = millis();
        }
        else {
          releasedTime = millis();
        }

        pressDuration = releasedTime - pressedTime;

        if(pressDuration > L_PRESS && pressDuration < H_PRESS) {
          screenShown = 0;
          displayCount = 0;
        }
        
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
        if(blackButton == LOW) {
          pressedTime = millis();
        }
        else {
          releasedTime = millis();
        }

        pressDuration = releasedTime - pressedTime;

        if(pressDuration > L_PRESS && pressDuration < H_PRESS) {
          screenShown = 0;
          displayCount = 0;
        }

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