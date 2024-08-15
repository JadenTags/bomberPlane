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
int rudderInPin = 23;
int elevatorInPin = 24;
int aileronInPin = 25;

//BOMBING STATE
bool bombingState = false;
double speed;

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
  throttleInDur = pulseIn(throttleInPin, HIGH, 50000);
  rudderInDur = pulseIn(rudderInPin, HIGH, 50000);
  elevatorInDur = pulseIn(elevatorInPin, HIGH, 50000);
  aileronInDur = pulseIn(aileronInPin, HIGH, 50000);

  Serial.println(aileronInDur);
  
  if (!bombingState) {
    //THROTTLE
    if (abs(throttleInDur - 1450) > 50) { //FINISH SHIT NOW
      int angle = max(min(((double) (throttleInDur - 960) / 1000) * 180, 180), 0);
    } else {
    }

    //RUDDER
    if (abs(rudderInDur - 1450) > 50) {
      int angle = max(min(((double) (rudderInDur - 960) / 1000) * 60, 60), 0) + 15;

      rudderServo.write(180 - angle);
    } else {
      rudderServo.write(90);
    }

    //ELEVATORS
    if (abs(elevatorInDur - 1450) > 50) {
      int angle = max(min(((double) (elevatorInDur - 960) / 1000) * 60, 60), 0) + 15;

      elevatorServo.write(angle);
    } else {
      elevatorServo.write(90);
    }

    //AILERONS
    if (abs(aileronInDur - 1450) > 50) {
      int angle = max(min(((double) (aileronInDur - 960) / 1000) * 60, 60), 0) + 15;

      leftAileronServo.write(angle);
      rightAileronServo.write(angle);
    } else {
      leftAileronServo.write(90);
      rightAileronServo.write(90);
    }
    
    //LANDING GEAR
    if (false) {
      if (landingGearDeployed) {
        frontLandingGearServo.write(0);
        rearLandingGearServo.write(0);
      } else {
        frontLandingGearServo.write(landingGearAngle);
        rearLandingGearServo.write(landingGearAngle);
      }

      landingGearDeployed = !landingGearDeployed;
    } 
    
    //BOMB BAY
    if (false) {
      if (bombBayOpen) {
        bombBayServo.write(0);
      } else {
        bombBayServo.write(bombBayAngle);
      }

      bombBayOpen = !bombBayOpen;
    }

    //MISSILES
    if (false) {
      //DEPLOY MISSILES
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
