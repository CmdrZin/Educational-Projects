/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on October 30, 2024, 12:30 PM
 */

#include <avr/io.h>
#include "io_ctrl.h"

#define LED_RED_PIN_BM PIN1_bm
#define LED_GRN_PIN_BM PIN3_bm
#define LED_YEL_PIN_BM PIN6_bm

/* *** Initialize the IO PORT *** */
void init_io(void){
    /* set PA1, PA3, and PA6 of PORT A as an OUTPUT pins. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= LED_RED_PIN_BM | LED_GRN_PIN_BM | LED_YEL_PIN_BM;
}

/* toggle the LED state. */
void toggle_LED()
{
    PORTA_OUTTGL = LED_YEL_PIN_BM;
}

void setRedState(bool state)
{
    if(state) {
        PORTA_OUTSET = LED_RED_PIN_BM;
    } else {
        PORTA_OUTCLR = LED_RED_PIN_BM;
    }
}

void setGreenState(bool state)
{
    if(state) {
        PORTA_OUTSET = LED_GRN_PIN_BM;
    } else {
        PORTA_OUTCLR = LED_GRN_PIN_BM;
    }
}
