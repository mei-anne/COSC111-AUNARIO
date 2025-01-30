# Arduino LED Fading Sequence

This Arduino project creates a fading effect for five LEDs connected to pins 3, 5, 6, 9, and 10. The LEDs will fade in and out one by one, using PWM to adjust the brightness smoothly. The fading effect is achieved by adjusting the brightness of each LED over time.

## Components Needed
- 1 Arduino board (e.g., Uno, Nano, etc.)
- 5 LEDs
- 5 resistors (220Ω or 330Ω recommended)
- Breadboard and jumper wires

## Circuit Setup
1. Connect the anode (long leg) of each LED to pins 3, 5, 6, 9, and 10 on the Arduino.
2. Connect the cathode (short leg) of each LED to the ground (GND) on the Arduino through a resistor.

## Code Explanation

```cpp
// LED pins
int ledPins[] = {3, 5, 6, 9, 10};  // Pins where LEDs are connected
int brightness = 0;                 // Current brightness level (0 to 255)
int fadeAmount = 5;                 // Amount to change brightness by
int index = 0;                      // LED index for iteration

void setup() {
  index = 0;
  // Initialize the pins connected to LEDs as OUTPUT
  while (index < 5){
    pinMode(ledPins[index], OUTPUT);
    index++;
  }
}

void loop(){
  index = 0;
  // Fade LEDs in sequence
  while (index < 5){
    fadeLED (ledPins[index], true);  // Fade in LED
    index++;
  }
  index = 0;
  // Fade LEDs out sequence
  while (index < 5){
    fadeLED (ledPins[index], false); // Fade out LED
    index++;
  }

  // Control the overall brightness change across LEDs
  brightness = brightness + fadeAmount;
  if(brightness <= 0 || brightness >= 255){
    fadeAmount = -fadeAmount;  // Reverse the direction of fading once limits are reached
  }
}

void fadeLED (int pin, bool fadeIn){
  int brightness = (fadeIn) ? 0 : 255;  // Set starting brightness based on fade direction
  int fadeAmount = (fadeIn) ? 5 : -5;   // Set the fade step size

  // Fade the LED up or down smoothly
  while ((fadeIn && brightness <= 255) || (!fadeIn && brightness >= 0)){
    analogWrite(pin, brightness);  // Set the LED brightness using PWM
    brightness += fadeAmount;      // Increase or decrease brightness
    delay(30);                     // Delay to create smooth fading effect
  }
}
