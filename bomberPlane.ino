#include <Servo.h>

//SERVOS
Servo lAilServo;
Servo rAilServo;
Servo eleServo;
Servo rudServo;
Servo fGearServo;
Servo rGearServo;
Servo bayServo;
Servo bombServo;
Servo xCamServo;
Servo yCamServo;

//DURATIONS FOR WAVES
unsigned long lYDur; //THROTTLE
unsigned long lXDur; //YAW
unsigned long rYDur; //PITCH
unsigned long rXDur; //ROLL
unsigned long sfDur; //MODE LEVER
unsigned long shDur; //BOMB LEVER
unsigned long saDur; //LANDING GEAR/BOMB BAY
unsigned long sbDur; //BOMB NUM

//CONSTANTS
const bool flyOnly = true;
const int bombCap = 1;
const int deadzone = 50; //RANGE AWAY FROM RESTING NUM
const int minWidth = 950; //LOWEST PULSE WIDTH FROM RADIO TRANSMITTER
const int throtAllow = 50; //ALLOWANCE FOR THROTTLE MOVEMENT WHEN IN BOMBING STATE
const int gearAngle = 90;
const int bayAngle = 90;

//OUTPUT PINS
int rudPin = 2;
int elePin = 3;
int lAilPin = 4;
int rAilPin = 5;
int fGearPin = 6;
int rGearPin = 7;
int bayPin = 8;
int bombPin = 9;
int xCamPin = 10;
int yCamPin = 11;
int motorPin = 12;

//INPUT PINS
int lYPin = 22;
int rXPin = 23;
int rYPin = 24;
int lXPin = 25;
int sfPin = 26;
int shPin = 27;
int saPin = 28;
int sbPin = 29;

//PROGRAMMING VARIABLES
unsigned long throtDur;
int bombNum;

int bombs = bombCap;
bool bombingState = false;
bool bombPrimed = false;
bool gearDeployed = false;
bool bayOpen = false;

int interpretStick(unsigned long dur, int range, int start) {
  return (int) max(min(((double) (dur - minWidth) / 1000) * range, range), 0) + start;
}

void setup() {
  lAilServo.attach(lAilPin);
  rAilServo.attach(rAilPin);
  eleServo.attach(elePin);
  rudServo.attach(rudPin);
  fGearServo.attach(fGearPin);
  rGearServo.attach(rGearPin);
  bayServo.attach(bayPin);
  bombServo.attach(bombPin);
  xCamServo.attach(xCamPin);
  yCamServo.attach(yCamPin);

  pinMode(lYPin, INPUT);
  pinMode(lXPin, INPUT);
  pinMode(rYPin, INPUT);
  pinMode(rXPin, INPUT);
  pinMode(sfPin, INPUT);
  pinMode(shPin, INPUT);
  pinMode(saPin, INPUT);
  pinMode(sbPin, INPUT);
  
  pinMode(lAilPin, OUTPUT);
  pinMode(rAilPin, OUTPUT);
  pinMode(elePin, OUTPUT);
  pinMode(rudPin, OUTPUT);
  pinMode(fGearPin, OUTPUT);
  pinMode(rGearPin, OUTPUT);
  pinMode(bayPin, OUTPUT);
  pinMode(bombPin, OUTPUT);
  pinMode(xCamPin, OUTPUT);
  pinMode(yCamPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  lYDur = pulseIn(lYPin, HIGH, 30000);
  lXDur = pulseIn(lXPin, HIGH, 30000);
  rYDur = pulseIn(rYPin, HIGH, 30000);
  rXDur = pulseIn(rXPin, HIGH, 30000);
  sfDur = pulseIn(sfPin, HIGH, 30000);
  shDur = pulseIn(shPin, HIGH, 30000);
  saDur = pulseIn(saPin, HIGH, 30000);
  sbDur = pulseIn(sbPin, HIGH, 30000);

  //CHECKS FOR BOMBING STATE
  if (sfDur < 1500) {
    bombingState = false;
  } else {
    if (!bombingState) {
      throtDur = lYDur;
      bombingState = true;
    } else if (abs(lYDur - throtDur) > throtAllow) { //ADD NO INTERUPTION WHEN BOMBING
      bombingState = false;
    }
  }
  
  if (!bombingState || flyOnly) {
    //THROTTLE
    if (abs(lYDur - 1450) > deadzone) { //FINISH SHIT NOW
      int throttle = interpretStick(lYDur, 180, 0);

      //DO REST
    }

    //RUDDER
    if (abs(lXDur - 1450) > deadzone) {
      rudServo.write(180 - interpretStick(lXDur, 60, 60));
    } else {
      rudServo.write(90);
    }

    //ELEVATORS
    if (abs(rYDur - 1450) > deadzone) {
      eleServo.write(interpretStick(rYDur, 60, 60));
    } else {
      eleServo.write(90);
    }

    //AILERONS
    if (abs(rXDur - 1450) > deadzone) {
      int angle = interpretStick(rXDur, 60, 60);

      lAilServo.write(angle);
      rAilServo.write(angle);
    } else {
      lAilServo.write(90);
      rAilServo.write(90);
    }
    
    if (!flyOnly) {
      //LANDING GEAR
      if (saDur <= 1300) {
        fGearServo.write(gearAngle);
        rGearServo.write(gearAngle);

        gearDeployed = true;
      } else {
        fGearServo.write(0);
        rGearServo.write(0);
        
        gearDeployed = false;
      }
      
      //BOMB BAY
      if (saDur >= 1700) {
        bayServo.write(bayAngle);

        bayOpen = true;
      } else {
        bayServo.write(0);
        
        bayOpen = false;
      }

      //BOMB NUM
      if (sbDur <= 1300 || bombs == 1) {
        bombNum = 1;
      } else if (sbDur <= 1700) {
        bombNum = 2;
      } else {
        bombNum = bombs;
      }

      //BOMBS
      if (shDur < 1500) {
        bombPrimed = true;
      } else if (bombPrimed) {
        bombPrimed = false;

        //BOMB DROP CODE
        if (bayOpen && bombs > 0) {
          bombs--;

          Serial.print(missileNum);
          Serial.println(" bomb(s) dropped");

          Serial.print(bombs);
          Serial.println(" bomb(s) left");
        }
      }
    }
  } else {
    bayServo.write(bayAngle);
    bayOpen = true;

    //AUTO STEADY

    //CAMERA Y
    if (abs(rYDur - 1450) > deadzone) {
    } else {
    }

    //CAMERA X
    if (abs(rXDur - 1450) > deadzone) {
    } else {
    }

    //BOMB NUM
    if (sbDur <= 1300 || bombs == 1) {
      bombNum = 1;
    } else if (sbDur <= 1700) {
      bombNum = 2;
    } else {
      bombNum = bombs;
    }

    if (shDur < 1500) {
      //WRITE BOMB CODE
    }
  }
}