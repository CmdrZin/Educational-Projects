/*
 * File:   ir.c
 * Author: Cmdrzin
 *
 * Created on April 29, 2025, 11:49 AM
 */


#include <avr/io.h>

#include "ir.h"
#include "systime.h"
#include "mod_led.h"

// Local defines
#define IR_DDR          PORTA.DIR
#define IR_IN           PORTA.IN
#define IR_PIN      	PIN3_bm                 // 0x08

#define GAP_ZERO        900             // 936 = 562 us
#define GAP_ONE         2400            // 2811 = 1.6875 us
#define GAP_SYNC        6000            // 6666 = 4000 us


typedef enum {R_IDLE, R_SYNC, R_ADRS, R_NADRS, R_CMD, R_NCMD} R_STATES;

bool bitFlag = false;
uint8_t bitData = 0;        // 0=0, 1=1, 2=SYNC

bool dataFlag = false;      // true is message data is ready.
uint8_t irAddress = 0;
uint8_t irCommand = 0;

uint16_t totalH;
uint16_t totalL;

static uint8_t commandX = 0;
static uint8_t ncommand = 0;


void ir_init()
{
  	IR_DDR &= ~(IR_PIN);			// set LOW for input (default)
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;          // Pull-up, Both EDGEs intr. 0x09
    
    // Use TCB for timing.
    TCB0.CCMP = 0xFFFF;
    TCB0.CTRLA = TCB_CLKSEL_CLKDIV2_gc | TCB_ENABLE_bm;               /// DIV2 | ENABLE
}

bool ir_isData()
{
    return dataFlag;
}

void ir_clearFlag()
{
    dataFlag = false;
}

uint8_t ir_getAddress()
{
    return irAddress;
}

uint8_t ir_getCommand()
{
    return irCommand;
}

uint16_t getTotalH()
{
    return totalH;
};
uint16_t getTotalL()
{
    return totalL;
};

// 0.6us tics adjusted for overflow. ~39 ms.
uint16_t getDuration() {
    static uint16_t lastCnt = 0;
    uint16_t newCnt;
    uint16_t temp;
    
    temp = TCB0.CNT;            // save count
    newCnt = temp;
    
    if (lastCnt > newCnt)		// overflowed?
    	newCnt += ~lastCnt +1;
    else
    	newCnt -= lastCnt;
    lastCnt = temp;             // update

    return newCnt;
}


// call at least once every 500us.
// returns true is data is ready.
void ir_service()
{
    static R_STATES state = R_IDLE;
    static uint8_t bitCount = 0;
    static uint8_t address = 0;
    static uint8_t naddress = 0;
    
    if( bitFlag )
    {
        switch(state)
        {
            case R_IDLE:            // waiting for SYNC
                if( bitData == 2 )
                {
                    state = R_ADRS;
                    mod_led_toggle(5);
                    bitCount = 0;
                    totalH = 0;
                    totalL = 0;
                    address = 0;    // reset for next set of bits.
                }
                break;
                
            case R_ADRS:            // capture Address
                totalH = (totalH<<1) + bitData;
                address = (address<<1) + bitData;
                if( ++bitCount == 8 ) {
                    bitCount = 0;
                    state = R_NADRS;
                    mod_led_toggle(6);
                    naddress = 0;
                }
                break;

            case R_NADRS:            // capture Address
                totalH = (totalH<<1) + bitData;
                naddress = (naddress<<1) + bitData;
                if( ++bitCount == 8 ) {
                    bitCount = 0;
                    state = R_CMD;
                    mod_led_toggle(7);
                    commandX =  0;
                }
                break;
                
            case R_CMD:
                totalL = (totalL<<1) + bitData;
                commandX = (commandX<<1) + bitData;
                if( ++bitCount == 8 ) {
                    bitCount = 0;
                    state = R_NCMD;
                    mod_led_toggle(8);
                    ncommand = 0;
                }
                break;

            case R_NCMD:
                totalL = (totalL<<1) + bitData;
                ncommand = (ncommand<<1) + bitData;
                if( ++bitCount == 8 ) {
                    bitCount = 0;
                    
                    if( ((address | naddress) == 0xFF) && ((commandX | ncommand) == 0xFF) )
                    {
                        irAddress = address;
                        irCommand = commandX;
                        dataFlag = true;
                    }
                    // restart regardless or good or error.
                    state = R_IDLE;
                    mod_led_toggle(9);
                }
                break;

            default:
                state = R_IDLE;
                break;
        }
        bitFlag = false;
    }
}

ISR(PORTA_PORT_vect)
{
    static uint16_t syncDelay = 0;
    uint16_t gapTime = 0;
    uint16_t gap = 0;
    
    // check bit flag
    if( PORTA.INTFLAGS & (IR_PIN))
    {
        // Check for 1 or 0.
        if( (IR_IN & IR_PIN) == IR_PIN )
        {
            // pin is now HIGH, setup to measuring a HIGH.
            // set to measure LOW
            syncDelay = TCB0.CNT;

            // ++ DEBUG
            mod_led_toggle(3);
            // -- DEBUG
        }
        else
        {
            // pin is now LOW, was measuring a HIGH.
            gapTime = TCB0.CNT;      // capture time

            if (syncDelay > gapTime)		// overflowed?
            	gap = gapTime + (~syncDelay + 1);
            else
            	gap = gapTime - syncDelay;
            
            if( gap < (GAP_SYNC<<1) )
            {
                if( gap > GAP_SYNC  )
                {
                    bitData = 2;
                }
                else if ( gap > GAP_ONE )
                {
                    bitData = 1;
                }
                else
                {
                    bitData = 0;
                }
                bitFlag = true;

                // ++ DEBUG
                mod_led_toggle(1);
                // -- DEBUG
            }
        }

        PORTA.INTFLAGS |= (IR_PIN);   // clear interrupt flag bit.
    }
    else
    {
        // Clear all flags. ERROR.
        PORTA.INTFLAGS = 0xFF;
    }
}
