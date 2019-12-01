#include "LedControl.h" 
LedControl lc=LedControl(0,1,2,1);

void setup() {
  // put your setup code here, to run once:
lc.shutdown(0,false); //change to true to keep LEDs off
lc.setIntensity(0,8); //intensity 0-8
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true); // turns on LED at col, row
      delay(25);
    }
  }
 
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false); // turns off LED at col, row
      delay(25);
    }
  }
}
