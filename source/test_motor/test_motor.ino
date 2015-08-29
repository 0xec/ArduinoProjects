int pwmPin = 9;
int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(sensorPin);
  int mvalue = map(value, 0, 1024, 0, 255);

  Serial.print("value=");
  Serial.print(value);
  Serial.print(", m=");
  Serial.println(mvalue);

  analogWrite(pwmPin, mvalue);

  delay(100);
}
