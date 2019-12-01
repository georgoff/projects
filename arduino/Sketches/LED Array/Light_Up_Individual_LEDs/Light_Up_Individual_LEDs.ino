#include "LedControl.h" 
LedControl lc=LedControl(8,9,10,1);

void setup() {
  // put your setup code here, to run once:
lc.shutdown(0,false); //change to true to keep LEDs off
lc.setIntensity(0,8); //intensity 0-8
}

void loop() {
  // put your main code here, to run repeatedly:
lc.setLed(0,0,3,true);
}
