/*
 * File:   adc.c
 * Author: Cmdrzin
 *
 * Created on August 19, 2024, 4:41 PM
 */


#include <avr/io.h>
#include "adc.h"

void init_adc()
{
    ADC0.CTRLA = ADC_RESSEL_8BIT_gc;                  // 8-bit resolution.
    ADC0.CTRLC = 0x40 | ADC_REFSEL_VDDREF_gc | ADC_PRESC_DIV4_gc;    // SAMPCAP, Vref = VDD, CLK_PER/4
    ADC0.MUXPOS = ADC_MUXPOS_AIN3_gc;   // AIN3 as input.
    ADC0.CTRLA |= ADC_ENABLE_bm;        // enable the ADC.
}

void trigger_adc()
{
    // Start conversion.
    ADC0.COMMAND = 0x01;
}

/* return true is ADC completed. */
bool check_adc()
{
    bool status = false;
    
    // Check for conversion complete.
    if (ADC0.COMMAND != 0x01)
    {
        status = true;
    }
    return status;
}

/* Wait for the conversion to complete, then return the ADC value. */
uint8_t read_adc()
{
    while(!check_adc());    // wait for completion

    return ADC0.RESL;
}
