;
; AssemblerApplication1.asm
;
; Created: 2/23/2021 10:44:16 AM
; Author : Brian
;


.org 0

INITIALIZE:
ldi r16, 0x00		;load r16 with 0 value
ldi r17, 0x08	;load r17 with 0x08 value
ldi r18, 0xff	;load r18 with 0xff value
ldi r19, 1		;load r19 with 1 value
ldi r20, 5		;load r20 with 5 for prescale value
ldi r21, 0xC6	;load r21 for 75% T1 low value
ldi r26, 0x2D	;load r26 for 75% T1 high value
ldi r27, 0x3D	;load r27 for 1 sec T1 high value
sts TCCR1A, r16	;timer 1 setup from r16
sts TCCR1B, r20 ;prescalar setup of 1024
out DDRB, r18	;setting DDRB at output

BEGIN:
out PORTB, r16	;set DDRB output to 0
sts TCNT1H, r16	;set timer1 high bits to zero
sts TCNT1L, r16 ;set timer1 low bits to zero

DELAY:
lds r22, TCNT1L		;T1L 75%
lds r23, TCNT1L		;T1L 100%
lds r24, TCNT1H		;T1H 75%
lds r25, TCNT1H		;T1H 100%
cp r22, r21			;compare r22 and r16
breq SUB1			;go to SUB if equal	
cp r23, r17			;compare r23 and r17
breq SUB2			;go to SUB2 if equal
rjmp DELAY			;restart delay

SUB1:
cp r24, r26			;compare 75% high timer values
breq TOGGLE			;to TOGGLE if same or higher
rjmp DELAY			;back to delay

SUB2:
cp r25, r27			;compare T1 full second time values
breq BEGIN			;if less than jump to DELAY
rjmp DELAY			;back to BEGIN

TOGGLE:
out PORTB, r17		;output 1 to PORTB
rjmp DELAY			;back to delay

