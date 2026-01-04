/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "io_ctrl.h"

#define LED_RED_PIN_BM PIN7_bm      // RED LED

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

void setLED(bool state)
{
    if(state) {
        PORTA_OUT |= LED_RED_PIN_BM;
    } else {
        PORTA_OUT &= ~LED_RED_PIN_BM;
    }
}
// +++ DEBUG SUPPORT +++
/*
 * Pulse LED ON n times.
 */
void pulseLED(uint8_t val)
{
	for(uint8_t i=0; i<val; ++i)
	{
		setLED(true);
		asm("nop");
		asm("nop");
		asm("nop");
		setLED(false);
		asm("nop");
		asm("nop");
		asm("nop");
	}
}
