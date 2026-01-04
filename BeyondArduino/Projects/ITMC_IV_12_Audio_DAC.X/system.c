/*
 * File:   system.c
 * Author: Cmdrzin
 *
 * Created on May 21, 2025, 9:16 AM
 */


#include <avr/io.h>

// Set system clock to 20 MHz. Also sets CLK_PER to 20 MHz.
void setSystemClock()
{
    // Initialize MCU clock for 20 MHz
    CPU_CCP = CCP_IOREG_gc;		// unlock Change Protected Registers
	CLKCTRL_MCLKCTRLB = 0;		// Clear PEN bit to disable pre-scaler
}