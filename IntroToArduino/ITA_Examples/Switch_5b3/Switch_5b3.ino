/*
 * Switch 5b3 - Reading a Dynamic Switch - Complex. Using a State Machine to debounce both press and release.
 * Demonstraights that a debounce may be needed for release as well as press.
 */

#define PUSH_SWITCH  11             // push button switch is connected to pin 11

#define BOUNCE_DELAY  100           // some cheap switches have really bad switch bounce.

typedef enum {SW_IDLE, SW_PRESSED, SW_P_DB, SW_RELEASED} SW_STATE;

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
 * Use a State Machine to evaluate the switch.
 * Doesn't have to be pressed for 10ms, but does have to be released for 10ms.
 */
bool isSwitchClosed()
{
  static unsigned long bounceDelay;
  static SW_STATE sw_state = SW_IDLE;

  static bool timingLow = false;
  static bool waitForHigh = false;
  bool results = false;                         // default value

  switch(sw_state) {
    case SW_IDLE:
      // test if the switch has been closed.
      if( digitalRead(PUSH_SWITCH) == LOW ) {   // if switch is pressed
        bounceDelay = millis() + BOUNCE_DELAY;            // start release wait.
        results = true;
        sw_state = SW_PRESSED;
      }
      break;

    case SW_PRESSED:
      // check for pressed time
      if( digitalRead(PUSH_SWITCH) == LOW ) {  // if switch is still pressed
        if( bounceDelay > millis() ) {          // check delay
          sw_state = SW_P_DB;                   // past 10ms. go to wait for release
        }
      } else {
        // bounced HIGH
        bounceDelay = millis() + BOUNCE_DELAY;            // restart release wait.
      }
      results = true;                           // not a comfermed release yet. So, treat as pressed.
      break;

    case SW_P_DB:
      if( digitalRead(PUSH_SWITCH) == HIGH ) {  // if switch released
          bounceDelay = millis() + BOUNCE_DELAY;          // start release wait.
          sw_state = SW_RELEASED;
      }
      results = true;                           // not a comfermed release yet. So, treat as pressed.
      break;
      
    case SW_RELEASED:
      if( digitalRead(PUSH_SWITCH) == LOW ) {   // if switch bounced
          bounceDelay = millis() + BOUNCE_DELAY;          // restart release wait.
          results = true;                       // not a comfermed release yet. So, treat as pressed.
      } else {
        if( bounceDelay > millis() ) {
          sw_state = SW_IDLE;                   // released for 10ms. So, treat as released. (return false)
        }
      }
      break;
 
    default:
      sw_state = SW_IDLE;
      break;
  }

  return results;
}
