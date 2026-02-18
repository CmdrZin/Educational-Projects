/*
 * File:   spi_client.c
 * Author: CmdrZin
 *
 * Created on October 2, 2024, 3:23 PM
 * 
 * A Simple SPI Client that receives low speed data from a Host.
 * NOTE: Set PA2 as an OUTPUT to echo back data to the Host.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi_client.h"

volatile uint8_t spiDataIn = 0;         // Set by USI interrupt routine.
volatile bool spiInFlag = false;        // Set by USI interrupt routine.

// Set up as SLAVE device.
void init_spi(void)
{
    SPI0.CTRLA |= SPI_ENABLE_bm;        // MSB first & ENABLE.
    SPI0.INTFLAGS = SPI_IF_bm;          // clear IF flag
    SPI0.INTCTRL |= SPI_IE_bm;          // enable interrupt
    
    // Uncomment to echo back data to host
//    PORTA.DIR |= PIN2_bm;
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
