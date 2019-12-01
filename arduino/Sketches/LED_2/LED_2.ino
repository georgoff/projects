void setup() {
// initialize the digital pin as an output.
// Pin 8 is our output pin
pinMode(9, OUTPUT);
}
void loop() {
digitalWrite(9, HIGH); // set the LED on
delay(100); // wait for a second
digitalWrite(9, LOW); // set the LED off
delay(100); // wait for a second
digitalWrite(11, HIGH); // set the LED on
delay(100); // wait for a second
digitalWrite(11, LOW); // set the LED off
delay(100); // wait for a second
}
