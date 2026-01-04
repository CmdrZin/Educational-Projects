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
    uint32_t ledTime = 0UL;
    uint8_t val = 0;

    init_systime(); // set up TCA0 timer.
    init_io(); // set up IO pins.
    init_spi();

    while (1) {
        if (millis() > ledTime) {
            ledTime = millis() + LED_DELAY;
            //toggle_LED();
        }

        if (isSpiData()) {
            val = getSpiData();
            if (val == 'A') {
                set_LED(true);
            }
            if (val == 'B') {
                set_LED(false);
            }
        }
    }
}
