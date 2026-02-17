/*
 * File:   dac.c
 * Author: Cmdrzin
 *
 * Created on September 3, 2024, 1:47 PM
 */

#include <avr/io.h>

void init_dac()
{
    // set ADC and DAC Vref to 2.5v.
    VREF.CTRLA |= VREF_ADC0REFSEL_1_bm | VREF_DAC0REFSEL_1_bm;
    // enable DAC output pin and the DAC.
    DAC0.CTRLA |= DAC_OUTEN_bm | DAC_ENABLE_bm;
}

void set_dac_output(uint8_t value)
{
    DAC0.DATA = value;
}
