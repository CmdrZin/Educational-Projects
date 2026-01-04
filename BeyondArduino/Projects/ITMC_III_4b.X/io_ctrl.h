/* 
 * File:   io_ctrl.h
 * Author: Cmdrzin
 *
 * Created on October 30, 2024, 12:55 PM
 */

#ifndef IO_CTRL_H
#define	IO_CTRL_H

#include <stdbool.h>

void init_io(void);    
void toggle_LED();
void set_LED(bool state);

#endif	/* IO_CTRL_H */

