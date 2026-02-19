/*
 * File:   systime.c
 * Author: Cmdrzin
 *
 * Created on February 18, 2026
 * 
 * This module uses TCB to generate a 1ms tic for the millis() function.
 */

#include <avr/io.h>
#include "systime.h"

volatile static uint32_t totalMilliseconds;	// local variable

#if 0
/* TCA interrupt service routine. */
ISR(TCA0_OVF_vect)
{
   	++totalMilliseconds;
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;   // clear the interrupt flag
}
#else
/* TCB interrupt service routine. */
ISR(TCB0_INT_vect)
{
   	++totalMilliseconds;
    TCB0.INTFLAGS = TCB_CAPT_bm;   // clear the interrupt flag
}
#endif
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

#if 0
/* *** TCA Configuration as NORMAL counter with interrupt for 1ms OVF *** */
void init_systime(void)
{
	TCA0_SINGLE_PER = 0x0D04;       // 3,333 - 1 since the counter starts at 0.
   	/* enable overflow interrupt */
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	/* set Normal mode */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc  /* set CLK_PER/64) */
					| TCA_SINGLE_ENABLE_bm; 	/* start timer */

}
#else
/* *** TCB Configuration as NORMAL counter with interrupt for 1ms OVF *** */
void init_systime(void)
{
    // The CCMP register contains the TOP value of the counter.
    TCB0.CCMP = 0x0D04;       // 3,333 - 1 since the counter starts at 0.
    /* enable periodic interrupt interrupt */
    TCB0.INTCTRL = TCB_CAPT_bm;
    /* set mode */
    // TCB0.CTRLB = (default, mode is periodic interrupt.)
    // TCB0.CTRLA = (default, use CLK_PER 3.333 MHz)
    TCB0.CTRLA |= TCB_ENABLE_bm;
}
#endif
