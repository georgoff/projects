int inputPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(inputPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  double voltage = analogRead(inputPin);

  Serial.print(voltage);
  Serial.println();

  delay(100);
}
