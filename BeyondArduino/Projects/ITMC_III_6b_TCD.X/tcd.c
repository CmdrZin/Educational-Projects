/*
 * File:   tcd.c
 * Author: CmdrZin
 *
 * Created on October 16, 2024, 2:59 PM
 */


#include <avr/io.h>

#define TCD_WOA     PIN6_bm        // PA6
#define TCD_WOB     PIN7_bm        // PA7

#define TCD_SYSCLK_gc   (TCD_CLKSEL_1_bm | TCD_CLKSEL_0_bm)
#define TCD_CNTDIV4_gc  (TCD_CNTPRES_0_bm)
#define TCD_SYNCDIV4_gc (TCD_SYNCPRES_1_bm)
#define TCD_ONERAMP_gc  (0)

// Setup for Mode 1 - Single Slope.
void init_TCD()
{
    // Set counter pins as OUTPUT.
    PORTA.DIRSET = TCD_WOA | TCD_WOB;
    // Use SYSCLK and DIV4 for prescalers.
    TCD0.CTRLA = TCD_SYSCLK_gc | TCD_CNTDIV4_gc | TCD_SYNCDIV4_gc;
    // Select One Ramp mode.
    TCD0.CTRLB = TCD_ONERAMP_gc;
    // Set up the delay and set compare registers.
	TCD0.CMPASET = 0x0400;
	TCD0.CMPACLR = 0x0800;
	TCD0.CMPBSET = 0x0C00;
	TCD0.CMPBCLR = 0x0FFF;
    
    // Turn on the timer by setting the ENABLE bit to ?1?. 
	TCD0.CTRLA |= TCD_ENABLE_bm;
}

void setTCD_setA(uint16_t val)
{
    TCD0.CMPASET = val;
}

void setTCD_setB(uint16_t val)
{
    TCD0.CMPBSET = val;
}