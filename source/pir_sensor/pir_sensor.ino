const int SensorPin = 9;
const int switcherPin = 8;
const int LEDPin = 10;
void setup() {
  
  Serial.begin(9600);
  pinMode(SensorPin, INPUT);
  pinMode(switcherPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  int sensorValue = digitalRead(SensorPin);
  Serial.println(sensorValue);

  digitalWrite(switcherPin, sensorValue);
  digitalWrite(LEDPin, !sensorValue);

  delay(300);
}
