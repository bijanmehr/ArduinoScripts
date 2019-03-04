#define delay_time 50
#define LED_pin 13
#define relay1_pin 3
#define relay2_pin 4


uint8_t input = 0;
uint8_t pins[8] = {5, 6, 7, 8, 9, 10, 11, 12};
uint32_t timer = 0 ;
uint8_t pins_state = 0 ;
bool lightwheel_flag = false;
String curtain_state;

void setup() {
  for (uint8_t i; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
  pinMode(LED_pin, OUTPUT);
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    input = Serial.read() - 48;

    if (input == 1) { // curtain up command and set led on
      curtain_state = "up";
      digitalWrite(LED_pin, HIGH);
      digitalWrite(relay1_pin, HIGH);
      digitalWrite(relay2_pin, LOW);
      delay(80000);
      digitalWrite(relay1_pin, LOW);
      digitalWrite(relay2_pin, LOW);
    }
    if (input == 2) { // curtain down command and set led off
      curtain_state = "down";
      digitalWrite(LED_pin, LOW);
      digitalWrite(relay1_pin, LOW);
      digitalWrite(relay2_pin, HIGH);
      delay(80000);
      digitalWrite(relay1_pin, LOW);
      digitalWrite(relay2_pin, LOW);
    }

    if (input == 3) { // led on
      digitalWrite(LED_pin, HIGH);
    }

    if (input == 4) { // led off
      digitalWrite(LED_pin, LOW);
    }
    
    if (input == 5) {
      lightwheel_flag = true;
    }
    if (input == 6) {
      lightwheel_flag = false;

      for (uint8_t i; i < 8; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
      }
    }
    Serial.println(input);
  }


  if ( millis() - timer >= delay_time && lightwheel_flag == true) {
    timer = millis();
    for (uint8_t i; i < 8; i++) {
      digitalWrite(pins[i], LOW);
    }
    digitalWrite(pins[pins_state], HIGH);

    pins_state++;
    if (pins_state >= 8)
      pins_state = 0;
  }
}
