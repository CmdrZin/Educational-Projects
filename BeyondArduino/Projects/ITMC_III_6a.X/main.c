/*
 * File:   main04.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"

#define LED_DELAY		1000UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    
    /* enable Global interrupts */
    sei();
   
    // Send out voltage, in HEX, each second.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            toggle_LED();
		}
    }
}
