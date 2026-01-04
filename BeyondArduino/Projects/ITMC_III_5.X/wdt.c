/*
 * File:   wdt.c
 * Author: Cmdrzin
 *
 * Created on September 14, 2024, 4:50 PM
 * WDT - Watch Dog Timer
 */


#include <avr/io.h>

void init_wdt(void)
{
    WDT.CTRLA = WDT_PERIOD_1_bm;        // 16 ms
}

void resetWDT(void)
{
    asm("WDR");
}
