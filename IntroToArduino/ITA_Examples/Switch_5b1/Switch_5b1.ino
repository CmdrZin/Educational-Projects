/*
 * Switch 5b1 - Reading a Dynamic Switch - Complex. Used if the switch being use to change a count.
 */

#define PUSH_SWITCH  11            // push button switch is connected to pin 11

void setup() {
  pinMode(PUSH_SWITCH, INPUT_PULLUP);  // use pin 11 as a INPUT. Activate internal pullup resistor.
  pinMode(13, OUTPUT);            // configure to use on-board LED.
}

// put your main code here, to run repeatedly:
void loop() {
  if( isSwitchClosed() == true ) {
    digitalWrite(13, HIGH);       // Turn ON LED.
  } else {
    digitalWrite(13, LOW);        // Turn OFF LED.
  }
}


/*
 * Test if the switch is closed.
 * Use the millis() function to filter out switch bounce.
 * Keep returning TRUE until the switch has been released for 10ms.
 */
bool isSwitchClosed()
{
  static unsigned long bounceDelay;
  static bool waitForRelease = false;
  bool results = false;                         // default value
  // Waiting for the switch to be pressed?
  if( digitalRead(PUSH_SWITCH) == LOW ) {       // switch is pressed
      bounceDelay = millis() + 10;                // start wait for release 10ms.
      waitForRelease = true;
      results = true;                             // switch is pressed.
  } else {
    if( bounceDelay > millis() ) {            // wait for at least 10ms of switch not being pressed.
      if( digitalRead(PUSH_SWITCH) == LOW ) {  // test the switch for bounce. (i.e. is it closed?)
        bounceDelay = millis() + 10;           // reset delay. Switch bounced.
      } else {
        // still not pressed.
        waitForRelease = false;
        results = false;
      }
    }
  }
  return results;
}
