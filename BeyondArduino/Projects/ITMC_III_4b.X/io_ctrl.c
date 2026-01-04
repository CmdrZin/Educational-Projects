/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "io_ctrl.h"

#define LED_RED_PIN_BM PIN7_bm      // RED LED on PA7

/* *** Initialize the IO PORT *** */
void init_io(void){
    /* set LED pins of PORT A as OUTPUT pins. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= LED_RED_PIN_BM;
}

/* toggle the RED LEDs state. */
void toggle_LED()
{
    PORTA_OUTTGL = LED_RED_PIN_BM;
}

/* set the RED LEDs state. */
void set_LED(bool state)
{
    if(state) {
        PORTA_OUTSET = LED_RED_PIN_BM;
    } else {
        PORTA_OUTCLR = LED_RED_PIN_BM;
     }
}
