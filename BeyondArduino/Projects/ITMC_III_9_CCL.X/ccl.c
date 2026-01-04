/*
 * File:   ccl.c
 * Author: CmdrZin
 *
 * Created on October 17, 2024, 3:28 PM
 * 
 * LED  PA4 LUT0-OUT
 * SW1  PA1 LUT0-IN1
 * SW2  PA2 LUT0-IN2
 * 
 */


#include <avr/io.h>
#include "ccl.h"

void init_CCL()
{
    CCL.LUT0CTRLB = CCL_INSEL1_2_bm | CCL_INSEL1_0_bm;      // IO (0x5)
    CCL.LUT0CTRLC = CCL_INSEL2_2_bm | CCL_INSEL2_0_bm;      // IO (0x5)
    CCL.TRUTH0 = 0b01000000;                                // 110 > 1
    
    CCL.LUT0CTRLA |= CCL_ENABLE_bm;     // enable LUT0
    CCL.CTRLA |= CCL_ENABLE_bm;         // enable CCL
}