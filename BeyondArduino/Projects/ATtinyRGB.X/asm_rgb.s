/*
 * File:   rgb.s
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

#include <avr/io.h>
    
#define DOUT_PORT 0x0404	// PORTA.OUT (0x0404) SFR address. MUST MATCH DEVICE PORT! .. ATtiny412 8SIOC
#define DOUT_PIN  3		// MUST MATCH DEVICE PIN! .. ATtiny412 8SIOC

.extern ledColor
    
/*
 * sendLED(RGB_COLOR_t out)
 *
 * r25:r24 = out
 * table has 3 bytes per entry. (see rgb.h GRB_t)
 * bytes: ledColor[out].green, ledColor[out].red, ledColor[out].blue
 *
 * For multiple LEDs, must be called again withing 50us after return.
 */
    .section	.text
    .global	sendLED
sendLED:
    ; multiply index by 3
    mov	    r18, r24
    add	    r24, r24			; double
    add	    r24, r18			; x3
    ; Z = table
    ldi	    ZH, hi8(ledColor)
    ldi	    ZL, lo8(ledColor)
    ; add index
    add	    ZL, r24
    adc	    ZH, r1			; r1 always 0
    ; get GREEN color code
    lpm	    r24, Z+			; (3)
    rcall sendByte			; (4)
    ; get RED color code
    lpm	    r24, Z+			; (3)
    rcall sendByte			; (4)
    ; get BLUE color code
    lpm		r24, Z			; (3)
    rcall sendByte			; (4)
    ;
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
 *				; clks		    Accumlative
 *				; (n)			m
 */
sendByte:
    ; DISABLE INTERRUPTS. This code is time critical.
    cli
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
;    sbi	    _SFR_IO_ADDR(PORTA), 3   ; SBI does not work with new AVRs
    LDI XL, lo8(DOUT_PORT)	; X=r27:r26 lsb of addr   (1)	-   16
    LDI XH, hi8(DOUT_PORT)	; msb of addr   (1)		-   17
    LD	r18, X			; read PORT	(2)		-   18
    ORI r18, (1<<DOUT_PIN)	; set bit3	(1)		-   19
    ST X, r18			; update port   (1)	1
;
    nop				; (1)			2
    nop				; (1)			3
    ;
    ; start L for [0.95us] 19 cycles (0.95us)
;    cbi	    DOUT_PORT, 3   ; (2) Set L for 19 cycles (0.95us) and do next check
; reuse X to access PORT
    LD	r18, X			; read PORT	(2)	4
    ANDI r18, ~(1<<DOUT_PIN)	; clear bit3	(1)	5
    ST X, r18			; update port   (1)	6   1
; 
    dec	    r25			; (1) Dec bit count.	-    2
    breq    wuSkip03		; (f.1) (t.2) Finish & Exit if done.	-   3
    ; Finish phase 2. Pre-test bit
    rol	    r24			; (1) move test bit into CY.		-   4
    ; finish out phase-2 before testing
    nop				; (1)		5
    nop				; (1)		6
    nop				; (1)		7
    nop				; (1)		8
    nop				; (1)		9
    nop				; (1)		10
    nop				; (1)		11
    nop				; (1)		12
    nop				; (1)		13
    brcc    wuLoop02		; (f.1) (t.2) test bit. ouput a 0.	14
    nop				; (1)		-   15
    nop				; (1)		-   16
    ;
wuSkip01:
    ; Output a 1 [0.60us]. H for 12 cycles (0.60us)
;    sbi	    DOUT_PORT, 3   ; (2) Always start H
; reuse X to access PORT
    LD	r18, X			; read PORT	(2)	-   18
    ORI r18, (1<<DOUT_PIN)	; set bit3	(1)	-   19
    ST X, r18			; update port   (1)	-   1
;
    nop				; (1)		-   2
    nop				; (1)		-   3
    nop				; (1)		-   4
    nop				; (1)		-   5
    nop				; (1)		-   6
    nop				; (1)		-   7
    nop				; (1)		-   8
    nop				; (1)		-   9
    ; start L for [0.65us] 13 cycles (0.65us)
;    cbi	    DOUT_PORT, 3   ; (2) Set L for 13 cycles (0.65us) and do next check
; reuse X to access PORT
    LD	r18, X			; read PORT	(2)	-   11
    ANDI r18, ~(1<<DOUT_PIN)	; clear bit3	(1)	-   12
    ST X, r18			; update port   (1)	1
;
    dec	    r25			; (1) Dec bit count.			3
    breq    wuSkip04		; (f.1) (t.2) Finish & Exit if done.	4
    ; Finish phase 2. Pre-test bit
    rol	    r24			; (1) move test bit into CY.		5
    brcc    wuSkip02		; (f.1) (t.2) test bit. branch if 0 next.
    nop				; (1)					7
    nop				; (1)					8
    nop				; (1)					9
    jmp	    wuSkip01		; (3) ouput a 1 next.			12
;    
wuSkip02:			; next bit is a 0
    nop				; (1)					8
    nop				; (1)					9
    jmp	    wuLoop02		; (3)					12
    ;						0 end	1 end
wuSkip03:			; 0 Exit	6
    nop				; (1)		7
    nop				; (1)		8
wuSkip04:
    nop				; (1)		9	6
    nop				; (1)		10	7
    nop				; (1)		11	8
    nop				; (1)		12	9
    nop				; (1)		13	10
    nop				; (1)		14	11
    ;
    ret				; (4)		18	12
    ; could be reduced. (7) used by code to get next byte.
    