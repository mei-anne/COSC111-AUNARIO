// Pin Definitions
#define THERMISTOR_PIN A0   // Thermistor connected to analog pin A0
#define LED_PIN 12          // Red LED connected to digital pin 12

// Threshold
const int TEMP_THRESHOLD = 50;  // Temperature threshold in Celsius

// Thermistor calculation constants
const float BETA = 3950;           // Beta coefficient for the thermistor
const float ROOM_TEMP_RESISTANCE = 10000;  // Resistance of the thermistor at 25°C (10k ohm)
const float SERIES_RESISTOR = 10000;       // Series resistor value (10k ohm)

// Variables
bool stopBlinking = false;

// Function to read temperature from thermistor
float readTemperature() {
  int analogValue = analogRead(THERMISTOR_PIN);

  // Avoid divide by zero issue
  if (analogValue == 0) {
    return -273.15;  // Error reading, absolute zero (invalid)
  }

  // Calculate the thermistor resistance
  float resistance = SERIES_RESISTOR * (1023.0 / analogValue - 1);

  // Calculate temperature using the Steinhart-Hart equation
  float steinhart;
  steinhart = resistance / ROOM_TEMP_RESISTANCE;         // (R/Ro)
  steinhart = log(steinhart);                            // ln(R/Ro)
  steinhart /= BETA;                                     // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25.0 + 273.15);                    // + (1/To)
  steinhart = 1.0 / steinhart;                           // Invert
  steinhart -= 273.15;                                   // Convert to Celsius

  return steinhart;
}

// Function to check for "stop" input from Serial Monitor
void checkStopCommand() {
  if (Serial.available() > 0) {
    String input = Serial.readString();  // Read the input string
    input.trim();  // Remove any extra spaces or newline characters
    input.toLowerCase();  // Convert to lowercase to make it case-insensitive

    if (input.equals("stop")) {
      stopBlinking = true;  // Stop the blinking
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
  Serial.begin(9600);        // Initialize serial communication
  Serial.println("Type 'stop' to stop the blinking.");
}

void loop() {
  float temperature = readTemperature();   // Read temperature from thermistor

  // Print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check for stop command from Serial Monitor
  checkStopCommand();

  // Blink the LED if temperature exceeds threshold and stopBlinking is false
  if (temperature >= TEMP_THRESHOLD && !stopBlinking) {
    // Blink LED fast
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  } else {
    // Turn off LED if the temperature is below the threshold or blinking is stopped
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);  // Delay for sensor stabilization and reduce reading frequency
}
