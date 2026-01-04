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
#include "adc.h"

#define LED_DELAY		100UL		// N * 1ms

int main(void) {
   	uint32_t ledTime = 0UL;
    uint8_t voltage = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_adc();                 // set up ADC for 8-bit results and manual sampling.
    
    /* enable Global interrupts */
    sei();
   
    // Read voltage. Set LED based on value.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            
            /* sample the input voltage. */
            trigger_adc();
            /* wait for conversion to complete and return voltage. */
            voltage = read_adc();
                       
            /* Light the LED that indicates the range of the voltage. */
            if (voltage < 0x80) {
                set_leds(LED_GREEN);
            } else if ((voltage >= 0x80) && (voltage < 0xC0)) {
                set_leds(LED_YELLOW);
            } else if (voltage >= 0xC0) {
                set_leds(LED_RED);
            }
		}
    }
}
