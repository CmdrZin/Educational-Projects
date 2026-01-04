/*
  Control a 7-segment LED display.



  ref1: https://docs.arduino.cc/hardware/ - Technical Specs of your board

  This code is for section 4a1 of the Introduction to Aduino - Student Handout.
*/

// To make code more human readable. The #define is used to match a name with a value.
// Give each pin connected to an LED a unique name for easy reference.
#define seg_a 0     // segment a is connected to digital pin 0
#define seg_b 1
#define seg_c 2
#define seg_d 3
#define seg_e 4
#define seg_f 5
#define seg_g 6
#define seg_dp 7    // segment dp is connected to digital pin 7

#define DIG_1  8     // Digit 1 control line.

// This array stores the segment pin values to be used.
const char leds[] = {seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g, seg_dp};

const char characters[][8] = {
  // seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g, seg_dp
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW},         // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW},      // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW},      // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW},       // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW},      // 5
  {LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},      // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW},        // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},    // 8
  {HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW},      // 9
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // A
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // B
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // C
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // D
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // E
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},     // F
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW}      // -
};

// the setup function runs once when you press reset or power the board.
// All initialization should be done in this section.
void setup() {
  // initialize digital pins for the LEDs as outputs. 
  // see Help > Reference > Digital I/O for this information about this and other commands.
  pinMode(seg_a, OUTPUT);
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_e, OUTPUT);
  pinMode(seg_f, OUTPUT);
  pinMode(seg_g, OUTPUT);
  pinMode(seg_dp, OUTPUT);

  pinMode(DIG_1, OUTPUT);
}

void loop() {
  static char index = 0;
  static uint32_t waitTime = 0;

  if( waitTime < millis()) {
    waitTime = millis() + 500;      // use #define WAIT_DELAY 500
    updateDisplay(index);
    // Adjust the index to select the next characer. Reset to 0 if at the end of the table.
    ++index;                       // increment the index by 1
    if(index >= 10) {
      index = 0;
      waitTime = waitTime + 500;    // wait a bit more after each series.
    }
  }

  // sizeof() returns the number of bytes in the array.
  // The index can not be greater than the size of the array-1 or an 'index error' will occur.
}


void updateDisplay(char value) {
  char digit[8];

  if( value < 10) {
    digitalWrite(DIG_1, HIGH);

    // Select the character. Copy pattern into digit[].
    for(int j=0; j<8; j++) {
      digit[j] = characters[value][j];
    }
    // If a Decimal Point is needed. Set digit[7] = HIGH.

    // Display the selected character
    for (int i=0; i<8; i++) {
      digitalWrite(leds[i], digit[i]);
    }
  }
}
