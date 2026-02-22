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
    VREF.CTRLA = 0x02;			// 2.5v ref (see Section 18.5.1[2])

    AC0.MUXCTRLA = 0x02;		// use VREF for negative input.
    AC0.CTRLA = AC_ENABLE_bm;
}

/* return true if AC input above Ref voltage. */
bool check_ac()
{
    // Check AC output state
    return (AC0.STATUS & AC_STATE_bm);
}
