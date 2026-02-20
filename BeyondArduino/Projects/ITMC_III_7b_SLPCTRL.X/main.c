/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on February 19, 2026
 * 
 * Example code for using the SLRCTRL (SLEEP) function.
 * ref: ATtiny212-214-412-414-416-DataSheet-DS40002287A.pdf
 */


#include <avr/io.h>

#include "sysdefs.h"
#include "io_ctrl.h"
#include "systime.h"

int main(void) {
    int cycleCounter = 0;
    uint32_t waitTime = 0;
    
    init_io();                 // set up IO pins.
    init_systime();
    
    sei();
    
    // Initialize Sleep Control for Power-Down mode.       PDOWN | SEN
    SLPCTRL.CTRLA = SLPCTRL_SMODE_1_bm | SLPCTRL_SEN_bm;

    while(1) {
        if (++cycleCounter > 10) {
            cycleCounter = 1;
        }

        for (int k = 0; k < cycleCounter; k++) {
            flash_LED();
        }
        
        // wait for switch to be released. Get's rid of 'switch bounce'.
        while (isSwitchPressed());
        waitTime = millis() + 20;       // wait after release.
        while(waitTime < millis());

        enablePA1();                    // interrupt disabled it.
                                        // IF switch bounce causes interrupt here, will lock up system.
                                        // SO, a GOOD reason to use a WDT!
        asm("SLEEP");           // will wake up on PORT interrupt.
    }
}
