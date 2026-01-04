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
#include "spi.h"

#define LED_DELAY		1000UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;
    uint8_t val = 'A';

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_spi();                 // set up SPI as a Host.
    
    /* enable Global interrupts */
    sei();
   
    // Send out voltage, in HEX, each second.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            
            sendByte(val);
            if( ++val > 'Z' ) {
                val = 'A';
            }
		}
    }
}
