int pushButtonPin = 0;
int VRyPin = 0;
int VRxPin = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pushButtonPin, INPUT);
  digitalWrite(pushButtonPin, HIGH);
  pinMode(VRyPin, INPUT);
  pinMode(VRxPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  double button = digitalRead(pushButtonPin);
  double y = analogRead(VRyPin);
  double x = analogRead(VRxPin);

  Serial.print("x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.print(y);
  Serial.print(", button = ");
  Serial.print(button);
  Serial.println();
}
