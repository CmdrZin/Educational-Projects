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
#include "adc.h"

#define LED_DELAY		1000UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;
    char data = 'A';
    uint8_t voltage = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    USART0_init(9600);          // set up USART for Aync 8N1 @ 9600
    init_adc();                 // set up ADC for 8-bit results and manual sampling.
    
    /* enable Global interrupts */
    sei();
   
    // Send out voltage, in HEX, each second.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            /* toggle the LED state. */
            toggle_LED();
            
            /* sample the input voltage. */
            trigger_adc();
            /* wait for conversion to complete and return voltage. */
            voltage = read_adc();
                       
            /* Send an voltage out as ASCII HEX characters. */
            data = (voltage >> 4) + '0';
            USART0_sendChar(data);
            data = (voltage & 0x0F) + '0';
            USART0_sendChar(data);

            USART0_sendChar(0x0D);  // CR
            USART0_sendChar(0x0A);  // LF
		}
    }
}
