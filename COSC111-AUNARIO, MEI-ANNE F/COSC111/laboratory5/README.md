# Arduino Button Press Detection System

This project demonstrates how to use a button to send a signal to an Arduino and print the button's state (pressed or not pressed) to the Serial Monitor.

## Components Needed
- 1 Arduino board (e.g., Uno, Nano, etc.)
- 1 Button
- 1 10kΩ resistor (for internal pull-up configuration)
- Breadboard and jumper wires

## Circuit Setup
1. Connect the **button** to **digital pin 12** on the Arduino.
2. One leg of the button should be connected to pin 12, and the other leg should be connected to the **GND** pin of the Arduino.
3. The internal pull-up resistor is used, so no external resistor is needed for this setup.

## Code Explanation

```cpp
const int buttonPin = 12;  // Connect your button to pin 12
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT); // Use internal pull-up resistor
  Serial.begin(9600);        // Initialize serial communication
}

void loop() {
  buttonState = digitalRead(buttonPin); // Read button state (HIGH/LOW)

  // Send button state as 1 (pressed) or 0 (not pressed)
  if (buttonState == HIGH) { // LOW because of pull-up resistor
    Serial.println("1");    // Button pressed
  } else {
    Serial.println("0");    // Button not pressed
  }

  delay(200); // Adjust as needed to avoid spamming data
}
