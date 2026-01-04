/* 
 * File:   rgb.h
 * Author: CmdrZin
 *
 * Created on September 18, 2024, 3:19 PM
 */

#ifndef RGB_H
#define	RGB_H

typedef struct {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} GRB_t;

typedef enum { 
    rBLACK=0, rRED, rGREEN, rBLUE, rYELLOW, rWHITE
} RGB_COLOR_t;

// C Functions
void init_rgb();
void display(uint8_t p);
void cycle();

// ASM functions
extern void sendLED(RGB_COLOR_t b);

#endif	/* RGB_H */

