// Date: 11/7/17
// Author: Alec Georgoff
// Purpose: Create "slow trail" random LED pattern

#include "LedControl.h"
LedControl lc = LedControl(7,5,6,1);
// LedControl(DIN, CLK, CS, #matrices)

int rows[] = {1,2,3,4,5};
int cols[] = {1,2,3,4,5};

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false); // Turn off power-saving mode
  lc.setIntensity(0,8); // Intensity from 0-15
}

void TakeStep(int TheArray[]) { // "shift" all values of position array
  for (int i = (sizeof(TheArray)/sizeof(int))-1; i >= 0; i--) {
    if (i == 0) {
      TheArray[i] = random(8);
    }
    else {
      TheArray[i] = TheArray[i-1];
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (rows[0] == rows[1] || cols[0] == cols[1]) {
    rows[0] = random(8);
    cols[0] = random(8);
  }

//  lc.setLed(0,new_loc[0],new_loc[1],true);
//  delay(200);
//  lc.setLed(0,old_loc[0],old_loc[1],false);
//  delay(200);

  for (int i = 0; i < 5; i++) {
    lc.setLed(0,rows[i],cols[i],true);
  }

  lc.setLed(0,rows[4],cols[4],false);

  TakeStep(rows);
  TakeStep(cols);
}
