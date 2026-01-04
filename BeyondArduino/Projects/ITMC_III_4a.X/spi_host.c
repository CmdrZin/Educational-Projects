/*
 * File:   spi.c
 * Author: CmdrZin
 *
 * Created on October 2, 2024, 3:23 PM
 */


#include <avr/io.h>
#include "spi_host.h"

#define MOSI    PIN1_bm
#define MISO    PIN2_bm
#define SCK     PIN3_bm
#define _SS     PIN4_bm

void init_spi(void)
{
    PORTA.DIR |= MOSI | SCK | _SS;
    SPI0.CTRLA |= SPI_MASTER_bm | SPI_PRESC_1_bm;
    SPI0.CTRLB |= SPI_SSD_bm;       // Disable Multi-Host, use Mode 0.
    SPI0.CTRLA |= SPI_ENABLE_bm;    // Enable SPI.
    SPI0.DATA = 0;                  // initiate first transfer. No /SS.
}

// Return FALSE  is val was corrupted.
bool spiSendByte(uint8_t val)
{
    bool result = false;
    
    PORTA.OUT &= ~(_SS);            // activate /SS
    
    SPI0.DATA = val;

    while( (SPI0.INTFLAGS & SPI_IF_bm) == 0);     // wait for transfer to complete.
    
    PORTA.OUT |= _SS;               // deactivate /SS

    // Check for collision.
    if( SPI0.INTFLAGS & SPI_WRCOL_bm ) {
        result = false;
    } else {
        result = true;
    }
    
    return result;
}
