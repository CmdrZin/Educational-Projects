/* 
 * File:   spi.h
 * Author: CmdrZin
 *
 * Created on October 2, 2024, 4:23 PM
 */

#ifndef SPI_H
#define	SPI_H

#include <stdbool.h>

void init_spi(void);
bool spiSendByte(uint8_t val);


#endif	/* SPI_H */

