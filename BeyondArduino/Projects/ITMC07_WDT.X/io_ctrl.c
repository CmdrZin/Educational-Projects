/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 30, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "sysdefs.h"
#include "io_ctrl.h"

#define LED_PIN_BM PIN7_bm          // change as needed to match hardware.
#define BUTTON_PIN_BM PIN1_bm       // change as needed to match hardware.

/* *** Initialize the IO PORT *** */
void init_io(void){
    /* set PA7 of PORT A as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= LED_PIN_BM;
}

bool read_Switch()
{
    return(PORTA.IN & BUTTON_PIN_BM);
}

/* toggle the LED state. */
void toggle_LED(void)
{
    PORTA_OUTTGL = LED_PIN_BM;
}

void set_LED(bool state)
{
    if(state) {
        PORTA.OUT |= LED_PIN_BM;        // Turn ON LED.
    } else {
        PORTA.OUT &= ~(LED_PIN_BM);     // Turn OFF LED.
    }
}

void flash_LED(void)
{
    uint16_t counter = 0;
    
    set_LED(true);

    // Non-timer delay. Wait 65536 counts.
    ++counter;
    while(counter != 0) {
        ++counter;
    }
    set_LED(false);
}
