// Date: 11/7/17
// Author: Alec Georgoff
// Purpose: Light up random LEDs with adjustable delay

#include "LedControl.h"
LedControl lc=LedControl(7,5,6,1);

void setup() {
  // put your setup code here, to run once:
lc.shutdown(0,false); //change to true to keep LEDs off
lc.setIntensity(0,8); //intensity 0-8
}

void loop() {
  // put your main code here, to run repeatedly:
  int col=random(0,8);
  int row=random(0,8);
lc.setLed(0,col,row,true);
delay(0.1);
lc.setLed(0,col,row,false);
delay(0.1);

}
