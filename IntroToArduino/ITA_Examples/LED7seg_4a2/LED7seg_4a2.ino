/*
  Control a 7-segment LED display using hardware registers.

  ref1: https://docs.arduino.cc/hardware/ - Technical Specs of your board
  ref2: https://docs.arduino.cc/retired/hacking/software/PortManipulation/ - Hardware control

  This code is for section 4a2 of the Introduction to Aduino - Student Handout.
*/

// To make code more human readable. The #define is used to match a name with a value.

#define WAIT_DELAY 500

// Give each pin connected to an LED a unique name for easy reference.
#define seg_a 0     // segment a is connected to digital pin 0
#define seg_b 1
#define seg_c 2
#define seg_d 3
#define seg_e 4
#define seg_f 5
#define seg_g 6
#define seg_dp 7    // segment dp is connected to digital pin 7

#define DIG_1  8     // Digit control line.

/*
         a
       ----
     f|    |b
      |  g |
       ----
     e|    |c
      |  d |
       ----
 */
// Segment table..the format B00000000 can also be used
const char characters[] = {
  //.gfedcba
  0b00111111,     // 0
  0b00000110,     // 1
  0b01011011,     // 2
  0b01001111,     // 3
  0b01100110,     // 4
  0b01101101,     // 5
  0b01111100,     // 6
  0b00000111,     // 7
  0b01111111,     // 8
  0b01100111,     // 9
  0b01110111,     // A
  0b01111100,     // b
  0b00111001,     // C
  0b01011110,     // d
  0b01111001,     // E
  0b01110001,     // F
  0b01000000      // -
};

// the setup function runs once when you press reset or power the board.
// All initialization should be done in this section.
void setup() {
  // initialize digital pins for the LEDs as outputs. 
  // see Help > Reference > Digital I/O for this information about this and other commands.
  DDRD = 0xFF;         // set all PORTD pins to OUTPUT. [2]

  pinMode(DIG_1, OUTPUT);   // Display digits
}

void loop() {
  static char index = 0;
  static uint32_t waitTime = 0;

  if( waitTime < millis()) {
    waitTime = millis() + WAIT_DELAY;
    updateDisplay(index);    // update the value

    // Adjust the index to select the next characer. Reset to 0 if at the end of the table.
    ++index;                       // increment the index by 1
    if(index >= 18) {
      index = 0;
      waitTime = waitTime + WAIT_DELAY;    // wait a bit more after each series.
    }
  }

  // sizeof() returns the number of bytes in the array.
  // The index can not be greater than the size of the array-1 or an 'index error' will occur.
}


void updateDisplay(char value) {
  char pattern = 0;

  if( value < 17) {
    digitalWrite(DIG_1, HIGH);      // enable the display

    // Display the selected character
    pattern = characters[value];
    // If a Decimal Point is needed. OR 0x01 to pattern.
    PORTD = pattern;                // set port pins. [2]
  }
  else
  {
    digitalWrite(DIG_1, LOW);     // or disable the display
  }
}
