/* 
 * File:   io_ctrl.h
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:55 PM
 */

#ifndef IO_CTRL_H
#define	IO_CTRL_H

#include <stdbool.h>

typedef enum { LED_RED, LED_YELLOW, LED_GREEN } LED;

void init_io(void);    
void toggle_LED();
void set_leds(LED led);

#endif	/* IO_CTRL_H */

