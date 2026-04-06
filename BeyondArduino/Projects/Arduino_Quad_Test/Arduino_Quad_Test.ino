/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

#define Ap  7
#define Bp  8

#define isA 0b10
#define isB 0b01

#define STEP_TIME 200
#define MAX_STEPS 20

// AB patterns
char pattern[] = {0b00, 0b01, 0b11, 0b10};
char step = 0;
int steps = 0;
bool direction = true;      // true:Forward .. false:Reverse

uint32_t waitTime = 0;

void setup() {
  // initialize digital pins as outputs.
  pinMode(Ap, OUTPUT);
  pinMode(Bp, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if( waitTime < millis() ) {
    waitTime = millis() + STEP_TIME;
    digitalWrite(Ap, (pattern[step] & isA) );
    digitalWrite(Bp, (pattern[step] & isB) );

    // Step though quad pattern.
    if(direction) {
      if( ++step > 3 ) {
        step = 0;
      }
    } else {
      if( --step < 0 ) {
        step = 3;
      }
    }

    // Change directions after MAX_STEPS
    if( ++steps > MAX_STEPS ) {
      steps = 0;
      direction = !direction;
    }
  }  
}
