/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 * 
 * Target: ATtinyt412 8SOIC
 * 
 * Section III.8 - RTC
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "sysdefs.h"
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "rtc.h"

#define LED_DELAY		500UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_rtc();
    
    /* enable Global interrupts */
    sei();
   
    // Read voltage. Set LED based on value.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
//            toggle_LED();
            // LED is now toggled by the RTC interrupt.
		}
    }
}
