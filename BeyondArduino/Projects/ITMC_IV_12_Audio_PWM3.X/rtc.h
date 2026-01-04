/* 
 * File:   rtc.h
 * Author: Cmdrzin
 *
 * Created on May 18, 2025
 */

#ifndef RTC_H
#define	RTC_H

#include <avr/interrupt.h>          // to support the use of interrupts

#define CCP_IOREG_gc            (CPU_CCP_7_bm | CPU_CCP_6_bm | CPU_CCP_4_bm | CPU_CCP_3_bm)    // 0xD8
#define RTC_CLKSEL_INT32K_gc    (0)

uint32_t millis(void);              // prototype for millis() function
void init_rtc(void);

#endif	/* RTC_H */

