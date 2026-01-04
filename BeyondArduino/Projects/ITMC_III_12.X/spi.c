/*
 * File:   spi.c
 * Author: CmdrZin
 *
 * Created on October 2, 2024, 3:23 PM
 */


#include <avr/io.h>
#include "spi.h"

void init_spi(void)
{
    PORTA.DIR |= PIN4_bm;
    SPI0.CTRLA |= SPI_MASTER_bm | SPI_PRESC_1_bm | SPI_ENABLE_bm;
    SPI0.CTRLB |= SPI_SSD_bm;              // Default Mode 0.
}

// Return FALSE  is val can not be sent.
bool sendByte(uint8_t val)
{
    bool result = false;
    
    if( SPI0.INTFLAGS & SPI_IF_bm ) {
        SPI0.INTFLAGS &= ~(SPI_IF_bm);      // clear IF flag
        SPI0.DATA = val;
        result = true;
    }
    
    return result;
}
