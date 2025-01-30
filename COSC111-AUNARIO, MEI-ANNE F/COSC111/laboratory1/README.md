# Arduino LED Sequence Control

This simple Arduino project controls five LEDs connected to pins 8 through 12. The LEDs will light up sequentially, stay on for a short period of time, and then turn off sequentially. This behavior is controlled using an Arduino script.

## Components Needed
- 1 Arduino board (e.g., Uno, Nano, etc.)
- 5 LEDs
- 5 resistors (220Ω or 330Ω recommended)
- Breadboard and jumper wires

## Circuit Setup
1. Connect the anode (long leg) of each LED to pins 8, 9, 10, 11, and 12 on the Arduino.
2. Connect the cathode (short leg) of each LED to the ground (GND) on the Arduino through a resistor.

## Code Explanation

```cpp
const int lightSpeed = 1000;  // Delay time (in milliseconds) between turning LEDs on/off

void setup() {
  // Set pins 8, 9, 10, 11, and 12 as OUTPUT
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  int pins[] = {12, 11, 10, 9, 8};  // Array holding the pin numbers

  // Turn LEDs on in sequence
  for (int i = 0; i < 5; i++) {
    digitalWrite(pins[i], HIGH);   // Turn on the LED
    delay(lightSpeed);             // Wait for 'lightSpeed' milliseconds
  }

  // Turn LEDs off in sequence
  for (int i = 0; i < 5; i++) {
    digitalWrite(pins[i], LOW);    // Turn off the LED
    delay(lightSpeed);             // Wait for 'lightSpeed' milliseconds
  }
}
