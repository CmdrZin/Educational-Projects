/*
 * File:   rtc.c
 * Author: Cmdrzin
 *
 * Created on May 18, 2025
 * 
 * RTC used for 1ms tic for millis() function.
 */

#include <avr/io.h>
#include "rtc.h"

volatile static uint32_t totalMilliseconds;	// local variable


void init_rtc()
{
    CPU_CCP = CCP_IOREG_gc;		// unlock Change Protected IO Registers
    CLKCTRL.OSC32KCTRLA = 0x02; // Force startup of oscillator.
    
    RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;    // 32.768kHz Internal Crystal Oscillator (INT32K)

    while( RTC.STATUS > 0);             // Wait for RTC to synchronize with system.
    
    // Set RTC Period register to overflow at 32 using 32kHz clock (default CLKSEL)
    RTC.PER = 34;
    // Enable interrupt on overflow.
    RTC.INTCTRL |= RTC_OVF_bm;
    // DIV1
    RTC.CTRLA = RTC_RTCEN_bm                                // Enable the RTC
            | RTC_RUNSTDBY_bm;                              // (optional) Run in standby (Sleep Mode)
}

/* Return the total number of milliseconds since the project started. */
uint32_t millis(void)
{
	uint32_t temp;			// make a holder for the counter.
    uint8_t sreg_save;
    
    // Save SREG, disable interrupts, do code, restore SREG.
    // If interrupts were enabled, they will be re-enabled.
    sreg_save = SREG;
    cli();
  	temp = totalMilliseconds;	// get a copy while interrupts are disabled.
    SREG = sreg_save;

	return temp;			// return a 'clean' copy of the counter.
}

// RTC Interrupt
ISR(RTC_CNT_vect)
{
   	++totalMilliseconds;
    RTC.INTFLAGS = RTC_OVF_bm;          // clear interrupt flag.
}
