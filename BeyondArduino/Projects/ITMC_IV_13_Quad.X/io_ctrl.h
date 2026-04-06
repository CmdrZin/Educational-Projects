/* 
 * File:   io_ctrl.h
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:55 PM
 */

#ifndef IO_CTRL_H
#define	IO_CTRL_H

#include <stdbool.h>

void init_io(void);    
void toggle_LED();
void setFWD(bool state);
void setREV(bool state);
void toggleCNT();

#endif	/* IO_CTRL_H */

