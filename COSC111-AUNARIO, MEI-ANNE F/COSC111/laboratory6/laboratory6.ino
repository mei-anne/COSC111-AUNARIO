// Pin where the LED is connected
const int ledPin = 13;

void setup() {
  // Initialize the LED pin as output
  pinMode(ledPin, OUTPUT);

  // Start the serial communication
  Serial.begin(9600);
  while (!Serial) {
    // Wait for the serial port to connect (only needed for some boards)
  }
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming byte
    char command = Serial.read();

    // Perform action based on the command received
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Turn the LED on
      Serial.println("LED ON");
    } else if (command == '0') {
      digitalWrite(ledPin, LOW); // Turn the LED off
      Serial.println("LED OFF");
    }
  }
}
