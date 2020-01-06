#define delay_time 100
#define LED_pin A0

uint8_t motor_pins[4] = {10, 11, 12, 13};
int uppin = A7;
int downpin = A6;
int upsensor = 0;
int downsensor = 0;
uint8_t input = 0;
int upthreshold = 400;
int downthreshold = 400;
uint8_t pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
uint32_t timer = 0 ;
uint8_t pins_state = 0 ;
bool lightwheel_flag = false;
String curtain_state;


void up();
void down();
void off();

void setup() {
  for (uint8_t i; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
  for (uint8_t i; i < 4; i++) {
    pinMode(motor_pins[i], OUTPUT);
    digitalWrite(motor_pins[i], HIGH);
  }
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin,LOW);
  Serial.begin(115200);
  Serial.setTimeout(50);
  Serial.println("arduino");
}

void loop() {
  upsensor = analogRead(uppin);
  downsensor = analogRead(downpin);
  if (Serial.available()) {
//    input = Serial.read() - 48;
//    Serial.println(input);
String command = Serial.readStringUntil('\n');
//command = command.substring(1,2);
input = command.toInt();
    
    if (input == 1) { // curtain up command and set led on
      curtain_state = "up";
      digitalWrite(LED_pin, HIGH);
      do{
        upsensor = analogRead(uppin);
        up();
      }while(upsensor < upthreshold);
      off();
      Serial.println("DONE!");
    }
    if (input == 2) { // curtain down command and set led off
      curtain_state = "down";
      digitalWrite(LED_pin, LOW);
      do{
        downsensor = analogRead(downpin);
        down();
      }while(downsensor < downthreshold);
      off();
      Serial.println("DONE!");
    }
   

    if (input == 3) {
      digitalWrite(LED_pin, HIGH);
      Serial.println("DONE!");
    }

    if (input == 4) {
      digitalWrite(LED_pin, LOW);
      Serial.println("DONE!");
    }
    
    if (input == 5) {
      lightwheel_flag = true;
      Serial.println("DONE!");
    }
    if (input == 6) {
      lightwheel_flag = false;

      for (uint8_t i=0; i < 8; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
        Serial.println("DONE!");
      }
    }
  }
//     Serial.println("upsensor:  "+String(upsensor)+" "+"downsensor: "+String(downsensor));
    
  if ( millis() - timer >= delay_time && lightwheel_flag == true) {
    timer = millis();
    for (uint8_t i=0; i < 8; i++) {
      digitalWrite(pins[i], LOW);
    }
    digitalWrite(pins[pins_state], HIGH);

    pins_state++;
    if (pins_state >= 8)
      pins_state = 0;
  }

}


void down() {
//  digitalWrite(10, LOW);
//  digitalWrite(11, HIGH);
//  digitalWrite(12, HIGH);
//  digitalWrite(13, LOW);
analogWrite(A1,255);
analogWrite(A2,0);
}

void up() {
//  digitalWrite(10, HIGH);
//  digitalWrite(11, LOW);
//  digitalWrite(12, LOW);
//  digitalWrite(13, HIGH);
analogWrite(A1,0);
analogWrite(A2,255);
}

void off() {
//  digitalWrite(10, HIGH);
//  digitalWrite(11, HIGH);
//  digitalWrite(12, HIGH);
//  digitalWrite(13, HIGH);
analogWrite(A1,0);
analogWrite(A2,0);
}
