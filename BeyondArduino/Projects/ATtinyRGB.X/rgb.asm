/*
 * File:   rgb.asm
 * Author: CmdrZin
 *
 * Created on September 18, 2024, 3:13 PM
 *     
 * WS2812B
 * 0: H:0.40us L:0.85us
 * 1: H:0.80us L:0.45us
 * SK6812
 * 0: H:0.30us L:0.95us
 * 1: H:0.60us L:0.65us
 * SKC6812RV
 * 0: H:0.30us L:0.95us
 * 1: H:0.80us L:0.45us
 *
 * Target: ATtiny AVR Series-1
 * Uses 20 MHz (0.050 us) CPU clock
 *
 * C_ASM_ICD
 * Can use r18:27, r30:31 in ASM without saving
 * X:r27,r26	Y:r29,r28	Z:r31,30	r1=0 always
 */ 
#include <arv/io.h>

DOUT_PORT = PORTA	    // MUST MATCH DEVICE PORT! .. ATtiny412 8SIOC
DOUT_PIN  = PORTA3	    // MUST MATCH DEVICE PIN! .. ATtiny412 8SIOC

    .section .text

/*
 * sendLED(RGB_COLOR_t out)
 *
 * r25:r24 = out
 * table has 3 bytes per entry. (see rgb.h GRB_t)
 * bytes: ledColor[out].green, ledColor[out].red, ledColor[out].blue
 *
 * For multiple LEDs, must be called again withing 50us after return.
 */
.global sendLED
sendLED:
	; multiply index by 3
    mov		r18, r24
    add		r24, r24			; double
    add		r24, r18			; x3
	; Z = table
    ldi		ZH, hi8(ledColor)
    ldi		ZL, lo8(ledColoc)
	; add index
    add		ZL, r24
    adc		ZH, r1				; r1 always 0
	; get GREEN color code
    lpm		r24, Z+
	;
	call sendByte
; send byte
	;
	; get RED color code
    lpm		r24, Z+
	;
	; send byte
	;
	; get BLUE color code
    lpm		r24, Z
	;
	; send byte

    ret    

/*
 * Send byte to SKC6812RV using stated timing sequence.
 * WS2812B
 * 0: H:0.40us L:0.85us
 * 1: H:0.80us L:0.45us
 * SK6812
 * 0: H:0.30us L:0.95us
 * 1: H:0.60us L:0.65us
 * SKC6812RV
 * 0: H:0.30us L:0.95us
 * 1: H:0.80us L:0.45us
 *
 * ASSUMES a 50ns clock (20 MHz)
 *     
 * r24 = byte
 */
sendByte:
    ; DISABLE INTERRUPTS. This code is time critical.
    cli
    ;
    ; Output loop. X->list. r23:22 -> count
    ;
    ldi	    r25, 8		; (1) load bit count
    ;
wuLoop01:
    ; Test bit
    rol	    r24		; (1) move test bit into CY
    brcs    wuSkip01	; (f.1) (t.2) go to Output a 1.
    ;
    ; Output a 0 [0.30us]. H for 6 cycles (0.30us)
wuLoop02:
    sbi	_SFR_IO_ADDR(DOUT_PORT), DOUT_PIN   ; (2) Always start H
    nop				; (1)		3
    nop				; (1)		4
    nop				; (1)		5
    nop				; (1)		6
    ;
    ; start L for [0.95us] 19 cycles (0.95us)
    cbi	_SFR_IO_ADDR(DOUT_PORT), DOUT_PIN   ; (2) Set L for 19 cycles (0.95us) and do next check
    dec	    r25			; (1) Dec bit count.			3   3	-
    breq    wuSkip03		; (f.1) (t.2) Finish & Exit if done.	4   5	-
    ; Finish phase 2. Pre-test bit
    rol	    r24			; (1) move test bit into CY.		5   -	13
    brcc    wuLoop02		; (f.1) (t.2) test bit. ouput a 0.  5	6   -
    
    
wuSkip03:			; 0 Exit	5
    nop				; (1)		6
    nop				; (1)		7
    nop				; (1)		9
    nop				; (1)		10
    nop				; (1)		11
    nop				; (1)		12
    nop				; (1)		13
    nop				; (1)		14
    
    ret