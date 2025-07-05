#define dirPin 8
#define stepPin 9

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void loop() {
  // Giro horario
  digitalWrite(dirPin, HIGH);
  for (int i = 0; i < 400; i++) {  // 1 vuelta a 1/8 paso
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);

  // Giro antihorario
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 400; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);
}
