/*
 * File:   quad.c
 * Author: Cmdrzin
 *
 * Created on March 24, 2026, 2:36 PM
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "quad.h"

#define B_PIN   PIN2_bm
#define A_PIN   PIN3_bm
#define EM_PIN  PIN1_bm

#define AB_PORT PORTA
#define AB_DDR  PORTA.DIR
#define AB_IN   PORTA.IN
#define EM_PORT PORTA
#define EM_DDR  PORTA.DIR

#define CNT_LED PIN2_bm
#define CNT_PORT    PORTB
#define CNT_DDR PORTB.DIR

#define REV_LED PIN6_bm
#define FWD_LED PIN7_bm
#define RF_PORT PORTA
#define RF_DDR  PORTA.DIR

static int position;        // this could be 32 bit.
static uint8_t state;       // make scope of state local to this file.
static DIR direction;

void init_quad()
{
    // set up i/o and PIN CHANGE intr
    // Receiver Setup
  	AB_DDR &= ~(A_PIN | B_PIN);			// set LOW for input (default)
    AB_PORT.PIN2CTRL = PORT_PULLUPEN_bm | PORT_ISC_0_bm;    // Pull-up, Both EDGEs intr.. 0x09
    AB_PORT.PIN3CTRL = PORT_PULLUPEN_bm | PORT_ISC_0_bm;    // Pull-up, Both EDGEs intr.. 0x09
    // Emitter setup
    EM_DDR |= EM_PIN;
    EM_PORT.OUT |= EM_PIN;              // turn ON emitter.
    
    position = 0;
    direction = D_CW;
    state = 0;
    
    // Emitter Setup
    EM_DDR |= EM_PIN;                   // set PA1 as OUTPUT
}

int getPosition()
{
    int pos;
    // prevent corruption due to interrupt occurring on multi-byte read.
    cli();
    pos = position;
    sei();
    
    return pos;
}

DIR getDirection()
{
    return direction;
}

// Detect Pin Change, either direction.
// NOTE that binary patterns are used.
ISR(PORTA_PORT_vect)
{
    uint8_t AB;
    
    // check bit flag
    if( PORTA.INTFLAGS & (A_PIN | B_PIN) )
    {
        // Read AB
        AB = (AB_IN & (A_PIN | B_PIN))>>2;      // mask the two input pins
        
        switch(state) {
            case 0b00:
                if(AB == 0b01) {
                    direction = D_CW;
                    ++position;
                    state = 0b01;
                } else {
                    if(AB == 0b10) {
                        direction = D_CCW;
                        --position;
                        state = 0b10;
                    }
                }
                break;
            
            case 0b01:
                if(AB == 0b11) {
                    direction = D_CW;
                    ++position;
                    state = 0b11;
                } else {
                    if(AB == 0b00) {
                        direction = D_CCW;
                        --position;
                        state = 0b00;
                    }
                }
                break;
            
            case 0b11:
                if(AB == 0b10) {
                    direction = D_CW;
                    ++position;
                    state = 0b10;
                } else {
                    if(AB == 0b01) {
                        direction = D_CCW;
                        --position;
                        state = 0b01;
                    }
                }
                break;

            case 0b10:
                if(AB == 0b00) {
                    direction = D_CW;
                    ++position;
                    state = 0b00;
                } else {
                    if(AB == 0b11) {
                        direction = D_CCW;
                        --position;
                        state = 0b11;
                    }
                }
                break;
                
            default:
                break;
        }
        PORTA.INTFLAGS |= ((A_PIN | B_PIN));   // clear interrupt flag bit.
    }
}
