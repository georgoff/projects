int trigPin = 7;
int echoPin = 8;
int speakerPin = 10;
double duration, cm, inches;

double max_distance = 10.0;
double min_distance = 2.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  ///// [BEGIN] Ultrasonic Sensor /////
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = (duration/2.0) / 29.1;
  inches = (duration/2.0) / 74.0;

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.println();
  ///// [END] Ultrasonic Sensor /////

  ///// [BEGIN] Tone Logic /////
  if(inches >= max_distance) {
    digitalWrite(speakerPin, LOW);
  }

  if(inches <= min_distance) {
    tone(speakerPin, 800);
  }

  if(inches < max_distance && inches > min_distance) {
    tone(speakerPin, 800);
    delay(40);
    // only need to vary the "off" time:
    noTone(speakerPin);
    delay(inches*10);
  }
  ///// [END] Tone Logic /////

}
