/*
 * File:   dss.c
 * Author: Cmdrzin
 *
 * Created on September 22, 2024, 5:31 PM
 */


#include <avr/io.h>
#include <avr/pgmspace.h>

#include "dds.h"
#include "dac.h"

#include "io_ctrl.h"        // DEBUG


const char sinTable127[] PROGMEM;

uint16_t sinAccumulator;
uint16_t step;                  // xx.yy .. 8.8 fractional

/* 
 * The DSS system uses a 20 MHz CPU clock, so the Pre-scaler has to be disabled.
 * The base frequency is 261.626 Hz (middle C). So the sample clock is 10.500 us (10.493 us)
 * A DAC voltage of 0.250 volts is middle C allowing for two octaves of range up.
 * 0.500 volts doubles the index step and therefore, doubles the frequency. (one octave up)
 * 1.00 volt quadruples the index step and therefore, quadruples the frequency. (two octaves up)
 * 
 * TCB is used for the sample clock.
 */


/* 
 * Vref = 1.1v  10bit ADC   1.00v = 931/1024 (0x03A3)
 *              8bit DAC    1.00v = 233/256 (0x00E9)
 */
void init_dds(void)
{
    // Initialize MCU clock for 20 MHz. This WILL affect systime.c settings.
    CPU_CCP = CCP_IOREG_gc;		// unlock Change Protected Registers
	CLKCTRL_MCLKCTRLB = 0;		// Clear PEN bit to disable pre-scaler

	// Initialize TCB0 to generate an OVF interrupt every 10.50 us. 20 MHz (0.050 us) CLK_PER
	TCB0_CCMP = 0x00D1;									// 210 - 1
//	TCB0_CTRLB                      				    // (default) CNTMODE[2:0] = 000
	TCB0_INTCTRL = TCB_CAPT_bm;							// Set CAPT interrupt flag
	TCB0_CTRLA = TCB_ENABLE_bm;							// turn ON the timer. CLKSEL[2:0]=000 (Clock/1)
    
    // Set Vref to 1.1v for both ADC and DAC. (for VCO project)
    VREF.CTRLA = VREF_ADC0REFSEL_0_bm | VREF_DAC0REFSEL_0_bm;

    sinAccumulator = 0;
    step = 0x0100;              // 1.0
}

/*
 * Set the Frequency based on the input voltage.
 * 
 * 0.125  (0x0074)  step 4.0    0x0040
 * 0.250v (0x00E8)  step 8.0    0x0080
 * 0.500v (0x01D1)  step 16.0   0x1000
 * 1.000v (0x03A3)  step 32.0   0x1FFF
 * 
 * 8.8 notation.
 * 
 * Accepts 10-bit ADC value. (0x03FF max)
 */
void setFrequency(uint16_t v)
{
    step = (v<<3);        // result is 8.8 fractional notation for step.
    //TODO: Use piece-wise linear tables to convert voltage into step.
    //use 4.3 Vref for better voltage span. (see DDS_Notes.rtf)
}

// Generate the next wave value. Do this after sending last value to DAC.
uint8_t sinWave()
{
    return 0;
}

// Generate the next wave value
void triangleWave()
{
        
}

// Generate the next wave value
void squareWave()
{
    
}

/*
 * This interrupt service is called every 10.50 us.
 * to update the DAC output.
 */
ISR(TCB0_INT_vect)
{
    // TODO: Support other waveforms.
    sinAccumulator += step;
    set_dac_output( 128+ pgm_read_byte( &(sinTable127[sinAccumulator>>8]) ) );
    
	TCB0.INTFLAGS = TCB_CAPT_bm;	// clear interrupt flag.
}



// Sin wave table. 256 byte entry for +112:0:-112
const char sinTable112[] PROGMEM = {
	0,   3,   5,   8,  11,  14,  16,  19,  22,  25,  27,  30,  33,  35,  38,  40,
	43,  45,  48,  50,  53,  55,  58,  60,  62,  64,  67,  69,  71,  73,  75,  77,
	79,  81,  83,  85,  87,  88,  90,  92,  93,  95,  96,  97,  99, 100, 101, 102,
	103, 104, 105, 106, 107, 108, 109, 109, 110, 110, 111, 111, 111, 112, 112, 112,
	112, 112, 112, 112, 111, 111, 111, 110, 110, 109, 109, 108, 107, 106, 105, 104,
	103, 102, 101, 100,  99,  97,  96,  95,  93,  92,  90,  88,  87,  85,  83,  81,
	79,  77,  75,  73,  71,  69,  67,  64,  62,  60,  58,  55,  53,  50,  48,  45,
	43,  40,  38,  35,  33,  30,  27,  25,  22,  19,  16,  14,  11,   8,   5,   3,
	0,  -3,  -5,  -8, -11, -14, -16, -19, -22, -25, -27, -30, -33, -35, -38, -40,
	-43, -45, -48, -50, -53, -55, -58, -60, -62, -64, -67, -69, -71, -73, -75, -77,
	-79, -81, -83, -85, -87, -88, -90, -92, -93, -95, -96, -97, -99,-100,-101,-102,
	-103,-104,-105,-106,-107,-108,-109,-109,-110,-110,-111,-111,-111,-112,-112,-112,
	-112,-112,-112,-112,-111,-111,-111,-110,-110,-109,-109,-108,-107,-106,-105,-104,
	-103,-102,-101,-100, -99, -97, -96, -95, -93, -92, -90, -88, -87, -85, -83, -81,
	-79, -77, -75, -73, -71, -69, -67, -64, -62, -60, -58, -55, -53, -50, -48, -45,
	-43, -40, -38, -35, -33, -30, -27, -25, -22, -19, -16, -14, -11,  -8,  -5, -3
};

// Sin wave table. 256 byte entry for +127:0:-128
const char sinTable127[] PROGMEM = {
       0,    3,    6,    9,   12,   16,   19,   22,   25,   28,   31,   34,   37,   40,   43,   46,
      49,   51,   54,   57,   60,   63,   65,   68,   71,   73,   76,   78,   81,   83,   85,   88,
      90,   92,   94,   96,   98,  100,  102,  104,  106,  107,  109,  111,  112,  113,  115,  116,
     117,  118,  120,  121,  122,  122,  123,  124,  125,  125,  126,  126,  126,  127,  127,  127,
     127,  127,  127,  127,  126,  126,  126,  125,  125,  124,  123,  122,  122,  121,  120,  118,
     117,  116,  115,  113,  112,  111,  109,  107,  106,  104,  102,  100,   98,   96,   94,   92,
      90,   88,   85,   83,   81,   78,   76,   73,   71,   68,   65,   63,   60,   57,   54,   51,
      49,   46,   43,   40,   37,   34,   31,   28,   25,   22,   19,   16,   12,    9,    6,    3,
      -3,   -3,   -6,   -9,  -12,  -16,  -19,  -22,  -25,  -28,  -31,  -34,  -37,  -40,  -43,  -46,
     -49,  -51,  -54,  -57,  -60,  -63,  -65,  -68,  -71,  -73,  -76,  -78,  -81,  -83,  -85,  -88,
     -90,  -92,  -94,  -96,  -98, -100, -102, -104, -106, -107, -109, -111, -112, -113, -115, -116,
    -117, -118, -120, -121, -122, -122, -123, -124, -125, -125, -126, -126, -126, -127, -127, -127,
    -127, -127, -127, -127, -126, -126, -126, -125, -125, -124, -123, -122, -122, -121, -120, -118,
    -117, -116, -115, -113, -112, -111, -109, -107, -106, -104, -102, -100,  -98,  -96,  -94,  -92,
     -90,  -88,  -85,  -83,  -81,  -78,  -76,  -73,  -71,  -68,  -65,  -63,  -60,  -57,  -54,  -51,
     -49,  -46,  -43,  -40,  -37,  -34,  -31,  -28,  -25,  -22,  -19,  -16,  -12,   -9,   -6,   -3 
};
