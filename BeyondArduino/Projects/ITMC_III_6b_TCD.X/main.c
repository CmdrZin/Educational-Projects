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
#include "tcd.h"

#define LED_DELAY		50UL		// N * 1ms

#define WOA_MIN     0x0400
#define WOA_MAX     0x0600
#define WOB_MIN     0x0C00
#define WOB_MAX     0x0E00

int main(void) {
   	uint32_t ledTime = 0UL;
    uint16_t woaCount = WOA_MIN;
    uint16_t wobCount = WOB_MAX;

    init_systime();             // set up TCA0 timer.
    init_TCD();
    
    /* enable Global interrupts */
    sei();
   
    // Read voltage. Set LED based on value.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            // Modify the ON time for WOA and WOB
            setTCD_setA(woaCount);
            if(++woaCount > WOA_MAX) {
                woaCount = WOA_MIN;
            }
            
            setTCD_setB(wobCount);
            if(--wobCount < WOB_MIN) {
                woaCount = WOA_MAX;
            }
            
		}
    }
}
