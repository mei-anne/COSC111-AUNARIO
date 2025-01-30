//LED pins
int ledPins[] = {3, 5, 6, 9, 10};
int brightness = 0;
int fadeAmount = 5;
int index = 0;

void setup() {
  index = 0;
  while (index < 5){
    pinMode(ledPins[index], OUTPUT);
    index++;
  }
}

void loop(){
  index = 0;
  while (index < 5){
    fadeLED (ledPins[index], true);
    index++;
  }
  index = 0;
  while (index < 5){
    fadeLED (ledPins[index], false);
    index++;
  }

  brightness = brightness + fadeAmount;
  if(brightness <= 0 || brightness >= 255){
    fadeAmount = -fadeAmount;
  }
}

void fadeLED (int pin, bool fadeIn){
  int brightness = (fadeIn) ? 0 : 255;
  int fadeAmount = (fadeIn) ? 5 : -5;

  while ((fadeIn && brightness <= 255) || (!fadeIn && brightness >= 0)){
    analogWrite(pin, brightness);
    brightness += fadeAmount;
    delay(30);
  }
}