/*
 * Jared and Adam Poe Lab 1
 */

const int num_leds = 3;
const int ledPins[] = {10, 11, 12};

const int buttonPin = 2;  // Pins 2 & 3 support interrupts

int cur_mode = 0;
const int num_modes = 2;

bool button_status = false;


void mode_on(){
  Serial.println("mode_on");
   for (int i=0; i < num_leds; i++){
    digitalWrite(ledPins[i], HIGH);
  }
}

void mode_off(){
  Serial.println("mode_off");
   for (int i=0; i < num_leds; i++){
    digitalWrite(ledPins[i], LOW);
  }
}


void increment_mode(){
  // Debounce here if necessary
  
  cur_mode++;
  if (cur_mode == num_modes){
    cur_mode = 0;
  }

  Serial.print("Changing mode to ");
  Serial.println(cur_mode);
  switch (cur_mode) {
    case 0:
      mode_off();
      break;
    case 1:
      mode_on();
      break;
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
  // Do the blinking
}



