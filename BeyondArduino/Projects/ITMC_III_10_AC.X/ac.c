/*
 * File:   ac.c
 * Author: Cmdrzin
 *
 * Created on October 30, 2024, 4:41 PM
 */


#include <avr/io.h>
#include "ac.h"

void init_ac()
{
    VREF.CTRLA = 0x02;			// 2.5v ref
    AC0.MUXCTRLA = 0x02;			// VREF on negative input.
    AC0.CTRLA = AC_ENABLE_bm;
}

/* return true is ADC completed. */
bool check_ac()
{
    // Check AC output state
    return (AC0.STATUS && 0x10);
}
