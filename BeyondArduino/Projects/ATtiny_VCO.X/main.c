/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on September 22, 2024
a * 
 * ADC + DAC to form a Voltage Controlled Oscillator(VC))
 * using Digital Signal Synthesis (DDS).
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "adc.h"
#include "dac.h"
#include "dds.h"

#define LED_DELAY		1000UL		// N * 1ms
#define SAMPLE_DELAY    10UL

int main(void) {
   	uint32_t ledTime = 0UL;
   	uint32_t sampleTime = 0UL;
    uint8_t voltage = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_adc();                 // set up ADC for 8-bit results and manual sampling.
    init_dac();                 // set up DAC
    init_dds();
            
    /* enable Global interrupts */
    sei();
   
    setFrequency(0x00E8);

    // Sample the ADC and copy its value to the DAC to send out voltage.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            toggle_LED();
        }
        
		if( millis() > sampleTime ) {
			sampleTime = millis() + SAMPLE_DELAY;
            /* sample the input voltage. */
            trigger_adc();
            /* wait for conversion to complete and return voltage. */
            voltage = read_adc();
            /* update Frequency */
            setFrequency(voltage);
        }
    }
}
