#include <LedControl.h>

///// [BEGIN] LED PREP /////

// LedControl(a,b,c,d)
// a = DATA IN
// b = CLOCK
// c = CS
// d = # of boards

int DATA_IN = 8;
int CLOCK = 9;
int CS = 10;

LedControl lc=LedControl(DATA_IN, CLOCK, CS, 1);

// lc.setLed(address, row, col, state)

int x_0 = random(0,8);
int y_0 = random(0,8);

int prev_x = 0;
int prev_y = 0;
int curr_x = x_0;
int curr_y = y_0;

int prev_target_x = 0;
int prev_target_y = 0;
int curr_target_x = random(0,8);
int curr_target_y = random(0,8);

///// [END] LED PREP /////


///// [BEGIN] JOYSTICK PREP /////

int pushButtonPin = 0; // digital
int VRyPin = 0; // analog
int VRxPin = 1; // analog

///// [END] JOYSTICK PREP /////

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);
  lc.setIntensity(0,8);

  pinMode(pushButtonPin, INPUT);
  digitalWrite(pushButtonPin, HIGH);
  pinMode(VRyPin, INPUT);
  pinMode(VRxPin, INPUT);

  randomSeed(analogRead(5));

  // x = COLUMNS (left = 0, right = 7)
  // y = ROWS (top = 0, bottom = 7)

  while(curr_target_x == curr_x || curr_target_y == curr_y) {
  curr_target_x = random(0,8);
  curr_target_y = random(0,8);
}

  lc.setLed(0, y_0, x_0, true);
//  lc.setLed(0, curr_target_y, curr_target_x, true);
  moveTargetSquare(curr_target_x, curr_target_y);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reset = digitalRead(pushButtonPin);

  int xJoy = analogRead(VRxPin);
  int yJoy = analogRead(VRyPin);

  if(!reset) {
//    moveToHere(random(0,8), random(0,8));
//    moveTargetDot(random(0,8), random(0,8));
  moveTargetSquare(random(0,8), random(0,8));
  }

  if(xJoy < 100 && curr_x > 0) {
    moveToHere(curr_x - 1, curr_y);
  }

  if(xJoy > 924 && curr_x < 7) {
    moveToHere(curr_x + 1, curr_y);
  }

  if(yJoy < 100 && curr_y > 0) {
    moveToHere(curr_x, curr_y - 1);
  }

  if(yJoy > 924 && curr_y < 7) {
    moveToHere(curr_x, curr_y + 1);
  }

  delay(500);
}

void moveToHere(int dest_x, int dest_y) {
  prev_x = curr_x;
  prev_y = curr_y;

  curr_x = dest_x;
  curr_y = dest_y;

  lc.setLed(0, prev_y, prev_x, false);
  lc.setLed(0, curr_y, curr_x, true);
}

void moveTargetDot(int new_target_x, int new_target_y) {

  prev_target_x = curr_target_x;
  prev_target_y = curr_target_y;

  curr_target_x = new_target_x;
  curr_target_y = new_target_y;

  while(curr_target_x == curr_x || curr_target_y == curr_y) {
    curr_target_x = random(0,8);
    curr_target_y = random(0,8);
  }

  lc.setLed(0, prev_target_y, prev_target_x, false);
  lc.setLed(0, curr_target_y, curr_target_x, true);
}

void moveTargetSquare(int new_target_x, int new_target_y) {

  prev_target_x = curr_target_x;
  prev_target_y = curr_target_y;

  curr_target_x = new_target_x;
  curr_target_y = new_target_y;

  while(curr_target_x == curr_x || curr_target_y == curr_y) {
    curr_target_x = random(0,8);
    curr_target_y = random(0,8);
  }
  
  lc.setLed(0, prev_target_y - 1, prev_target_x, false);
  lc.setLed(0, prev_target_y + 1, prev_target_x, false);
  lc.setLed(0, prev_target_y - 1, prev_target_x - 1, false);
  lc.setLed(0, prev_target_y + 1, prev_target_x - 1, false);
  lc.setLed(0, prev_target_y - 1, prev_target_x + 1, false);
  lc.setLed(0, prev_target_y + 1, prev_target_x + 1, false);
  lc.setLed(0, prev_target_y, prev_target_x + 1, false);
  lc.setLed(0, prev_target_y, prev_target_x - 1, false);
  
  lc.setLed(0, new_target_y - 1, new_target_x, true);
  lc.setLed(0, new_target_y + 1, new_target_x, true);
  lc.setLed(0, new_target_y - 1, new_target_x - 1, true);
  lc.setLed(0, new_target_y + 1, new_target_x - 1, true);
  lc.setLed(0, new_target_y - 1, new_target_x + 1, true);
  lc.setLed(0, new_target_y + 1, new_target_x + 1, true);
  lc.setLed(0, new_target_y, new_target_x + 1, true);
  lc.setLed(0, new_target_y, new_target_x - 1, true);
}



