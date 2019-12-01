int speaker_pin = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

//  for(int i = 0; i <= 127; i++) {
//    analogWrite(speaker_pin, i);
//    delay(40);
//  }

  tone(speaker_pin, 1000, 500);
  delay(1000);
}
