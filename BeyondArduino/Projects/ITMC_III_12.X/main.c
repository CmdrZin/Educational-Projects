/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on October 9, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include <avr/eeprom.h>

#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "serialPoll.h"

#define LED_DELAY		100UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;
    uint8_t val = 'A';
    uint8_t epval;
    int count = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    USART0_init(9600);          // set up USART for Async 8N1 @ 9600
    
    /* enable Global interrupts */
    sei();

    // Write 13 character into EEPROM, then read them all back and output to Serial.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            
            eeprom_write_byte((uint8_t *)count, val);     // avr/eeprom takes care of setting CCP and Write address register.
            ++count;

            if( ++val > 'Z' ) {
                val = 'A';
            }
		}
        
        if(count > 12) {
            for (int i=0; i<13; i++) {
                epval = eeprom_read_byte((uint8_t *)i);      // avr/eeprom lib ASSUMES 0x1400 as a base address.
                /* Send an ASCII character out. */
                USART0_sendChar(epval);
            }
            USART0_sendChar(0x0D);
            USART0_sendChar(0x0A);
            count = 0;
        }
    }
}
