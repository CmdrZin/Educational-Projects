/*
  Blink 6 LEDs, one at a time.

  Turns each LED on for one tenth of a second, then off for one tenth of second.
  One tenth of a second is 100ms (100 milliseconds)

  ref1: https://docs.arduino.cc/hardware/ - Technical Specs of your board

  This code is for section 3a1 of the Introduction to Aduino - Student Handout.
*/

// To make code more human readable. The #define is used to match a name with a value.
// Give each pin connected to an LED a unique name for easy reference.
#define LED1  2     // LED 1 is connected to digital pin 2
#define LED2  3
#define LED3  4
#define LED4  5
#define LED5  6
#define LED6  7     // LED 6 is connected to digital pin 7

// the setup function runs once when you press reset or power the board.
// All initialization should be done in this section.
void setup() {
  // initialize digital pins for the LEDs as an outputs. 
  // see Help > Reference > Digital I/O for this information about this and other commands.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
}

// The loop function runs over and over again forever.
// It returns to the Arduino OS which then calls loop() again.
// Therefore, the loop() function must always return to allow other Arduino processes to run.
// This is an example of 'straight-line' coding.
// It is simple and easy understand and therefore easier to debug.
void loop() {
  // Blink LED1
  digitalWrite(LED1, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED1, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second
  // Blink LED2
  digitalWrite(LED2, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED2, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second
  // Blink LED3
  digitalWrite(LED3, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED3, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second
  // Blink LED4
  digitalWrite(LED4, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED4, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second
  // Blink LED5
  digitalWrite(LED5, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED5, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second
  // Blink LED6
  digitalWrite(LED6, HIGH);       // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED6, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                    // wait for a second
}
