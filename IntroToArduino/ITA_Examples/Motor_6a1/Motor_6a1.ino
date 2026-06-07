/*
 * Motor_6a1 - Simplr motor control
 * June 6, 2026
 * D5 - PWM output
 *
 * Single NPN transistor: Should be rated at twice the maximum current draw of the motor.
 *                        This is typically the 'stall' current rating of the motor.
 * A TO-220 package is a good choice. A TO-92 package may not be able to dissapate enough heat.
 * An NPN Darlington pair is also a good choice.
 */

#define MOTOR 3

bool oneTime;

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);

  oneTime = true;
}

void loop() {
  if(oneTime) {
    oneTime = false;          // speed only has to set once.
    // The analogWrite() will generate a PWM signal propotional to the value.
    analogWrite(MOTOR, 250);
  } 
}
