#include <Servo.h>

Servo leftAileronServo;
Servo rightAileronServo;
Servo elevatorServo;
Servo rudderServo;
Servo frontLandingGearServo;
Servo rearLandingGearServo;
Servo bombBayServo;
Servo missileServo;
Servo xCameraServo;
Servo yCameraServo;

unsigned long throttleInDur;
unsigned long rudderInDur;
unsigned long elevatorInDur;
unsigned long aileronInDur;
unsigned long modeSwitchInDur;
unsigned long missileInDur;
unsigned long landingInDur;
unsigned long missileNumInDur;

int rudderPin = 2;
int elevatorPin = 3;
int leftAileronPin = 4;
int rightAileronPin = 5;
int frontLandingGearPin = 6;
int rearLandingGearPin = 7;
int bombBayPin = 8;
int missilePin = 9;
int xCameraPin = 10;
int yCameraPin = 11;
int motorPin = 12;

int throttleInPin = 22;
int aileronInPin = 23;
int elevatorInPin = 24;
int rudderInPin = 25;
int modeSwitchInPin = 26;
int missileInPin = 27;
int landingInPin = 28;
int missileNumInPin = 29;

//BOMBING STATE
bool bombingState = false;
double speed;

//BOMBING
bool bombPrimed = false;
int missileNum;

//LANDING GEAR
bool landingGearDeployed = false;
int landingGearAngle = 90;

//BOMB BAY
bool bombBayOpen = false;
int bombBayAngle = 90;

void setup() {
  leftAileronServo.attach(leftAileronPin);
  rightAileronServo.attach(rightAileronPin);
  elevatorServo.attach(elevatorPin);
  rudderServo.attach(rudderPin);
  frontLandingGearServo.attach(frontLandingGearPin);
  rearLandingGearServo.attach(rearLandingGearPin);
  bombBayServo.attach(bombBayPin);
  missileServo.attach(missilePin);
  xCameraServo.attach(xCameraPin);
  yCameraServo.attach(yCameraPin);

  pinMode(throttleInPin, INPUT);
  pinMode(rudderInPin, INPUT);
  pinMode(elevatorInPin, INPUT);
  pinMode(aileronInPin, INPUT);
  pinMode(modeSwitchInPin, INPUT);
  pinMode(missileInPin, INPUT);
  pinMode(landingInPin, INPUT);
  pinMode(missileNumInPin, INPUT);
  
  pinMode(leftAileronPin, OUTPUT);
  pinMode(rightAileronPin, OUTPUT);
  pinMode(elevatorPin, OUTPUT);
  pinMode(rudderPin, OUTPUT);
  pinMode(frontLandingGearPin, OUTPUT);
  pinMode(rearLandingGearPin, OUTPUT);
  pinMode(bombBayPin, OUTPUT);
  pinMode(missilePin, OUTPUT);
  pinMode(xCameraPin, OUTPUT);
  pinMode(yCameraPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  throttleInDur = pulseIn(throttleInPin, HIGH, 30000);
  rudderInDur = pulseIn(rudderInPin, HIGH, 30000);
  elevatorInDur = pulseIn(elevatorInPin, HIGH, 30000);
  aileronInDur = pulseIn(aileronInPin, HIGH, 30000);
  modeSwitchInDur = pulseIn(modeSwitchInPin, HIGH, 30000);
  missileInDur = pulseIn(missileInPin, HIGH, 30000);
  landingInDur = pulseIn(landingInPin, HIGH, 30000);
  missileNumInDur = pulseIn(missileNumInPin, HIGH, 30000);

  if (modeSwitchInDur < 1500) {
    bombingState = false;
  } else {
    bombingState = true;
  }
  
  if (!bombingState) {
    //THROTTLE
    if (abs(throttleInDur - 1450) > 50) { //FINISH SHIT NOW
      int throttle = max(min(((double) (throttleInDur - 950) / 1000) * 180, 180), 0);

      //DO REST
    }

    //RUDDER
    if (abs(rudderInDur - 1450) > 50) {
      int angle = max(min(((double) (rudderInDur - 950) / 1000) * 60, 60), 0) + 60;

      rudderServo.write(180 - angle);
    } else {
      rudderServo.write(90);
    }

    //ELEVATORS
    if (abs(elevatorInDur - 1450) > 50) {
      int angle = max(min(((double) (elevatorInDur - 950) / 1000) * 60, 60), 0) + 60;

      elevatorServo.write(angle);
    } else {
      elevatorServo.write(90);
    }

    //AILERONS
    if (abs(aileronInDur - 1450) > 50) {
      int angle = max(min(((double) (aileronInDur - 950) / 1000) * 60, 60), 0) + 60;

      leftAileronServo.write(angle);
      rightAileronServo.write(angle);
    } else {
      leftAileronServo.write(90);
      rightAileronServo.write(90);
    }
    
    //LANDING GEAR
    if (landingInDur <= 1300) {
      frontLandingGearServo.write(landingGearAngle);
      rearLandingGearServo.write(landingGearAngle);

      landingGearDeployed = true;
    } else {
      frontLandingGearServo.write(0);
      rearLandingGearServo.write(0);
      
      landingGearDeployed = false;
    }
    
    //BOMB BAY
    if (landingInDur >= 1700) {
      bombBayServo.write(bombBayAngle);

      bombBayOpen = true;
    } else {
      bombBayServo.write(0);
      
      bombBayOpen = false;
    }

    //MISSILE NUM
    if (missileNumInDur <= 1300) {
      missileNum = 1;
    } else if (missileNumInDur <= 1700) {
      missileNum = 2;
    } else {
      missileNum = 20;
    }

    //MISSILES
    if (missileInDur < 1500) {
      bombPrimed = true;
    } else if (bombPrimed) {
      bombPrimed = false;

      //BOMB DROP CODE
      if (bombBayOpen) {
        Serial.print(missileNum);
        Serial.println(" bomb(s) dropped");
      }
    }

    //SWITCH TO BOMBING STATE
    if (false) {
      bombingState = true;
      speed = 0; //FILL IN INPUT
    }
  } else {
    //SET CONSTANT SPEED
    //AUTO STEADY

    //CAMERA CONTROLS

    //SWITCH TO FLYING STATE
    if (false) {
      bombingState = false;
    }
  }

//  delay(100);
}
