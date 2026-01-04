/* 
 * File:   adc.h
 * Author: Cmdrzin
 *
 * Created on August 19, 2024, 4:41 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <stdbool.h>

void init_adc();
void trigger_adc();
bool check_adc();
uint8_t read_adc();

#endif	/* ADC_H */

