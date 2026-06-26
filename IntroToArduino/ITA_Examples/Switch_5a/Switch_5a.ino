/*
 * Switch 5a - Reading a Static Switch
 */

void setup() {
  pinMode(5, INPUT_PULLUP);   // use pin 5 as a INPUT. Activate internal resistor.
  pinMode(13, OUTPUT);        // configure to use on-board LED.
}

// put your main code here, to run repeatedly:
void loop() {
#if 1
  // Simple way.
  if(digitalRead(5) == LOW) {
    digitalWrite(13, LOW);        // Turn OFF LED.
  } else {
    digitalWrite(13, HIGH);       // Turn ON LED.
  }
#else
  // Compact way
  digitalWrite(13, digitalRead(5));
#endif
}
