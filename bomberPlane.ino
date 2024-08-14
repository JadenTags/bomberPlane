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

int leftAileronPin = 2;
int rightAileronPin = 3;
int elevatorPin = 4;
int rudderPin = 5;
int frontLandingGearPin = 6;
int rearLandingGearPin = 7;
int bombBayPin = 8;
int missilePin = 9;
int xCameraPin = 10;
int yCameraPin = 11;
int motorPin = 12;

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

  pinMode(leftAileronServo, OUTPUT);
  pinMode(rightAileronServo, OUTPUT);
  pinMode(elevatorsServo, OUTPUT);
  pinMode(rudderServo, OUTPUT);
  pinMode(frontLandingGearServo, OUTPUT);
  pinMode(rearLandingGearServo, OUTPUT);
  pinMode(bombBayServo, OUTPUT);
  pinMode(missileServo, OUTPUT);
  pinMode(xCameraServo, OUTPUT);
  pinMode(yCameraServo, OUTPUT);
  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (!bombingState) {
    //THROTTLE
    if (false) {

    }

    //AILERONS
    if (false) { //ONE IF FOR ROLL AND ANOTHER IF FOR TAKEOFF/LANDING
      //deal with calculations n shit
    } else {
      //HANDLE AUTO STEADY HERE
    }

    //ELEVATORS
    if (false) {

    }

    //RUDDER
    if (false) {

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
}