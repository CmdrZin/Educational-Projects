/*
 * Switch 5b2 - Reading a Dynamic Switch - Complex. Used if the switch being use to change a count.
 * Does not stay in reading function.
 */

#define PUSH_SWITCH  11            // push button switch is connected to pin 11

unsigned long bounceDelay;

void setup() {
  pinMode(PUSH_SWITCH, INPUT_PULLUP);  // use pin 11 as a INPUT. Activate internal pullup resistor.
  pinMode(13, OUTPUT);            // configure to use on-board LED.
  bounceDelay = 0;
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
 * Wait for switch to go HIGH before testing again.
 */
bool isSwitchClosed()
{
  static bool timingLow = false;
  static bool waitForHigh = false;
  bool results = false;                         // default value

  // Waiting for the switch to be released?
  if( !waitForHigh ) {
    if( timingLow ) {
      if( bounceDelay < millis() ) {
        timingLow = false;                        // bounce time past.
        waitForHigh = true;                       // don't test again until released.
      }
      results = true;                             // still pressed.
    } else {
      // normal test
      if( digitalRead(PUSH_SWITCH) == LOW ) {       // if switch is pressed
        bounceDelay = millis() + 10;                // set to wait 10ms.
        timingLow = true;
        results = true;                             // switch is closed.
      }
    }
  } else {
    // Yes. Test if released.
      if( digitalRead(PUSH_SWITCH) == HIGH ) {    // release. clear flag.
        waitForHigh = false;
      } else {
        results = true;                           // still pressed.
      }
  }

  return results;
}
