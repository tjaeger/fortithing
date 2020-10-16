
const int buttonPin = 18;  // ONLY on v2.0-rev.A "GA" - this is Pin35/GPIO18

int buttonState = 0;

void setup() {
  Serial.begin(115200);  
  digitalWrite(buttonPin, HIGH);
  pinMode(buttonPin, INPUT);
  
  
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  delay(300);
}
