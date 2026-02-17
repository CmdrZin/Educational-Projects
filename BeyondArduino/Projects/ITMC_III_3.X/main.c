/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 * 
 * DAC with ADC example.
 */


#include <avr/io.h>
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "dac.h"

#define LED_DELAY		1000UL		// N * 1ms
#define SAMPLE_DELAY    10UL

int main(void) {
   	uint32_t ledTime = 0UL;
   	uint32_t sampleTime = 0UL;
    uint8_t count = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_dac();                 // set up DAC
            
    /* enable Global interrupts */
    sei();
   
    // Generate a sawtooth wave with a simple counter to set DAC voltage.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            toggle_LED();
        }
            
		if( millis() > sampleTime ) {
			sampleTime = millis() + SAMPLE_DELAY;
            /* update count. Allow to roll-over. */
            ++count;
            /* update DAC value */
            set_dac_output(count);
        }
    }
}
