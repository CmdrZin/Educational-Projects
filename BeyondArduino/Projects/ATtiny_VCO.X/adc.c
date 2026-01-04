/*
 * File:   adc.c
 * Author: Cmdrzin
 *
 * Created on August 19, 2024, 4:41 PM
 * 
 * Maximum sample rate is 115 kHz
 * 
 * When used with the ATtiny_VCO project, the sample rate will be 20 kHz, Free-run.
 */


#include <avr/io.h>
#include "adc.h"

void init_adc()
{
    // Set Vref to 1.1v for both ADC and DAC. (for VCO project)
    VREF.CTRLA = VREF_ADC0REFSEL_0_bm | VREF_DAC0REFSEL_0_bm;

    ADC0.CTRLA = ADC_RESSEL_10BIT_gc;                  // 8-bit resolution.
    ADC0.CTRLC = 0x40 | ADC_REFSEL_VDDREF_gc | ADC_PRESC_DIV256_gc;    // SAMPCAP, Vref = VDD, CLK_PER/256 (20 MHz clock)
    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;   // AIN2 as input.
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

/* Wait for the conversion to complete, then return the 10-bit ADC value. */
uint16_t read_adc()
{
    while(!check_adc());    // wait for completion

    return ADC0.RES;
}
