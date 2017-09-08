/*
 * Jared and Adam Poe Lab 1
 */

const int num_leds = 5;
const int led_pins[] = {8, 9, 10, 11, 12};

const int button_pin = 2;  // Pins 2 & 3 support interrupts
const int pot_pin = A0;

const int pot_max = 910;  // Maximum value from pot
const int pot_led_index = pot_max / num_leds;  // Value per LED

int cur_mode = 0;
const int num_modes = 4;

unsigned long last_debounce_millis = 0;
unsigned long cur_debounce_millis = 0;
const int debounce_delay = 100;

unsigned long last_time_millis = 0;
unsigned long cur_time_millis = 0;

bool mode_blinking_led_status = false;
const int mode_blinking_delay_millis = 300;


const bool debug = false;

void mode_on(){
  /* All LEDs on */
  if (debug) {
    Serial.println("mode_on");
  }
   for (int i=0; i < num_leds; i++){
    digitalWrite(led_pins[i], HIGH);
  }
}

void mode_off(){
  /* All LEDs off */
  if (debug) {
    Serial.println("mode_off");
  }
  for (int i=0; i < num_leds; i++){
    digitalWrite(led_pins[i], LOW);
  }
}

void mode_blinking(){
  /* Blink LEDs every mode_blinking_delay_millis ms */
  if (debug) {
    Serial.println("mode_blinking");
  }

  cur_time_millis = millis();
  if (cur_time_millis - last_time_millis > mode_blinking_delay_millis) {
    last_time_millis = cur_time_millis;
    mode_blinking_led_status = !mode_blinking_led_status;
     for (int i=0; i < num_leds; i++){
      digitalWrite(led_pins[i], mode_blinking_led_status);
    }
  }
}

void mode_adjust(){
 /* Use the pot to pick an LED to be on */
 if (debug) {
  Serial.println("mode_adjust");
 }
 int cur_pin_on = analogRead(pot_pin) / pot_led_index; // Index of pin to turn on
 for (int i=0; i < num_leds; i++){
    digitalWrite(led_pins[i], i == cur_pin_on);  // True if i = cur_pin_on, else false
  }
}


void increment_mode(){
  cur_debounce_millis = millis();
  if(cur_debounce_millis - last_debounce_millis < debounce_delay){
    return;
  }

  last_debounce_millis = cur_debounce_millis;

  cur_mode++;
  if (cur_mode == num_modes){
    cur_mode = 0;
  }
}

void setup() {
  Serial.begin(9600);

  for (int i=0; i < num_leds; i++){
    pinMode(led_pins[i], OUTPUT);
  }

  pinMode(button_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), increment_mode, FALLING);
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
