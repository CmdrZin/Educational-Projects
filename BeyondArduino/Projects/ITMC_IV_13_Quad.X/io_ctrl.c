/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "io_ctrl.h"

#define LED_REV_BM PIN6_bm      // Reverse
#define LED_FWD_BM PIN7_bm      // Forward
#define LED_CNT_BM PIN2_bm      // Count blink

/* *** Initialize the IO PORT *** */
// PIN SETTINGS MUST MATCH DEVICE USED!

void init_io(void){
    /* set pins of PORTx as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= LED_REV_BM | LED_FWD_BM;
    PORTB.DIR |= LED_CNT_BM;
}

/* toggle the LED state. */
void toggle_LED()
{
//    PORTA_OUTTGL = LED_PIN_BM;
}

void setFWD(bool state)
{
    if(state) {
        PORTA.OUTSET = LED_FWD_BM;
    } else {
        PORTA.OUTCLR = LED_FWD_BM;
    }
}

void setREV(bool state)
{
    if(state) {
        PORTA.OUTSET = LED_REV_BM;
    } else {
        PORTA.OUTCLR = LED_REV_BM;
    }
}

void toggleCNT()
{
    PORTB.OUTTGL = LED_CNT_BM;
}