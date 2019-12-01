void setup() {
// initialize the digital pin 9 as an input.
pinMode(9, INPUT);
// initialize the serial port.
Serial.begin(9600);
}
void loop() {
int buttonStatus = digitalRead(9);
if (buttonStatus == LOW) //The button is down
{
Serial.println("The button is down");
}
else
{
  Serial.println("The button is up");
}
}
