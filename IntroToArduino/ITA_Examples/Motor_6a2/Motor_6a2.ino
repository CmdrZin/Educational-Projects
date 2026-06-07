/*
 * Motor_6a1 - Simplr motor control
 * June 6, 2026
 * D3 - PWM output
 *
 * H-Bridge: TB6612 can easily control a toy motor down to about 10% PWM with no load.
 */

#define MOTOR 3
#define AN1   5
#define AN2   4

bool oneTime;

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);

  digitalWrite(AN1, LOW);
  digitalWrite(AN2, LOW);
  pinMode(AN1, OUTPUT);
  pinMode(AN2, OUTPUT);

  oneTime = true;
}

void loop() {
  if(oneTime) {
    oneTime = false;          // speed only has to set once.

    // Set direction to CW
    digitalWrite(AN1, HIGH);
    digitalWrite(AN2, LOW);
    // The analogWrite() will generate a PWM signal propotional to the value.
    analogWrite(MOTOR, 75);
  } 
}
