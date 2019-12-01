#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  // put your setup code here, to run once:
AFMS.begin();
myMotor1->setSpeed(250);
myMotor2->setSpeed(250);
myMotor3->setSpeed(250);
myMotor4->setSpeed(250);
}

void loop() {
  // put your main code here, to run repeatedly:

for(int i=1;i<250;i++)
{
myMotor1->setSpeed(i);
myMotor1->run(FORWARD);
delay(1);
myMotor2->setSpeed(i);
myMotor2->run(FORWARD);
delay(1);
myMotor3->setSpeed(i);
myMotor3->run(FORWARD);
delay(1);
}
//delay(2000);
//
//myMotor1->run(RELEASE);
//delay(1000);

//for(int i=25;i<256;i++)
//{
//myMotor2->setSpeed(i);
//myMotor2->run(FORWARD);
//delay(50);


//delay(2000);
//myMotor2->run(RELEASE);
//delay(1000);

//for(int i=255;i>24;i--)
//{
//  myMotor2->setSpeed(i);
//  myMotor2->run(FORWARD);
//  delay(50);
//}

//myMotor2->run(RELEASE);
//delay(1000);
//
//for(int i=1;i<250;i++)
//{
//myMotor3->setSpeed(i);
//myMotor3->run(FORWARD);
//delay(1);
//}
//delay(2000);
//
//myMotor3->run(RELEASE);
//delay(1000);
//
//for(int i=1;i<250;i++)
//{
//myMotor4->setSpeed(i);
//myMotor4->run(FORWARD);
//delay(1);
//}
//delay(2000);
//
//myMotor4->run(RELEASE);
//delay(1000);

//myMotor1->run(FORWARD);
//myMotor2->run(FORWARD);
//myMotor3->run(FORWARD);
//myMotor4->run(FORWARD);
  

}
