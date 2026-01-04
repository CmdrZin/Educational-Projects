/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on July 31, 2024, 11:03 PM
 */


#include <avr/io.h>

int main(void) {
    uint16_t count = 0;
	/* set PA7 of PORT A as an output pin */
	PORTA.DIR |= PIN7_bm;

    // Toggle pin every 65536 counts.
    while (1) {
        if( count == 0) {
            PORTA_OUTTGL = PIN7_bm;
        }
        ++count;
    }
}
