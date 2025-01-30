const int lightSpeed = 1000;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  int pins[] = {12, 11, 10, 9, 8};

  // ON
  for (int i = 0; i < 5; i++) {
    digitalWrite(pins[i], HIGH);
    delay(lightSpeed);
  }

  // OFF
  for (int i = 0; i < 5; i++) {
    digitalWrite(pins[i], LOW);
    delay(lightSpeed);
  }
}
