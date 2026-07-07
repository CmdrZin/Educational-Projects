/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on July 6, 2026
 * 
 * Complex Input Switch example Section IV-3.2.2
 * Checks for bounce on press and release. Useful when counting switch changes.
 * Connect a switch to PA1 configured as a INPUT with PULL-UP enabled.
 * Connect an LED with resistor to PA7 configured as an OUTPUT.
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "systime.h"                // access systime functions.

#define BOUNCE_DELAY		10UL	// N * 1ms. Some poor switches may need large delays.

typedef enum {SW_IDLE, SW_PRESSED, SW_P_DB, SW_RELEASED} SW_STATE;

bool isSwitchClosed();

int main(void) {
    
    PORTA.DIR |= PIN7_bm;        // set PA7 to OUTPUT
    PORTA.PIN1CTRL |= (1<<3);    // enable PULL-UP for PA1  

    init_systime();             // set up TCA0 timer for millis().
    
    /* enable Global interrupts */
    sei();
   
    while (1) {
        if( isSwitchClosed() == true ) {
            PORTA.OUT |= PIN7_bm;          // Turn ON LED.
        } else {
            PORTA.OUT &= ~PIN7_bm;         // Turn OFF LED.
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

  bool results = false;                         // default value

  switch(sw_state) {
    case SW_IDLE:
      // test if the switch has been closed.
      if( (PORTA.IN & PIN1_bm) == 0 ) {   // if switch is pressed
        bounceDelay = millis() + BOUNCE_DELAY;            // start release wait.
        results = true;
        sw_state = SW_PRESSED;
      }
      break;

    case SW_PRESSED:
      // check for pressed time
      if( (PORTA.IN & PIN1_bm) == 0 ) {  // if switch is still pressed
        if( bounceDelay > millis() ) {          // check delay
          sw_state = SW_P_DB;                   // past 10ms. go to wait for release
        }
      } else {
        // bounced HIGH
        bounceDelay = millis() + BOUNCE_DELAY;            // restart release wait.
      }
      results = true;                           // not a confirmed release yet. So, treat as pressed.
      break;

    case SW_P_DB:
      if( (PORTA.IN & PIN1_bm) == PIN1_bm ) {  // if switch released
          bounceDelay = millis() + BOUNCE_DELAY;          // start release wait.
          sw_state = SW_RELEASED;
      }
      results = true;                           // not a confirmed release yet. So, treat as pressed.
      break;
      
    case SW_RELEASED:
      if( (PORTA.IN & PIN1_bm) == 0 ) {   // if switch bounced
          bounceDelay = millis() + BOUNCE_DELAY;          // restart release wait.
          results = true;                       // not a confirmed release yet. So, treat as pressed.
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
