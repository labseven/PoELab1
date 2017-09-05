/*
 * Jared and Adam Poe Lab 1
 */

const int num_leds = 3;
const int ledPins = [10, 11, 12];

const int buttonPin = 7;

void setup() {
  for (int i=0; i < num_leds; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT);
}

void loop() {
  // Do the blinking
}
