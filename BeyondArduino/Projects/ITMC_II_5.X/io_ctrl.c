/*
 * File:   io_ctrl.c
 * Author: Cmdrzin
 *
 * Created on August 8, 2024, 12:30 PM
 */


#include <avr/io.h>
#include "io_ctrl.h"

/* *** Initialize the IO PORT ***
 * MUST MATCH THE DEVICE BEING USED!
 */
void init_io(void){
    /* set PAn of PORTx as an OUTPUT pin. The other bits are left as '0'
     * so that their associated pins will be INPUT pins. */
	PORTA.DIR |= PIN7_bm;
}
