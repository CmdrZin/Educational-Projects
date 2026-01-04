/*
 * File:   main04.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts

#define LED_DELAY		1000UL		// N * 1ms

volatile static uint32_t totalMilliseconds;	// global variable

uint32_t millis();                  // prototype for function

/* TCA interrupt service routine. */
ISR(TCA0_OVF_vect)
{
   	++totalMilliseconds;
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;   // clear the interrupt flag
}

/* Return the total number of milliseconds since the project started. */
uint32_t millis()
{
	uint32_t temp;			// make a holder for the counter.

	cli();				// Turn OFF interrupts to avoid corruption
						// during a multi-byte read.
	temp = totalMilliseconds;	// get a copy while interrupts are disabled.
	sei();				// Turn interrupts back ON.

	return temp;			// return a 'clean' copy of the counter.
}

int main(void) {
   	uint32_t ledTime = 0UL;

	/* set PA7 of PORT A as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= PIN7_bm;

    /* *** TCA Configuration as NORMAL counter with interrupt for 1ms OVF *** */
	TCA0_SINGLE_PER = 0x0D04;       // 3,333 - 1 since the counter starts at 0.
   	/* enable overflow interrupt */
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	/* set Normal mode */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc  /* set CLK_PER/64) */
					| TCA_SINGLE_ENABLE_bm; 	/* start timer */

    /* enable Global interrupts */
    sei();
   
    // Blink the LED at a rate set by the TCA overflow rate.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            /* toggle the LED state. */
            PORTA_OUTTGL = PIN7_bm;
		}
    }
}
