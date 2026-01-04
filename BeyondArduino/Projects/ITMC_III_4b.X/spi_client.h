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
bool isSpiData();
uint8_t getSpiData();

#endif	/* SPI_H */

