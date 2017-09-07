/*
 * Jared and Adam Poe Lab 1
 */

const int num_leds = 5;
const int ledPins[] = {8, 9, 10, 11, 12};

const int buttonPin = 2;  // Pins 2 & 3 support interrupts
const int potPin = A0;

const int potMax = 910;
const int potLedIndex = potMax / num_leds;

int cur_mode = 0;
const int num_modes = 4;

unsigned long lastDebounceMillis = 0;
unsigned long curDebounceMillis = 0;
const int debounceDelay = 100;

unsigned long lastTimeMillis = 0;
unsigned long curTimeMillis = 0;

bool mode_blinking_led_status = false;
const int mode_blinking_delay_millis = 500;


const bool debug = false;

void mode_on(){
  if (debug) {
    Serial.println("mode_on");
  }
   for (int i=0; i < num_leds; i++){
    digitalWrite(ledPins[i], HIGH);
  }
}

void mode_off(){
  if (debug) {
    Serial.println("mode_off");
  }
  for (int i=0; i < num_leds; i++){
    digitalWrite(ledPins[i], LOW);
  }
}

void mode_blinking(){
  if (debug) {
    Serial.println("mode_blinking");
  }

  curTimeMillis = millis();
  if (curTimeMillis - lastTimeMillis > mode_blinking_delay_millis) {
    lastTimeMillis = curTimeMillis;
    mode_blinking_led_status = !mode_blinking_led_status;
     for (int i=0; i < num_leds; i++){
      digitalWrite(ledPins[i], mode_blinking_led_status);
    }
  }

}

void mode_adjust(){
 if (debug) {
  Serial.println("mode_adjust");
 }
 for (int i=0; i < num_leds; i++){
    digitalWrite(ledPins[i], LOW);
  }
 digitalWrite(ledPins[analogRead(potPin) / potLedIndex], HIGH);
 
}


void increment_mode(){
  curDebounceMillis = millis();
  if(curDebounceMillis - lastDebounceMillis < debounceDelay){
    return;
  }

  lastDebounceMillis = curDebounceMillis;
  
  cur_mode++;
  if (cur_mode == num_modes){
    cur_mode = 0;
  }
}

void setup() {
  Serial.begin(9600);
  
  for (int i=0; i < num_leds; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT);
  attachInterrupt(0, increment_mode, FALLING);
}

void loop() {
  switch (cur_mode) {
    case 0:
      mode_off();
      break;
      
    case 1:
      mode_on();
      break;
      
    case 2:
      mode_blinking();
      break;
      
    case 3:
      mode_adjust();
      break;
      
    default:
      Serial.println("switch failed");
  }
}



