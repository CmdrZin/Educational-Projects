/*
 * File:   main04.c
 * Author: Cmdrzin
 *
 * Created on August 6, 2024
 */


#include <avr/io.h>
#include <avr/interrupt.h>          // to support the use of interrupts
#include <avr/pgmspace.h>

#include "systime.h"                // access systime functions.

#define LED_DELAY		1UL		// N * 1ms
#define LED_ROTATE      200UL

typedef struct LEDconfig {
    uint8_t dir;
    uint8_t lines;
} LED_CONFIG;

//  dir, lines PA:76543210
const LED_CONFIG select[] PROGMEM = {
    { 0b00000110, 0b00000100 },     // D1   PA2->PA1
    { 0b00000110, 0b00000010 },     // D2   PA1->PA2
    { 0b00001100, 0b00000100 },     // D3   PA2->PA3
    { 0b01001000, 0b00001000 },     // D4   PA3->PA6
    { 0b11000000, 0b01000000 },     // D5   PA6->PA7
    { 0b00001010, 0b00001000 },     // D6   PA3->PA1
    { 0b00001100, 0b00001000 },     // D7   PA3->PA2
    { 0b01001000, 0b01000000 },     // D8   PA6->PA3
    { 0b11000000, 0b10000000 },     // D9   PA7->PA6
    { 0b10001000, 0b00001000 },     // D10  PA3->PA7
    { 0b01000010, 0b01000000 },     // D11  PA6->PA1
    { 0b01000100, 0b01000000 },     // D12  PA6->PA2
    { 0b10001000, 0b10000000 },     // D13  PA7->PA3
    { 0b01000100, 0b00000100 },     // D14  PA2->PA6
    { 0b10000100, 0b00000100 },     // D15  PA2->PA7
    { 0b10000010, 0b10000000 },     // D16  PA7->PA1
    { 0b10000100, 0b10000000 },     // D17  PA7->PA2
    { 0b00001010, 0b00000010 },     // D18  PA1->PA3
    { 0b01000010, 0b00000010 },     // D19  PA1->PA6
    { 0b10000010, 0b00000010 }      // D20  PA1->PA7
};
//                               LED   09876543210987654321         
const uint32_t pattern = 0b00000000000010000000000000000000;
uint32_t display;

void nextLED();

int main(void) {
   	uint32_t ledTime = 0UL;
    uint32_t rotateTime = 0UL;
    uint32_t live = pattern;    // copy of starting pattern
    display = live;

    init_systime();             // set up TCA0 timer.
    
    /* enable Global interrupts */
    sei();
   
    // Send out voltage, in HEX, each second.
    while (1) {
		if( millis() > ledTime ) {
			ledTime = millis() + LED_DELAY;
            nextLED();
		}
		if( millis() > rotateTime ) {
			rotateTime = millis() + LED_ROTATE;
            live = live << 1;
            if( (live & 0x00100000) != 0 ) {
                live |= 0x01;
            }
            display = live;
		}
    }
}

// Display the pattern in display.
void nextLED()
{
    uint32_t temp;
    static uint8_t led = 0;
    static LED_CONFIG nextConfig = {0,0};
    uint16_t  adrs;
    uint16_t config;
    
    // First, update display.
    PORTA.DIR = 0;              // turn OFF all lines.
    PORTA.OUT = nextConfig.lines;
    PORTA.DIR = nextConfig.dir;

    // Then calculate next display.
//    adrs = (uint16_t)&select[0];      // this is equivalent to the next line of code.
    adrs = (uint16_t)select;            // get the address of the top of the table.
    adrs = adrs + (led<<1);     // double to skip 2 bytes per index.
    
    temp = display >> led;      // shift display bit to LSB.
    if( temp & 0x0001UL ) {
        config = pgm_read_word_near( adrs );
        nextConfig.dir = (uint8_t)(config & 0x00FF);
        nextConfig.lines = (uint8_t)(config>>8);
    } else {
        nextConfig.dir = 0;
        nextConfig.lines = 0;
    }

    if (++led > 19) {
        led = 0;
    }
}
