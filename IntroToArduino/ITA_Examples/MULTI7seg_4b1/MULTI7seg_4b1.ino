/*
  Control mulltiple 7-segment LED displays using hardware registers.

  ref1: https://docs.arduino.cc/hardware/ - Technical Specs of your board
  ref2: https://docs.arduino.cc/retired/hacking/software/PortManipulation/ - Hardware control

  This code is for section 4b1 of the Introduction to Aduino - Student Handout.
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

#define DIG_3  8     // Digit 3 control line. |8| |9| |10|
#define DIG_2  9     // Digit 2 control line.
#define DIG_1  10    // Digit 1 control line.

// Put DIG defines into a array to allow indexing.
const char digits[] = {DIG_1, DIG_2, DIG_3};

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
  //abcdefgdp
  0b11111100,     // 0
  0b01100000,     // 1
  0b11011010,     // 2
  0b11110010,     // 3
  0b01100110,     // 4
  0b10110110,     // 5
  0b00111110,     // 6
  0b11100000,     // 7
  0b11111110 ,    // 8
  0b11100110,     // 9
  0b11101110,     // A
  0b00111110,     // b
  0b10011100,     // C
  0b01111010,     // d
  0b10011110,     // E
  0b10001110,     // F
  0b00000010      // -
};

// the setup function runs once when you press reset or power the board.
// All initialization should be done in this section.
void setup() {
  // initialize digital pins for the LEDs as outputs. 
  // see Help > Reference > Digital I/O for this information about this and other commands.
  DDRD = 0xFF;         // set all PORTD pins to OUTPUT.

  pinMode(DIG_1, OUTPUT);   // Display digits
  pinMode(DIG_2, OUTPUT);
  pinMode(DIG_3, OUTPUT);
}

void loop() {
  static char index = 0;
  static char digit = 0;
  static uint32_t waitTime = 0;

  if( waitTime < millis()) {
    waitTime = millis() + WAIT_DELAY;
    updateDisplay(index, digit);    // update the value and digit it is displayed on.

    // cycle though the digits
    if( ++digit > 2 ) {
      digit = 0;
      // Adjust the index to select the next characer. Reset to 0 if at the end of the table.
      ++index;                       // increment the index by 1
      if(index >= 11) {
        index = 0;
        waitTime = waitTime + WAIT_DELAY;    // wait a bit more after each series.
      }
    }
  }

  // sizeof() returns the number of bytes in the array.
  // The index can not be greater than the size of the array-1 or an 'index error' will occur.
}


void updateDisplay(char value, char digit) {
  char pattern = 0;

  if( value < 10) {
    digitalWrite(digits[digit], HIGH);

    // Display the selected character
    pattern = characters[value];
    // If a Decimal Point is needed. OR 0x01 to pattern.
    PORTD = pattern;
  }
  else
  {
    digitalWrite(digit, LOW);
  }
}
