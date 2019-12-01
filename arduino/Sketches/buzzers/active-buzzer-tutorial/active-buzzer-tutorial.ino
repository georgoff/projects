int speaker_pin = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(speaker_pin, HIGH);
//  delay(500);
//  digitalWrite(speaker_pin, LOW);
//  delay(500);

  analogWrite(speaker_pin, 50);
}
