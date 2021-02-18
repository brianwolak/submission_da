
.equ STARTADDS = 0x0400	;address begin of all numbers
.equ ypoint = 0x0500	;address begin of odd numbers
.equ zpoint = 0x0600	;address begin of even numbers
ldi r16, 0				;used to store low bits odd numbers
ldi r17, 0				;used to store mid bits odd numbers
ldi r18, 0				;used to store high bits odd numbers
ldi r19, 0				;used to store low bits even numbers
ldi r20, 0				;used to store mid bits even numbers
ldi r21, 0				;used to store high bits even numbers
ldi r22, 0x71			;total numbers used (112 in decimal) using 113 for proper counter usage
ldi r23, 0x21			;start of numbers to add
ldi r24, 0x01			;used to set carry flag in add/subtract

ldi xh, HIGH(STARTADDS)	;storing all numbers using xpointer
ldi xl, LOW(STARTADDS)
ldi yh, HIGH(ypoint)	;storing odd numbers using ypointer
ldi yl, LOW(ypoint)
ldi zh, HIGH(zpoint)	;storing even numbersing using zpointer
ldi zl, LOW(zpoint)

START:
cpi r22, 0				;check to see if counter is zero
breq END				;if counter is zero end program
st x+, r23				;store number from r23 to X register
mov r25, r23			;temporary store of current number
sub r22, r24			;decrement counter
ror r25					;odd/even check
brcs ODD				;if r25 odd branch to ODD
rjmp EVEN				;if r25 even jump to EVEN

ODD:
st y+, r23				;store odd number to Y register
add r16, r23			;add current number to odd sum
brcs ODDOVERFLOW		;if r27 rollover branch to ODDOVERFLOW		
inc r23					;increment current number
jmp START				;return to start

ODDOVERFLOW:
add r17,r24				;increment middle bit
brcs ODDOVERFLOW2		;branch to ODDOVERFLOW2 if carry set
inc r23					;increment current number
rjmp START

ODDOVERFLOW2:
add r18, r24			;increment highest bit values for odd 
inc r23					;increment current number
rjmp START				;return to start

EVEN:
st z+, r23				;store even number to X register
add r19, r23			;add current number to even sum
brcs EVENOVERFLOW		;if r23 
inc r23					;increment current number
jmp START				;back to start

EVENOVERFLOW:
add r20, r24			;increment middle even bits 
brcs EVENOVERFLOW2		;if overflow set branch to EVENOVERFLOW2
inc r23					;increment curent number
rjmp START				;return to start

EVENOVERFLOW2:
add r21, r24			;increment highest even bits
inc r23					;increment current number
rjmp START				;return to start

END:
rjmp END				;program ends
