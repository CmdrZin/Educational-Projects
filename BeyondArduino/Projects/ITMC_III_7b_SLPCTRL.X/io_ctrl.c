/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on February 19, 2026
 * 
 * This is an example of using a switch to wake up a device in SLEEP mode.
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
    /* enable the internal Pull-up resistor for PORTA pin 1 */
    // allow pin to wake up device while in SLEEP mode.
    PORTA.PIN1CTRL |= PORT_PULLUPEN_bm | PORT_ISC_LEVEL_gc;
    PORTA.INTFLAGS |= BUTTON_PIN_BM;         // clear flag
}

void enablePA1(void)
{
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm | PORT_ISC_LEVEL_gc;
}

void disablePA1(void)
{
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
}

ISR(PORTA_PORT_vect)
{
    disablePA1();
    // only PA1 used, so no tests needed. The interrupt wakes up the device.
    PORTA.INTFLAGS |= BUTTON_PIN_BM;         // clear flag
}

// Return true if BUTTON_PIN_BM is LOW.
bool isSwitchPressed()
{
    bool result = false;
    if ( (PORTA.IN & BUTTON_PIN_BM) == 0 ) {
        result = true;
    }
    return(result);
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

    // ON time. Non-timer delay. Wait 65536 counts.
    ++counter;
    while(counter != 0) {
        ++counter;
    }
    set_LED(false);
    // OFF time. Non-timer delay. Wait 65536 counts.
    ++counter;
    while(counter != 0) {
        ++counter;
    }
}
