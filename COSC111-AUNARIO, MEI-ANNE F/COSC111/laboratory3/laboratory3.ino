#include <math.h> //to provide right celsius format

//pins using #define
#define THERMISTOR_PIN A0   
#define PHOTORESISTOR_PIN A2 
#define LED_PIN 12           

//threshold
const int TEMP_THRESHOLD = 50;  
const int BRIGHTNESS_THRESHOLD = 220;

//thermistor calculation
const float BETA = 3950;     
const float ROOM_TEMP_RESISTANCE = 10000; 
const float SERIES_RESISTOR = 10000;  

//temperature
float readTemperature() {
  int analogValue = analogRead(THERMISTOR_PIN);
  
  // Convert the analog value to resistance of the thermistor
  float resistance = SERIES_RESISTOR * (1023.0 / analogValue - 1);
  
  // Convert the resistance to temperature using the BETA parameter
  float temperature = 1 / (log(resistance / ROOM_TEMP_RESISTANCE) / BETA + 1 / 298.15) - 273.15;

  return temperature;
}

//brightness
int readBrightness() {
  return analogRead(PHOTORESISTOR_PIN);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temperature = readTemperature();
  int brightness = readBrightness();
  
  //print
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Brightness: ");
  Serial.println(brightness);

  //limit checker
  if (temperature >= TEMP_THRESHOLD && brightness >= BRIGHTNESS_THRESHOLD) {
    //when fire is detected
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  } else {
    //when no fire is detected
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);
}
