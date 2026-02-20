/* 
 * File:   io_ctrl.h
 * Author: Cmdrzin
 *
 * Created on August 30, 2024, 12:55 PM
 */

#ifndef IO_CTRL_H
#define	IO_CTRL_H

#include <avr/interrupt.h>

void init_io(void);
void enablePA1(void);
void disablePA1(void);
bool isSwitchPressed();
void toggle_LED(void);
void set_LED(bool state);
void flash_LED(void);

#endif	/* IO_CTRL_H */

