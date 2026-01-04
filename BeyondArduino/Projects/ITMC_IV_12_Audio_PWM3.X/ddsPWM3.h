/* 
 * File:   systime.h
 * Author: Cmdrzin
 *
 * Created on May 18, 2025
 */

#ifndef SYSTIME_H
#define	SYSTIME_H

#include <avr/interrupt.h>          // to support the use of interrupts

void init_dds(void);
void setInc(uint8_t chan, uint16_t val);

// Note table   f = (n/256) * 305.17 Hz     n = (f/305.17) * 256
// Multiply by 2 to scale up. Divide by 2 to scale down.
#define F_C4    219     // 261.626
#define F_D4    246     // 293.665
#define F_E4    277     // 329.628
#define F_F4    293     // 349.228
#define F_G4    329     // 391.995
#define F_A4    369     // 440 Hz
#define F_B4    414     // 493.883

#endif	/* SYSTIME_H */

