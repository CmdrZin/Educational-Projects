/*
 * File:   main.c
 * Author: CmdrZin
 *
 * Created on September 18, 2024, 3:12 PM
 * 
 * Target: ATtiny1614 .. should work with all AVR Series-1 devices.
 * RGB SK6812 RGB LED string control demo
 */

#include <avr/io.h>
#include "systime.h"
#include "rgb.h"

#define WAIT_DELAY  1000          // n * ms
#define LED_DELAY   200

int main(void) {
    uint32_t    waitTime = 0L;
    uint32_t    ledTime = 0L;
    uint8_t     pattern = 0;
    
    init_systime();
    init_rgb();             // Modifies CLK
    
    sei();
    
    PORTA.DIR |= PIN3_bm;           // Set PORTA PA3 as OUTPUT        
    PORTA.DIR |= PIN7_bm;           // DEBUG..Heartbeat status


    /* Replace with your application code */
    while (1) {
        if(millis() > ledTime) {
            ledTime = millis() + LED_DELAY;
            // DEBUG
            PORTA.OUTTGL |= PIN7_bm;
        }

        if(millis() > waitTime) {
            waitTime = millis() + WAIT_DELAY;
            display(0);     // outPattern1[]
            cycle();
        }
    }
}
