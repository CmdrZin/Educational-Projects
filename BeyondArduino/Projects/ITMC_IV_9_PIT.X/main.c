/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on February 24, 2026, 12:20 PM
 */


#include <avr/io.h>

#include "io_ctrl.h"
#include "systime.h"

#define WAIT_DELAY 500


int main(void) {
    uint32_t    waitTime = 0;
    
    init_io();
    init_systime();
    
    // Indicate a RESET.
    flash_LED();
    flash_LED();
    
    sei();

    while (1) {
        if (waitTime < millis()) {
            waitTime = millis() + WAIT_DELAY;
            
            toggle_LED();
        }
    }
}
