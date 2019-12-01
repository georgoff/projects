#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Set up shields at different addresses and motors:
Adafruit_MotorShield rotMotors = Adafruit_MotorShield(0x60);
Adafruit_DCMotor *rotMotor_A = rotMotors.getMotor(1);
Adafruit_DCMotor *rotMotor_B = rotMotors.getMotor(2);
Adafruit_DCMotor *rotMotor_C = rotMotors.getMotor(3);

Adafruit_MotorShield linMotors = Adafruit_MotorShield(0x61);
Adafruit_DCMotor *linMotor_A = linMotors.getMotor(1);
Adafruit_DCMotor *linMotor_B = linMotors.getMotor(2);

// Declare global variables:
int linRawValue; // potentiometer output, linear
int rotRawValue; // potentiometer output, rotational

int linCurSpeed = 0; // current speed (0-255)
int rotCurSpeed = 0; // current speed (0-255)

int linDesSpeed; // desired linear speed (0-255)
int rotDesSpeed; // desired rotational speed (0-255)

int linMaxSpeed = 255; // max linear speed (0-255)
int rotMaxSpeed = 255; // max rotational speed (0-255)

float linBUF = 0.1; // linear buffer zone, specified as a percentage
float rotBUF = 0.05; // rotational buffer zone, specified as a percentage

float linCenter = 760; // linear center, where the wiper rests at neutral position
float rotCenter = 430; // rotational center, where the wiper rests at neutral position

float linRelativeMin = 600; // linear relative "zero" (max speed in one direction)
float linRelativeMax = 880; // linear relative "100" (max speed in other direction)
float rotRelativeMin = 273; // rotational relative "zero" (max speed in one direction)
float rotRelativeMax = 606; // rotational relative "100" (max speed in other direction)

int linRampDelay = 0.01; // linear ramp delay in ms (higher means slower ramp)
int rotRampDelay = 0.01; // rotational ramp delay in ms (higher means slower ramp)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Set up serial monitor
rotMotors.begin();
linMotors.begin();

pinMode(7, OUTPUT);
digitalWrite(7, HIGH);

linRelativeMin = linRelativeMin-10; // Adding these corrections prevents the wiper from going "past max"
linRelativeMax = linRelativeMax+10;
rotRelativeMin = rotRelativeMin-10;
rotRelativeMax = rotRelativeMax+10;

//if (linCenter <= 512) // This code is blocked out because these values are set by the user, but it can
                        // used for an adaptive centering system
//{
//  linRelativeMin = 0;
//  linRelativeMax = linCenter*2;
//}
//else if (linCenter > 512)
//{
//  linRelativeMax = 1023;
//  linRelativeMin = linCenter-(linRelativeMax-linCenter);
//}
//
//if (rotCenter <= 512)
//{
//  rotRelativeMin = 0;
//  rotRelativeMax = rotCenter*2;
//}
//else if (rotCenter > 512)
//{
//  rotRelativeMax = 1023;
//  rotRelativeMin = rotCenter-(rotRelativeMax-rotCenter);
//}

}

float linUpThres = linCenter+(round(linBUF*(linRelativeMax-linCenter))); // upper threshold of linear buffer zone
float linLowThres = linCenter-(round(linBUF*(linRelativeMax-linCenter))); // lower threshold of linear buffer zone

float rotUpThres = rotCenter+(round(rotBUF*(rotRelativeMax-rotCenter))); // upper threshold of linear buffer zone
float rotLowThres = rotCenter-(round(rotBUF*(rotRelativeMax-rotCenter))); // lower threshold of linear buffer zone

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

int rotDetermineSpeed(int rotRawValue)  // This function takes in potentiometer value and returns the desired speed
{
  int result;

  if(rotRawValue<rotUpThres && rotRawValue>rotLowThres)
{
  result = 0;
}
else if(rotRawValue<rotLowThres)
{
  result = round((1-((rotRawValue-rotRelativeMin)/(rotLowThres-rotRelativeMin)))*-rotMaxSpeed);
}
else if(rotRawValue>rotUpThres)
{
  result = round(((rotRawValue-rotUpThres)/(rotRelativeMax-rotUpThres))*rotMaxSpeed);
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
  if(linCurSpeed<linDesSpeed) // Ramp Up (Forward)
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
  else if(linCurSpeed>linDesSpeed && linDesSpeed>=0) // Ramp Down (Backward)
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
  else if(linDesSpeed<=0) // Ramp Up (Forward) + Ramp Up (Backward)
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
  if(linCurSpeed>linDesSpeed) // Ramp Up (Backward)
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
  else if(linCurSpeed<linDesSpeed && linDesSpeed<=0) // Ramp Down (Backward)
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
  else if(linDesSpeed>=0) // Ramp Down (Backward) + Ramp Up (Forward)
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

// **************************ROTATIONAL SECTION************************** //

rotRawValue = analogRead(A3); // Read in the potentiometer value

rotDesSpeed = rotDetermineSpeed(rotRawValue); // Find the desired speed

// CURRENTLY MOVING BACKWARD (OR NOT MOVING) //

if(rotCurSpeed>=0)
{
  if(rotCurSpeed<rotDesSpeed) // Ramp Up (Forward)
  {
    for(int i=rotCurSpeed;i<=rotDesSpeed;i++) // rotCurSpeed->rotDesSpeed
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(BACKWARD);
      rotMotor_B->run(BACKWARD);
      rotMotor_C->run(BACKWARD);
      delay(rotRampDelay);
    }
  }
  else if(rotCurSpeed>rotDesSpeed && rotDesSpeed>=0) // Ramp Down (Forward)
  {
    for(int i=rotCurSpeed;i>=rotDesSpeed;i--) // rotDesSpeed<-rotCurSpeed
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(BACKWARD);
      rotMotor_B->run(BACKWARD);
      rotMotor_C->run(BACKWARD);
      delay(rotRampDelay);
    }
  }
  else if(rotDesSpeed<=0) // Ramp Down (Forward) + Ramp Up (Backward)
  {
    for(int i=rotCurSpeed;i>=0;i--) // 0<-rotCurSpeed
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(BACKWARD);
      rotMotor_B->run(BACKWARD);
      rotMotor_C->run(BACKWARD);
      delay(rotRampDelay);
    }
    for(int i=0;i>=rotDesSpeed;i--) // rotDesSpeed<-0
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(FORWARD);
      rotMotor_B->run(FORWARD);
      rotMotor_C->run(FORWARD);
      delay(rotRampDelay);
    }
  }
}

// CURRENTLY MOVING FORWARD //

if(rotCurSpeed<0)
{
  if(rotCurSpeed>rotDesSpeed) // Ramp Up (Backward)
  {
    for(int i=rotCurSpeed;i>=rotDesSpeed;i--) // rotDesSpeed<-rotCurSpeed
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(FORWARD);
      rotMotor_B->run(FORWARD);
      rotMotor_C->run(FORWARD);
      delay(rotRampDelay);
    }
  }
  else if(rotCurSpeed<rotDesSpeed && rotDesSpeed<=0) // Ramp Down (Backward)
  {
    for(int i=rotCurSpeed;i<=rotDesSpeed;i++) // rotCurSpeed->rotDesSpeed
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(FORWARD);
      rotMotor_B->run(FORWARD);
      rotMotor_C->run(FORWARD);
      delay(rotRampDelay);
    }
  }
  else if(rotDesSpeed>=0) // Ramp Down (Backward) + Ramp Up (Forward)
  {
    for(int i=rotCurSpeed;i<=0;i++) // rotCurSpeed->0
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(FORWARD);
      rotMotor_B->run(FORWARD);
      rotMotor_C->run(FORWARD);
      delay(rotRampDelay);
    }
    for(int i=0;i<=rotDesSpeed;i++) // 0->rotDesSpeed
    {
      rotMotor_A->setSpeed(abs(i));
      rotMotor_B->setSpeed(abs(i));
      rotMotor_C->setSpeed(abs(i));
      rotMotor_A->run(BACKWARD);
      rotMotor_B->run(BACKWARD);
      rotMotor_C->run(BACKWARD);
      delay(rotRampDelay);
    }
  }
}
  linCurSpeed = linDesSpeed; // set current speed to desired (all actions are done)
  rotCurSpeed = rotDesSpeed; // set current speed to desired (all actions are done)
}
