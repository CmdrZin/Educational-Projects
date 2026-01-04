/*
 * File:   systime.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:29 PM
 * rev: May 8, 2025     adj for ATtiny1614 default clock speed.
 */


#include <avr/io.h>
#include "systime.h"

volatile static uint32_t totalMilliseconds;	// local variable

/* TCA interrupt service routine. */
ISR(TCA0_OVF_vect)
{
   	++totalMilliseconds;
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;   // clear the interrupt flag
}

/* Return the total number of milliseconds since the project started. */
uint32_t millis(void)
{
	uint32_t temp;			// make a holder for the counter.
    uint8_t sreg_save;
    
    // Save SREG, disable interrupts, do code, restore SREG.
    // If interrupts were enabled, they will be re-enabled.
    sreg_save = SREG;
    cli();
  	temp = totalMilliseconds;	// get a copy while interrupts are disabled.
    SREG = sreg_save;

	return temp;			// return a 'clean' copy of the counter.
}

/* *** TCA Configuration as NORMAL counter with interrupt for 1ms OVF *** */
void init_systime(void)
{
	TCA0_SINGLE_PER = 0x0D06;       // set for ATtiny1614 default clock
   	/* enable overflow interrupt */
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	/* set Normal mode */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc  /* set CLK_PER/64) */
					| TCA_SINGLE_ENABLE_bm; 	/* start timer */

}
