/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on May 18, 2025, 2:58 PM
 */


#include <avr/io.h>
#include <stdbool.h>

#include "system.h"
#include "rtc.h"
#include "mod_led.h"
#include "ddsDAC.h"

#define HB_WAIT 500

uint32_t lastTime = 0;

// Note Table
uint16_t notes[7] = {F_C4, F_D4, F_E4, F_F4, F_G4, F_A4, F_B4};
uint8_t totalNotes = sizeof(notes)/sizeof(notes[0]);

int main(void) {
    bool hbOn = false;
    uint8_t noteIndex = 0;

    setSystemClock();

    mod_led_init();
    init_rtc();
    init_dds();
    
    // set DAC Vref to 4.3v.
    VREF.CTRLA |= VREF_DAC0REFSEL_1_bm | VREF_DAC0REFSEL_0_bm;
    PORTA.DIR |= PIN6_bm; // set as OUTPUT
    DAC0.CTRLA |= DAC_OUTEN_bm | DAC_ENABLE_bm;
    
    sei();          // enable global interrupts.
    
    while (1) {
        /* Heartbeat to show that the system is still cycling */
        if(lastTime < millis()) {
            lastTime = millis() + HB_WAIT;
            if(hbOn) {
                hbOn = false;
                mod_led_off();
                setInc(notes[noteIndex]);
                if(++noteIndex >= totalNotes) {
                    noteIndex = 0;
                }
            } else {
                hbOn = true;
                mod_led_on();
            }
        }
        
        
        
    }
}
