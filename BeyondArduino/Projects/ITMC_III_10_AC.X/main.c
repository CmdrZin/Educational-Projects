/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on October 30, 2024
 * 
 * This is example code for Section III-10 on the Analog Comparator.
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "ac.h"

#define LED_DELAY		1000UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_ac();                  // set up AC for single ended compare.
    
    /* enable Global interrupts */
    sei();
   
    // Send out voltage, in HEX, each second.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            /* toggle the LED state. */
            toggle_LED();
        }
            
        /* continously test the input voltage. */
        if( check_ac() ) {
            setRedState(true);
            setGreenState(false);
        } else {
            setRedState(false);
            setGreenState(true);
        }
    }
}
