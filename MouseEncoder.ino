int encoder0PinA = 18;
int encoder0PinB = 19;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int val = LOW;

 
void setup() { 
    Serial.begin (115200);
    pinMode (encoder0PinA,INPUT);
    pinMode (encoder0PinB,INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder0PinA), func1,CHANGE );
} 
 
void loop() { 

    if ((encoder0PinALast == LOW) && (val == HIGH)) {
        if (digitalRead(encoder0PinB) == LOW) {
            encoder0Pos--;
        } else {
            encoder0Pos++;
        }
        Serial.println(encoder0Pos);

    } 
    encoder0PinALast = val;
}

void func1() {
  val = digitalRead(encoder0PinA);
}
