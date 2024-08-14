#include <Servo.h>

Servo leftWingServo;
Servo rightWingServo;
Servo frontLandingGearServo;
Servo rearLandingGearServo;
Servo bombBayServo;
Servo missileServo;
Servo xCameraServo;
Servo yCameraServo;

int leftWingPin = 2;
int rightWingPin = 3;
int frontLandingGearPin = 4;
int rearLandingGearPin = 5;
int bombBayPin = 6;
int missilePin = 7;
int xCameraPin = 8;
int yCameraPin = 9;

bool bombingState = false;

//LANDING GEAR
bool landingGearDeployed = false;
int landingGearAngle = 90;

//BOMB BAY
bool bombBayOpen = false;
int bombBayAngle = 90;

void setup() {
  leftWingServo.attach(leftWingPin);
  rightWingServo.attach(rightWingPin);
  frontLandingGearServo.attach(frontLandingGearPin);
  rearLandingGearServo.attach(rearLandingGearPin);
  bombBayServo.attach(bombBayPin);
  missileServo.attach(missilePin);
  xCameraServo.attach(xCameraPin);
  yCameraServo.attach(yCameraPin);

  pinMode(leftWingServo, OUTPUT);
  pinMode(rightWingServo, OUTPUT);
  pinMode(frontLandingGearServo, OUTPUT);
  pinMode(rearLandingGearServo, OUTPUT);
  pinMode(bombBayServo, OUTPUT);
  pinMode(missileServo, OUTPUT);
  pinMode(xCameraServo, OUTPUT);
  pinMode(yCameraServo, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //HANDLE AUTO STEADY HERE
  
  //AILERONS
  if (false) {
    //deal with calculations n shit
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

  //CAMERA
  if (false) {
    //CAMERA SHIT
  }
}
