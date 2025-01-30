# Arduino Fire Detection System

This project uses a thermistor and a photoresistor to detect fire conditions based on temperature and brightness. When both conditions (temperature above a certain threshold and brightness above a certain threshold) are met, an LED will blink to indicate that a fire is potentially detected.

## Components Needed
- 1 Arduino board (e.g., Uno, Nano, etc.)
- 1 Thermistor
- 1 Photoresistor (LDR)
- 1 LED
- 1 10kΩ resistor for the thermistor
- 1 10kΩ resistor for the photoresistor
- Breadboard and jumper wires

## Circuit Setup
1. Connect the **thermistor** to analog pin A0. Use a voltage divider circuit with a 10kΩ resistor.
2. Connect the **photoresistor** to analog pin A2.
3. Connect the **LED** to pin 12, with a suitable current-limiting resistor (220Ω or 330Ω).
4. Ensure both sensors are wired correctly to the Arduino to provide analog readings.

## Code Explanation

```cpp
#include <math.h> // To provide correct celsius format for temperature readings

// Pin definitions
#define THERMISTOR_PIN A0   
#define PHOTORESISTOR_PIN A2 
#define LED_PIN 12            

// Threshold values
const int TEMP_THRESHOLD = 50;  
const int BRIGHTNESS_THRESHOLD = 220;

// Thermistor calculation constants
const float BETA = 3950;     
const float ROOM_TEMP_RESISTANCE = 10000; 
const float SERIES_RESISTOR = 10000;  

// Function to read the temperature
float readTemperature() {
  int analogValue = analogRead(THERMISTOR_PIN);
  
  // Convert the analog value to resistance of the thermistor
  float resistance = SERIES_RESISTOR * (1023.0 / analogValue - 1);
  
  // Convert the resistance to temperature using the BETA parameter
  float temperature = 1 / (log(resistance / ROOM_TEMP_RESISTANCE) / BETA + 1 / 298.15) - 273.15;

  return temperature;
}

// Function to read the brightness
int readBrightness() {
  return analogRead(PHOTORESISTOR_PIN);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as output
  Serial.begin(9600);        // Start serial communication
}

void loop() {
  float temperature = readTemperature();  // Read the temperature
  int brightness = readBrightness();     // Read the brightness
  
  // Print the values to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Brightness: ");
  Serial.println(brightness);

  // Check if the temperature and brightness exceed thresholds
  if (temperature >= TEMP_THRESHOLD && brightness >= BRIGHTNESS_THRESHOLD) {
    // If both conditions are met, simulate fire detection
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
    delay(100);                   // Keep LED on for 100ms
    digitalWrite(LED_PIN, LOW);   // Turn off LED
    delay(100);                   // Keep LED off for 100ms
  } else {
    // If no fire is detected, ensure the LED is off
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);  // Delay before reading the sensors again
}
