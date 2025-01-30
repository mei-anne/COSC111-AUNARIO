const int buttonPin = 12;  // Pin connected to the button
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  Serial.begin(9600);                // Initialize serial communication
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Read the state of the button

  // Send `group1_on` when button is pressed (HIGH) and `group1_off` when not pressed (LOW)
  if (buttonState == HIGH) {  // Button pressed
    Serial.println("group1_on");
  } else {                   // Button not pressed
    Serial.println("group1_off");
  }

  delay(2000);  // Adjust delay to control the frequency of messages
}
