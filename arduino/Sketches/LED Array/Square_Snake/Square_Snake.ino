#include "LedControl.h"
LedControl lc=LedControl(7,5,6,1);

void setup() {
  // put your setup code here, to run once:
lc.shutdown(0,false);
lc.setIntensity(0,8);
}

void loop() {
  // put your main code here, to run repeatedly:
  int RowRight=7;
  int RowLeft=0;
  int ColTop=0;
  int ColBottom=7;

int rate=10;

for (int count=0; count<4; count++)
{
  for (int i=RowLeft; i<RowRight+1; i++)
{
  lc.setLed(0,ColTop,i,true);
  delay(rate);
}
for (int i=ColTop+1; i<ColBottom+1; i++)
{
  lc.setLed(0,i,RowRight,true);
  delay(rate);
}
for (int i=RowRight-1; i>RowLeft-1; i--)
{
  lc.setLed(0,ColBottom,i,true);
  delay(rate);
}
for (int i=ColBottom-1; i>ColTop; i--)
{
  lc.setLed(0,i,RowLeft,true);
  delay(rate);
}

RowLeft=RowLeft+1;
RowRight=RowRight-1;
ColTop=ColTop+1;
ColBottom=ColBottom-1;

}

RowRight=7;
RowLeft=0;
ColTop=0;
ColBottom=7;

for (int count=0; count<4; count++)
{
  for (int i=RowLeft; i<RowRight+1; i++)
{
  lc.setLed(0,ColTop,i,false);
  delay(rate);
}
for (int i=ColTop+1; i<ColBottom+1; i++)
{
  lc.setLed(0,i,RowRight,false);
  delay(rate);
}
for (int i=RowRight-1; i>RowLeft-1; i--)
{
  lc.setLed(0,ColBottom,i,false);
  delay(rate);
}
for (int i=ColBottom-1; i>ColTop; i--)
{
  lc.setLed(0,i,RowLeft,false);
  delay(rate);
}

RowLeft=RowLeft+1;
RowRight=RowRight-1;
ColTop=ColTop+1;
ColBottom=ColBottom-1;

}

}
