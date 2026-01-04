/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on September 13, 2024
 * TWI (I2C) Slave example
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "adc.h"
#include "twiRegSlave.h"
#include "wdt.h"

#define LED_DELAY		500UL		// N * 1ms
#define TWI_DELAY		1000UL      // update TWI slave data
#define SLAVE_ADRS		0x50

volatile uint8_t rxRegister[16];
volatile uint8_t txRegister[16];

int main(void) {
   	uint32_t ledTime = 0UL;
	uint32_t twiTime = 0UL;
    uint8_t voltage = 0;

    init_systime();             // set up TCA0 timer.
    init_io();                  // set up IO pins.
    init_adc();                 // set up ADC for 8-bit results and manual sampling.
   	twiRegSlaveInit(SLAVE_ADRS, rxRegister, 16, txRegister, 16);
    init_wdt();
    
    /* enable Global interrupts */
    sei();
   
    // Read voltage. Set register 1 based on value.
    while (1) {
        resetWDT();
        
        // Heartbeat
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            toggle_LED();
            resetWDT();
        }
            
		if( millis() > ledTime ) {
			twiTime = millis() + TWI_DELAY;
            
            /* sample the input voltage. */
            trigger_adc();
            /* wait for conversion to complete and return voltage. */
            voltage = read_adc();

            // update data register 1.
    		twiSetRegister(1, voltage);
		}
    }
}
