/*
 * File:   spi.c
 * Author: CmdrZin
 *
 * Created on October 2, 2024, 3:23 PM
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi_client.h"

volatile uint8_t spiDataIn = 0;         // Set by USI interrupt routine.
volatile bool spiInFlag = false;        // Set by USI interrupt routine.

// Set up as SLAVE device.
// Use alt configuration PORTMUX CTRLB
// 
// SPI_CLOCK  J1-7    12  PC0 (SCLK)  INPUT
// SPI_DIN    J1-5    14  PC2 (SDI)   INPUT
// SPI_LATCH  J1-4    15  PC3 (/SS)   INPUT
void init_spi(void)
{
    // PORTC pins default as INPUT.
    SPI0.CTRLA |= SPI_ENABLE_bm;        // MSB first & ENABLE.
    PORTMUX.CTRLB = PORTMUX_SPI0_bm;    // PC0:2 used instead of PA1:3
    SPI0.INTFLAGS = SPI_IF_bm;          // clear IF flag
    SPI0.INTCTRL |= SPI_IE_bm;          // enable interrupt
}

bool isSpiData()
{
    return spiInFlag;
}

// Check isSpiData() first. If true, then call this function.
uint8_t getSpiData()
{
    spiInFlag = false;                  // reset flag.
    return spiDataIn;
}

ISR(SPI0_INT_vect)
{
    spiDataIn = SPI0.DATA;
    spiInFlag = true;
    SPI0.INTFLAGS = SPI_IF_bm;          // clear IF flag
}
