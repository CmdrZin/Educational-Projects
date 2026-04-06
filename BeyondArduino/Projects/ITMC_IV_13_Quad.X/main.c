/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on March 24, 2026
 * 
 * main() for ITMC_IV_13_Quad project.
 * 
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "quad.h"

#define LED_DELAY		200UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;
    int distance = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_quad();
    
    /* enable Global interrupts */
    sei();
    setFWD(true);
    setREV(true);
    toggleCNT();
   
    // Toggle the LED as heartbeat.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            /* toggle the LED state. */
//            toggle_LED();
		}
        
        if( getPosition() != distance ) {
            distance = getPosition();
            toggleCNT();
            if( getDirection() == D_CW ) {
                setREV(false);
                setFWD(true);
            } else {
                setREV(true);
                setFWD(false);
            }
        }
    }
}
