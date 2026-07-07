/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on July 6, 2026
 * 
 * Simple Input Switch example Section IV-3.2.1
 * Connect a switch to PA1 configured as a INPUT with PULL-UP enabled.
 * Connect an LED with resistor to PA7 configured as an OUTPUT.
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "systime.h"                // access systime functions.

#define DEBOUNCE_DELAY		10UL	// N * 1ms

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

// Simple switch input
bool isSwitchClosed()
{
    static unsigned long bounceDelay;
    static bool waitForRelease = false;
    bool results = false;                       // default value

    // Waiting for the switch to be pressed?
    if( (PORTA.IN & PIN1_bm) == 0 ) {           // switch is pressed
        bounceDelay = millis() + DEBOUNCE_DELAY;            // start wait for release 10ms.
        waitForRelease = true;
        results = true;                         // switch is pressed.
    } else {
        if( bounceDelay > millis() ) {          // wait for at least 10ms of switch not being pressed.
            if( (PORTA.IN & PIN1_bm) == 0 ) { // test the switch for bounce. (i.e. is it closed?)
                bounceDelay = millis() + DEBOUNCE_DELAY;        // reset delay. Switch bounced.
            } else {
                // still not pressed.
                waitForRelease = false;
                results = false;
            }
        }
    }
    return results;
}
