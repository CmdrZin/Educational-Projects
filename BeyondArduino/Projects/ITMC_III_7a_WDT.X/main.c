/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on February 19, 2026
 * 
 * Example code for using the Watchdog Timer(WDT)
 * ref: ATtiny212-214-412-414-416-DataSheet-DS40002287A.pdf
 * 
 * The WDT issues a RESET if it times out. This clears all registers and SRAM.
 * This example uses EEPROM to store a state variable to continue a count after reset.
 */

#include <avr/io.h>

// Configuration code to set up the WDT.
FUSES = {
	.WDTCFG = 0x0B, // WDTCFG {PERIOD=8KCLK, WINDOW=OFF}
	.BODCFG = 0x00, // BODCFG {SLEEP=DIS, ACTIVE=DIS, SAMPFREQ=1KHz, LVL=BODLEVEL0}
	.OSCCFG = 0x02, // OSCCFG {FREQSEL=20MHZ, OSCLOCK=CLEAR}
	.TCD0CFG = 0x00, // TCD0CFG {CMPA=CLEAR, CMPB=CLEAR, CMPC=CLEAR, CMPD=CLEAR, CMPAEN=CLEAR, CMPBEN=CLEAR, CMPCEN=CLEAR, CMPDEN=CLEAR}
	.SYSCFG0 = 0xF6, // SYSCFG0 {EESAVE=CLEAR, RSTPINCFG=UPDI, CRCSRC=NOCRC}
	.SYSCFG1 = 0x07, // SYSCFG1 {SUT=64MS}
	.APPEND = 0x00, // APPEND {APPEND=User range:  0x0 - 0xFF}
	.BOOTEND = 0x00, // BOOTEND {BOOTEND=User range:  0x0 - 0xFF}
};

LOCKBITS = 0xC5; // {LB=NOLOCK}

#include <avr/eeprom.h>

#include "sysdefs.h"
#include "io_ctrl.h"

uint8_t countAdrs = 0;      // Use EEPROM address 0.

int main(void) {
    uint8_t cycleCounter = 0;               // Cleared to 0 on RESET.

    if (RSTCTRL.RSTFR & RSTCTRL_WDRF_bm) {
        // WDT reset. Load counter.
        cycleCounter = eeprom_read_byte((uint8_t *)countAdrs);
    } else {
        // Power-on reset. Clear counter.
        eeprom_write_byte((uint8_t *)countAdrs, 0);
    }
    
    init_io();                 // set up IO pins.

    // Initialize Sleep Control for Power-Down mode.       PDOWN | SEN
    SLPCTRL.CTRLA = SLPCTRL_SMODE_1_bm | SLPCTRL_SEN_bm;
  
    if (++cycleCounter > 10) {
        cycleCounter = 1;
    }
    eeprom_write_byte((uint8_t *)countAdrs, cycleCounter);
    for (int k = 0; k < cycleCounter; k++) {
        flash_LED();
    }
    
    asm("SLEEP");               // SLEEP until WDT time-out
}
