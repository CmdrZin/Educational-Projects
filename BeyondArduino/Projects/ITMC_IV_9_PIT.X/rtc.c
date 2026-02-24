/*
 * File:   rtc.c
 * Author: Cmdrzin
 *
 * Created on October 14, 2024, 10:49 AM
 */

#include <avr/io.h>
#include "rtc.h"
#include "io_ctrl.h"

void init_rtc()
{
    CPU_CCP = CCP_IOREG_gc;		// unlock Change Protected IO Registers
    CLKCTRL.OSC32KCTRLA = 0x02; // Force startup of oscillator.
    
    RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;    // 32.768kHz Internal Crystal Oscillator (INT32K)

    while( RTC.STATUS > 0);             // Wait for RTC to synchronize with system.
    
    // Set RTC Period register to overflow at 512
    RTC.PER = 512;
    // Enable interrupt on overflow.
    RTC.INTCTRL |= RTC_OVF_bm;
    // DIV32
    RTC.CTRLA = RTC_PRESCALER_2_bm | RTC_PRESCALER_0_bm     // 0x05 for DIV32 for 1024 Hz clock.
            | RTC_RTCEN_bm                                  // Enable the RTC
            | RTC_RUNSTDBY_bm;                              // (optional) Run in standby (Sleep Mode)
}

// RTC Interrupt
ISR(RTC_CNT_vect)
{
    RTC.INTFLAGS = RTC_OVF_bm;
    toggle_LED();                           // Replace with other code as needed.
}
