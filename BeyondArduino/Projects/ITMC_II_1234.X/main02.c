/*
 * File:   main02.c
 * Author: Cmdrzin
 *
 * Created on July 31, 2024, 11:03 PM
 * 
 * Connect an LED and resistor to PA7.
 * Use PA1 as an INPUT with it's PULL-UP resistor activated to sense a switch.
 */

#include <avr/io.h>

int main(void) {
    uint8_t portA_pins = 0;

	/* set PA7 of PORT A as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= PIN7_bm;
    
    /* enable the internal Pull-up resistor for PORTA pin 1 */
    PORTA.PIN1CTRL |= (1<<3);   // shift the '1' into the bit3 position.

    // Control the LED with the push button switch.
    while (1) {
        portA_pins = PORTA.IN;          // read all the pins of PORTA.
        portA_pins &= PIN1_bm;          // set all bits except bit.1 to '0'.
        if( portA_pins == 0 ) {
            /* turn ON the LED if bit.1 (pin1) is LOW (i.e. switch is closed) */
            PORTA_OUTSET = PIN7_bm;
        } else {
            /* turn OFF the LED if pin1 is HIGH (i.e. switch is open) */
            PORTA_OUTCLR = PIN7_bm;
        }
    }
}
