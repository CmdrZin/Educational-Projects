/*
 * File:   main03.c
 * Author: Cmdrzin
 *
 * Created on August 5, 2024
 */


#include <avr/io.h>

int main(void) {
	/* set PA7 of PORT A as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= PIN7_bm;

    /* *** TCA Configuration as NORMAL counter *** */
	/* set Normal mode */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc  /* set CLK_PER/64) */
					| TCA_SINGLE_ENABLE_bm; 	/* start timer */

    // Blink the LED at a rate set by the TCA overflow rate.
    while (1) {
        /* Test for overflow */
        if( TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm) {
            /* reset the flag */
           	/* The OVF flag has to be cleared manually */
        	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
            /* and toggle the LED state. */
            PORTA_OUTTGL = PIN7_bm;
        }
    }
}
