/*
 * File:   main04.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts

/* TCA interrupt service routine. */
ISR(TCA0_OVF_vect)
{
    /* toggle the LED state. */
    PORTA_OUTTGL = PIN7_bm;
    /* The interrupt flag has to be cleared manually */
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void) {
	/* set PA7 of PORT A as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= PIN7_bm;

    /* *** TCA Configuration as NORMAL counter with interrupt *** */
   	/* enable overflow interrupt */
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

	/* set Normal mode */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc  /* set CLK_PER/64) */
					| TCA_SINGLE_ENABLE_bm; 	/* start timer */

    /* enable Global interrupts */
    sei();
    
    // Blink the LED at a rate set by the TCA overflow rate.
    while (1) {
        ;       // LED control is handled by the interrupt service.
    }
}
