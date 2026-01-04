/* 
 * File:   dds.h
 * Author: Cmdrzin
 *
 * Created on September 22, 2024, 5:31 PM
 */

#ifndef DDS_H
#define	DDS_H

#include <stdbool.h>
#include <avr/interrupt.h>          // to support the use of interrupts

void init_dds(void);
void setFrequency(uint16_t v);
uint8_t sinWave();

#endif	/* DDS_H */

