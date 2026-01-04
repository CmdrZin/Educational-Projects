/*
 * File:   main04.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.

#define LED_DELAY		1000UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;

    init_systime();     // set up TCA0 timer.

    init_io();          // set up IO pins. MUST MATCH THE DEVICE BEING USED!
    
    /* enable Global interrupts */
    sei();
   
    // Toggle the LED at a 1s rate.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            /* toggle the LED state. */
            PORTA_OUTTGL = PIN7_bm;     // MUST MATCH THE DEVICE BEING USED!
		}
    }
}
