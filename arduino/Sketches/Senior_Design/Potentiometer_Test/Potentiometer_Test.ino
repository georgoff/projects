// The purpose of this code is to read potentiometer values at various grip positions. It can be used
// for either linear or rotational potentiometers, depending upon which sections are commented out

int rawlinValue;
int rawrotValue;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(7, OUTPUT);
digitalWrite(7, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
//rawlinValue = analogRead(A2);
rawrotValue = analogRead(A2);
//Serial.println(rawlinValue);
Serial.println(rawrotValue);
delay(100);
}
