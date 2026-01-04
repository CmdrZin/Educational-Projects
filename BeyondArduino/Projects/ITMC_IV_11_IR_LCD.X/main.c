/*
 * File:   main.c
 * Author: Cmdrzin
 *
 * Created on March 27, 2025, 11:30 AM
 * Revised on April 30, 2025.   Add IR support.
 */


#include <avr/io.h>
#include <stdio.h>          // for sprintf()

#include "mod_led.h"
#include "systime.h"
#include "lcd_hd44780.h"
#include "ir.h"

#define HEADER_DELAY    3000
#define WAIT_TIME   500     // n * ms

int main(void) {
    uint32_t    waitTime;
    int     count;
    char    buff[24];
    
    mod_led_init();
    mod_led_on();
    lcd_init();
    init_systime();
    ir_init();
    mod_led_off();
    
    waitTime = HEADER_DELAY + millis();
    count = 0;
    
    sei();                          // enable global interrupts for systime.

    // CLOCK TEST
#if 0
    while(1) {
        if( waitTime < millis() ) {
            waitTime = millis() + 1;
            if( ++count & 0x01 == 1) {
                mod_led_on();
            } else {
                mod_led_off();
            }
        }
    }
#endif    
    
    while( waitTime > millis() );      // Delay screen clear.
    waitTime = millis() + WAIT_TIME;
    lcd_clearScreen();
    
    while (1) {
        ir_service();               // service IR module at least every 500 us.
        if ( ir_isData() == true )
        {
            ir_clearFlag();
            (void)sprintf(buff,"AD:%2X CD:%2X T:%4X%4X", ir_getAddress(), ir_getCommand(), getTotalH(), getTotalL());
            lcd_print(2,0,buff);        
        }
        if( waitTime < millis() ) {
            waitTime = millis() + WAIT_TIME;

            lcd_print(1,5,"        ");
            (void)sprintf(buff,"%8d", count++);
            lcd_print(1,5,buff);        
        }
    }
}
