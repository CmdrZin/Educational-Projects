/*
 * File:   rgb.c
 * Author: CmdrZin
 *
 * Created on September 18, 2024, 3:13 PM
 * 
 * This library MUST use the 20 MHz clock. Default is 3.33 MHz.
 * systime.c must be adjusted to use 20 MHz, not 3.33 MHz.
 */


#include <avr/io.h>
#include <avr/pgmspace.h>

#include "rgb.h"

#define MAX_LEDS    8

#define CYCLE_DELAY     100     // n * ms

// Byte patterns for colors. Indexed by RGB_COLOR_t enum list
// Green, Red , Blue
const GRB_t ledColor[] PROGMEM = {
    {0x00, 0x00, 0x00},         // rBLACK=0
    {0x00, 0x40, 0x00},         // rRED=1
    {0x40, 0x00, 0x00},         // rGREEN=2
    {0x00, 0x00, 0xFF},         // rBLUE=3
    {0x30, 0x30, 0x00},         // rYELLOW=4
    {0x30, 0x30, 0x30}          // rWHITE=5
};

// Array used for display() to update an LED string.
RGB_COLOR_t outPattern1[MAX_LEDS] = {
    rRED, rGREEN, rYELLOW, rBLUE, rGREEN, rWHITE, rYELLOW, rBLUE
};

// Array used for display() to update an LED string.
RGB_COLOR_t outPattern2[MAX_LEDS] = {
    rGREEN, rYELLOW, rBLUE, rGREEN, rYELLOW, rBLUE, rWHITE, rRED
};

// Set Clock to 20 NHz..DIV1
void init_rgb()
{
    // Initialize MCU clock for 20 MHz
    CPU_CCP = CCP_IOREG_gc;		// unlock Change Protected Registers
	CLKCTRL_MCLKCTRLB = 0;		// Clear PEN bit to disable prescaler
}

void display(uint8_t pattern)
{
    if( pattern == 0) {
        for(int i=0; i<sizeof(outPattern1); i++) {
            sendLED(outPattern1[i]);         // call ASM function
        }
    } else {
        for(int i=0; i<sizeof(outPattern2); i++) {
            sendLED(outPattern2[i]);         // call ASM function
        }
    }
}

// Cycle through all available colors.
void cycle() {
    uint8_t color;
    int i;
        
    color = outPattern1[0];
    for( i=1; i<sizeof(outPattern1); i++ ) {
        outPattern1[i-1] = outPattern1[i];
    }
    outPattern1[i-1] = color;
}

