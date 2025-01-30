# Arduino Serial Control LED System

This project demonstrates how to control an LED using commands sent through the Serial Monitor. You can turn the LED **ON** and **OFF** by sending `1` and `0`, respectively, via the Serial Monitor.

## Components Needed
- 1 Arduino board (e.g., Uno, Nano, etc.)
- 1 LED
- 1 220Ω resistor (current-limiting resistor for LED)
- Breadboard and jumper wires

## Circuit Setup
1. Connect the **LED** to **digital pin 13** (the onboard LED on most Arduino boards, or use another pin if preferred).
2. Use a **220Ω resistor** in series with the LED to limit the current and prevent damaging the LED.
3. The **long leg (anode)** of the LED connects to the **digital pin 13**, and the **short leg (cathode)** goes to **GND**.

## Code Explanation

```cpp
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
