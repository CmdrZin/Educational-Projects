/* 
 * File:   ir.h
 * Author: Cmdrzin
 *
 * Created on April 29, 2025, 11:49 AM
 */

#ifndef IR_H
#define	IR_H

#include <stdbool.h>

void ir_init();
bool ir_isData();
void ir_clearFlag();
uint8_t ir_getAddress();
uint8_t ir_getCommand();
uint16_t getTotalH();
uint16_t getTotalL();
uint16_t getDuration();
void ir_service();

#endif	/* IR_H */

