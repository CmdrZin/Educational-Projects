/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "io_ctrl.h"

#define LED_PIN_BM PIN3_bm

/* *** Initialize the IO PORT *** */
void init_io(void){
    /* set PA7 of PORT A as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= LED_PIN_BM;
}

/* toggle the LED state. */
void toggle_LED()
{
    PORTA_OUTTGL = LED_PIN_BM;
}
