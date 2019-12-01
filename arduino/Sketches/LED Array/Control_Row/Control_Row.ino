#include "LedControl.h"
LedControl lc=LedControl(0,1,2,1);

void setup() {
  // put your setup code here, to run once:
lc.shutdown(0,false); //change to true to keep LEDs off
lc.setIntensity(0,8); //intensity 0-8
}

void loop() {
  // put your main code here, to run repeatedly:
  int col=random(0,8);
  int row=random(0,8);
lc.setRow(0,row,B11111111);
lc.setColumn(0,col,B11111111);
delay(25);
lc.setColumn(0,col,B10101010);
lc.setRow(0,row,B00000000);
delay(25);

}
