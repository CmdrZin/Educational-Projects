/*
 * Switch 5b2 - Reading a Dynamic Switch - Used for counting.
 */

#define PUSH_SWITCH  11            // push button switch is connected to pin 11

bool waitForClose;
bool waitForOpen;

int countCloses = 0;
int countOpens = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PUSH_SWITCH, INPUT_PULLUP);  // use pin 11 as a INPUT. Activate internal pullup resistor.
  pinMode(13, OUTPUT);            // configure to use on-board LED.
  waitForClose = true;
  waitForOpen = false;
}

// put your main code here, to run repeatedly:
void loop() {
  if( isSwitchClosed() == true ) {
    if( waitForClose ) {
      waitForClose = false;
      waitForOpen = true;
      digitalWrite(13, HIGH);       // Turn ON LED.
      ++countCloses;
      Serial.print(countCloses);
    }
  } else {
    if( waitForOpen ) {
      waitForOpen = false;
      waitForClose = true;
      digitalWrite(13, LOW);        // Turn OFF LED.
      ++countOpens;
      Serial.println(countOpens);
    }
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
