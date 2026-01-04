/*
 * File:   dac.c
 * Author: Cmdrzin
 *
 * Created on September 3, 2024, 1:47 PM
 * 
 * Maximum update rate is 350 kHz
 */

#include <avr/io.h>

void init_dac()
{
    // Set Vref to 1.1v for both ADC and DAC. (for VCO project)
    VREF.CTRLA = VREF_ADC0REFSEL_0_bm | VREF_DAC0REFSEL_0_bm;

    // enable DAC output pin and the DAC.
    PORTA.DIR |= PIN6_bm;                   // set as OUTPUT
    DAC0.CTRLA |= DAC_OUTEN_bm | DAC_ENABLE_bm;
}

void set_dac_output(uint8_t value)
{
    DAC0.DATA = value;
}
