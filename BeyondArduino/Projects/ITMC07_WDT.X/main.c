/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on August 30, 2024
 * 
 * Example code for using the Watchdog Timer(WDT)
 * ref: ATtiny212-214-412-414-416-DataSheet-DS40002287A.pdf
 */


#include <avr/io.h>
#include <avr/interrupt.h>     // to support the use of interrupts

#include "sysdefs.h"
#include "io_ctrl.h"

int active;                    // if 0xAA55, system is in Sleep process.
int cycleCounter;

int main(void) {

    init_io();                 // set up IO pins.
    flash_LED();               // indicate a RESET
    
    // Initialize Sleep Control for Power-Down mode.       PDOWN | SEN
    SLPCTRL.CTRLA = SLPCTRL_SMODE_1_bm | SLPCTRL_SEN_bm;
    // Initialize WDT for 8 sec timeout Normal mode.
    WDT.CTRLA = WDT_PERIOD_3_bm | WDT_PERIOD_1_bm | WDT_PERIOD_0_bm;

    if (active != 0xAA55) {
        active = 0xAA55;
        cycleCounter = 0;
        while( PORTA.IN & read_Switch() );   // wait for Push Button press.
    } else {
        ++cycleCounter;
        for (int k = 0; k < cycleCounter; k++) {
            flash_LED();
            // Non-timer delay. Wait 65536 counts.
            for (uint16_t i = 0; i < 0xFFFF; i++) {
                asm("NOP");
            }
        }
    }
    
    asm("SLEEP");
}
