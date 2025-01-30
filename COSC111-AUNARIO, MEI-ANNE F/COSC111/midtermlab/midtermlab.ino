int sensorPin = A0;  // P-SENSOR KONEKTED SA A0 PIN
int lightValue;      // VARIABLE PARA SA L-INTENSITY
int lightPercent;    // Variable PARA SA CONVERTED L-INTENSITY IN PERCENTAGE

int greenLED = 11;   // G-LED TO PIN 11
int yellowLED = 12;  // Y-LED TO PIN 12
int redLED = 13;     // R-LED TO PIN 13

int lowThreshold = 40;   // DEFAULT LOW THRESHOLD
int highThreshold = 70;  // DEAFULT HIGH THRESHOLD

String currentMode = "Manual/Automatic";  // DEFAULT MODE (Manual/Automatic)
String environment = "Cloudy/Clear/Bright Sunlight";  // DEFAULT ENVIRONMENT (Cloudy/Clear/Bright Sunlight)

void setup() {
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // TAGA-READ NG IN-INPUT NI USER NA COMMAND MODE
    command.trim();  // PAG NASOBRAHAN NG SPACE YUNG INPUT NI USER
    command.toUpperCase();  //PANG HANDLE KAPAG LOWER CASE NILAGAY NI USER

    // HANDLE NG PAGPAPALIT NG CURRENT MODE KAPAG NAG TYPE SI USER
    handleModeSwitching(command);

    // PANG-HANDLE NG MODE IF MANUAL NILAGAY NI USER
    if (currentMode == "Manual") {
      handleThresholdAdjustment(command);
    }
  }

  // VOID NAME NA TUMATAWAG PARA SA CURRENT MODE
  adjustEnvironmentForManualAndAutomaticMode();

  // MAPPING NG SENSOR FROM ANALOG TO DIGITAL (INSTEAD OF 255 HERE, NAKA-PERCENTAGE)
  lightValue = analogRead(sensorPin);
  lightPercent = map(lightValue, 0, 1023, 0, 100);

  // VOID NAME NA TUMATAWAG PARA SA CONTROL NG LEDS
  controlLEDs();

  // VOID NAME NA TUMATAWAG PARA SA PAG DISPLAY NG STATUS
  displayStatus();

  delay(1000);  // DELAY NG 1 SEC
}
// HANDLER NG CONDITIONS PARA SA SWITCHING NG MODE
void handleModeSwitching(String command) {
  if (command == "MODE AUTO") {
    currentMode = "Automatic";
    Serial.println("Switched to Automatic mode");
  } else if (command == "MODE MANUAL") {
    currentMode = "Manual";
    Serial.println("Switched to Manual mode");
  } else {
    Serial.println("Error: Wrong Command");
  }
}
// HANDLER NG CONDITIONS PARA SA MANUAL SET UP NG THRESHOLD
void handleThresholdAdjustment(String command) {
  if (command.startsWith("SET LOW ")) {
    lowThreshold = command.substring(8).toInt();  // READER NG SINET NI USER SA LOW THRESHOLD
    Serial.print("Low threshold set to: ");
    Serial.println(lowThreshold);
  } else if (command.startsWith("SET HIGH ")) {
    highThreshold = command.substring(9).toInt();  // READER NG SINET NI USER SA HIGH THRESHOLD
    Serial.print("High threshold set to: ");
    Serial.println(highThreshold);
  } else {
    Serial.println("Error: Wrong Command");
  }
}

// HANDLER NG CONDITION PARA SA VALUE NA LALABAS NA ENVIRONMENT FOR MANUAL AND AUTO 
void adjustEnvironmentForManualAndAutomaticMode() {
  if (lightPercent < lowThreshold) {
    environment = "Cloudy";
  } else if (lightPercent < highThreshold) {
    environment = "Normal";
  } else {
    environment = "Bright Sunlight";
  }
}

// DISPLAY NG LEDS AT CONDITION PARA SA PAGPAPALIT NG PAGBUKAS NG ILAW DEPENDE SA LIGHT INTENSITY
void controlLEDs() {
  if (lightPercent < lowThreshold) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    Serial.println("--- ");
    Serial.println("Active LED: Green");
  } else if  (lightPercent < highThreshold) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    Serial.println("--- ");
    Serial.println("Active LED: Yellow");
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    Serial.println("--- ");
    Serial.println("Active LED: Red");
  }
}

// DIPLAY NG LIGHT INTENSITY, MODE, AND ENVIRONMENT
void displayStatus() {
  Serial.print("Light Intensity: ");
  Serial.print(lightPercent);
  Serial.println("%");

  Serial.print("Current Mode: ");
  Serial.println(currentMode);

  Serial.print("Environment: ");
  Serial.println(environment);
  Serial.println("---");
}
