/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "io_ctrl.h"

#define LED_RED_PIN_BM PIN3_bm      // RED LED
#define LED_YEL_PIN_BM PIN6_bm      // YELLOW LED
#define LED_GRN_PIN_BM PIN7_bm      // GREEN LED

/* *** Initialize the IO PORT *** */
void init_io(void){
    /* set LED pins of PORT A as OUTPUT pins. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= LED_RED_PIN_BM | LED_YEL_PIN_BM | LED_GRN_PIN_BM;
}

/* toggle the RED LEDs state. */
void toggle_LED()
{
    PORTA_OUTTGL = LED_RED_PIN_BM;
}

// control the LEDs as a group. Turn only one of them ON.
void set_leds(LED led)
{
    switch(led) {
        case LED_RED:
            PORTA.OUT &= ~(LED_YEL_PIN_BM | LED_GRN_PIN_BM);    // turn OFF
            PORTA.OUT |= LED_RED_PIN_BM;                        // turn ON
            break;
            
        case LED_YELLOW:
            PORTA.OUT &= ~(LED_RED_PIN_BM | LED_GRN_PIN_BM);    // turn OFF
            PORTA.OUT |= LED_YEL_PIN_BM;                        // turn ON
            break;
            
        case LED_GREEN:    
            PORTA.OUT &= ~(LED_RED_PIN_BM | LED_YEL_PIN_BM);    // turn OFF
            PORTA.OUT |= LED_GRN_PIN_BM;                        // turn ON
            break;
            
        default:
            PORTA.OUT &= ~(LED_RED_PIN_BM |
                    LED_YEL_PIN_BM | LED_GRN_PIN_BM);    // turn all OFF
            break;
    }
}
