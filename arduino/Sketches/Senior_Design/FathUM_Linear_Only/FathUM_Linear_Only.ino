#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Set up shields at different addresses and motors:

Adafruit_MotorShield linMotors = Adafruit_MotorShield(0x61);
Adafruit_DCMotor *linMotor_A = linMotors.getMotor(1);
Adafruit_DCMotor *linMotor_B = linMotors.getMotor(2);

// Declare global variables:
int linRawValue; // potentiometer output, linear

int linCurSpeed = 0; // current speed (0-255)

int linDesSpeed; // desired linear speed (0-255)

int linMaxSpeed = 255; // max linear speed (0-255)

float linBUF = 0.1; // linear buffer zone, specified as a percentage

float linCenter = 760; // linear center, where the wiper rests at neutral position

float linRelativeMin = 600; // linear relative "zero" (max speed in one direction)
float linRelativeMax = 880; // linear relative "100" (max speed in other direction)

int linRampDelay = 0.01; // linear ramp delay in ms (higher means slower ramp)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Set up serial monitor
linMotors.begin();

pinMode(7, OUTPUT);
digitalWrite(7, HIGH);

linRelativeMin = linRelativeMin-10; // Adding these corrections prevents the wiper from going "past max"
linRelativeMax = linRelativeMax+10;

}

float linUpThres = linCenter+(round(linBUF*(linRelativeMax-linCenter))); // upper threshold of linear buffer zone
float linLowThres = linCenter-(round(linBUF*(linRelativeMax-linCenter))); // lower threshold of linear buffer zone

int linDetermineSpeed(int linRawValue)  // This function takes in potentiometer value and returns the desired speed
{
  int result;

  if(linRawValue<linUpThres && linRawValue>linLowThres)
{
  result = 0;
}
else if(linRawValue<linLowThres)
{
  result = round((1-((linRawValue-linRelativeMin)/(linLowThres-linRelativeMin)))*linMaxSpeed);
}
else if(linRawValue>linUpThres)
{
  result = round(((linRawValue-linUpThres)/(linRelativeMax-linUpThres))*-linMaxSpeed);
}
return result;
}

void loop() {
  // put your main code here, to run repeatedly:

// **************************LINEAR SECTION************************** //
  
linRawValue = analogRead(A2); // Read in the potentiometer value

linDesSpeed = linDetermineSpeed(linRawValue); // Find the desired speed

// CURRENTLY MOVING FORWARD (OR NOT MOVING) //

if(linCurSpeed>=0)
{
  if(linCurSpeed<linDesSpeed) // RUF
  {
    for(int i=linCurSpeed;i<=linDesSpeed;i++) // linCurSpeed->linDesSpeed
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(FORWARD);
      linMotor_B->run(FORWARD);
      delay(linRampDelay);
    }
  }
  else if(linCurSpeed>linDesSpeed && linDesSpeed>=0) //RDF
  {
    for(int i=linCurSpeed;i>=linDesSpeed;i--) // linDesSpeed<-linCurSpeed
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(FORWARD);
      linMotor_B->run(FORWARD);
      delay(linRampDelay);
    }
  }
  else if(linDesSpeed<=0) // RDF + RUB
  {
    for(int i=linCurSpeed;i>=0;i--) // 0<-linCurSpeed
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(FORWARD);
      linMotor_B->run(FORWARD);
      delay(linRampDelay);
    }
    for(int i=0;i>=linDesSpeed;i--) // linDesSpeed<-0
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(BACKWARD);
      linMotor_B->run(BACKWARD);
      delay(linRampDelay);
    }
  }
}

// CURRENTLY MOVING BACKWARD //

if(linCurSpeed<0)
{
  if(linCurSpeed>linDesSpeed) // RUB
  {
    for(int i=linCurSpeed;i>=linDesSpeed;i--) // linDesSpeed<-linCurSpeed
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(BACKWARD);
      linMotor_B->run(BACKWARD);
      delay(linRampDelay);
    }
  }
  else if(linCurSpeed<linDesSpeed && linDesSpeed<=0) // RDB
  {
    for(int i=linCurSpeed;i<=linDesSpeed;i++) // linCurSpeed->linDesSpeed
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(BACKWARD);
      linMotor_B->run(BACKWARD);
      delay(linRampDelay);
    }
  }
  else if(linDesSpeed>=0) // RDB + RUF
  {
    for(int i=linCurSpeed;i<=0;i++) // linCurSpeed->0
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(BACKWARD);
      linMotor_B->run(BACKWARD);
      delay(linRampDelay);
    }
    for(int i=0;i<=linDesSpeed;i++) // 0->linDesSpeed
    {
      linMotor_A->setSpeed(abs(i));
      linMotor_B->setSpeed(abs(i));
      linMotor_A->run(FORWARD);
      linMotor_B->run(FORWARD);
      delay(linRampDelay);
    }
  }
}
  linCurSpeed = linDesSpeed; // set current speed to desired (all actions are done)
}
