// Declare global variables:
int rawValue; // potentiometer output
int curSpeed = 0; // current speed (0-255)
int desSpeed; // desired speed (0-255)
float BUF = 0.05; // buffer zone, specified as a percentage
float upThres = 512+(round(BUF*512)); // upper threshold of buffer zone
float lowThres = 512-(round(BUF*512)); // lower threshold of buffer zone
int rampDelay = 1; // ramp delay in ms (higher means slower ramp)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Set up serial monitor
Serial.println(lowThres);
Serial.println(upThres);
}

int determineSpeed(int rawValue)
{
  // This function takes in potentiometer value and returns the desired speed
  int result;

  if(rawValue<upThres && rawValue>lowThres)
{
  result = 0;
}
else if(rawValue<lowThres)
{
  result = round((1-(rawValue/lowThres))*-255);
}
else if(rawValue>upThres)
{
  result = round(((rawValue-upThres)/lowThres)*255);
}
return result;
}

void loop() {
  // put your main code here, to run repeatedly:
rawValue = 485;
desSpeed = determineSpeed(rawValue);
Serial.println(desSpeed);
delay(50000);

}
