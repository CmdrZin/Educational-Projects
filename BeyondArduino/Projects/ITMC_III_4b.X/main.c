/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on October 30, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include "systime.h"                // access systime functions.
#include "io_ctrl.h"
#include "spi_client.h"

#define LED_DELAY		1000UL		// N * 1ms

int main(void) {
    uint8_t val = 0;
    uint32_t td = 0;

    init_systime(); // set up TCA0 timer.
    init_io(); // set up IO pins.
    init_spi();
    
    sei();

    // RESET detection
    for (int i=0; i<6; i++) {
        while( millis() < td );     // DELAY
        td = millis() + 500;
        toggle_LED();
    }
    
    while (1) {
        if (isSpiData()) {
            val = getSpiData();         // clears flag.
            if (val == 'A') {
                set_LED(true);
            }
            if (val == 'B') {
                set_LED(false);
            }
        }
    }
}
