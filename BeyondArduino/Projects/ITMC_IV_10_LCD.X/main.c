/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on March 27, 2025, 11:30 AM
 */


#include <avr/io.h>
#include <stdio.h>          // for sprintf()

#include "mod_led.h"
#include "systime.h"
#include "lcd_hd44780.h"

#define HEADER_DELAY    3000
#define WAIT_TIME   500     // n * ms

int main(void) {
    uint32_t    waitTime;
    int     count;
    char    buff[8];
    
    mod_led_init();
    mod_led_on();
    lcd_init();
    init_systime();
    mod_led_off();
    
    waitTime = HEADER_DELAY;
    count = 0;
    
    sei();                          // enable global interrupts for systime.
    
    while (1) {
        if( waitTime < millis() ) {
            waitTime = millis() + WAIT_TIME;

            (void)sprintf(buff,"%8d", count++);
            lcd_clearScreen();
            lcd_print(1,5,buff);        
        }
    }
}
