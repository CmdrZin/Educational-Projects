/*
 * File:   main04.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "serialPoll.h"             // USART support

#define LED_DELAY		200UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;
    char data = 'A';

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    USART0_init(9600);          // set up USART for Async 8N1 @ 9600
    
    /* enable Global interrupts */
    sei();
   
    // Toggle the LED and output a letter code.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            /* toggle the LED state. */
            toggle_LED();
            
            /* Send an ASCII character out. */
            USART0_sendChar(data);
            if (++data > 'Z')
            {
                USART0_sendChar(0x0D);  // CR
                USART0_sendChar(0x0A);  // LF
                data = 'A';
            }
		}
    }
}
