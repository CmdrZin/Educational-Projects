/*
  Blink 6 LEDs, one at a time.

  Turns each LED on for one tenth of a second, then off for one tenth of second.
  One tenth of a second is 100ms (100 milliseconds)

  ref1: https://docs.arduino.cc/hardware/ - Technical Specs of your board

  This code is for section 3a2 of the Introduction to Aduino - Student Handout.
*/

// To make code more human readable. The #define is used to match a name with a value.
// Give each pin connected to an LED a unique name for easy reference.
#define LED1  2     // LED 1 is connected to digital pin 2
#define LED2  3
#define LED3  4
#define LED4  5
#define LED5  6
#define LED6  7     // LED 6 is connected to digital pin 7

// This array stores the LED values to be used.
const char leds[] = {LED1, LED2, LED3, LED4, LED5, LED6};

// the setup function runs once when you press reset or power the board.
// All initialization should be done in this section.
void setup() {
  // initialize digital pins for the LEDs as an outputs. 
  // see Help > Reference > Digital I/O for this information about this and other commands.
  // Use the leds[] array and a for() control to repeat the same function for each LED.
  for( int i=0; i<sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
}

// The loop function runs over and over again forever.
// It returns to the Arduino OS which then calls loop() again.
// Therefore, the loop() function must always return to allow other Arduino processes to run.
// This is an example of using a indexed array as a value table.
// It uses less code and reuses code sections. This can help isolate bugs.
void loop() {
  static int index = 0;           // This value is static so it is retained after exiting the loop() function.

  // Select an LED. leds[0] is the first LED, leds[5] is the last LED.
  char led = leds[index];
  // Blink the selected LED
  digitalWrite(led, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                    // wait for a second
  digitalWrite(led, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second

  // Adjust the index to select the next LED. Reset to 0 if at the end of the table.
  ++index;                       // increment the index by 1
  if(index >= sizeof(leds)) {
    index = 0;
  }
  // sizeof() returns the number of bytes in the array.
  // The index can not be greater than the size of the array-1 or an 'index error' will occur.
}
