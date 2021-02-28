/*
 * GccApplication1.c
 *
 * Created: 2/27/2021 4:42:59 PM
 * Author : brian
 */ 

#define F_CPU 16000000UL	//define clock speed
#include <avr/io.h>
#include <util/delay.h>		//delay library
#include <avr/interrupt.h>	//interrupt library

int main(void)
{
	PORTD = 0x04;		//set pull up resistor
	EICRA = 0x02;		//set EICRA register for interrupts
	EIMSK = 0x01;		//setup EIMSK register for interrupt
	sei();				//turn on interrupts
	DDRB = 0xff; 		//initialize PORTB as output
	while (1)
	{
		PORTB = 0x00;	//PORTB pin 3 set to output
		_delay_ms(750); //delay 750ms
		PORTB = 0x08;	//PORTB pin 3 turns off
		_delay_ms(250); //delay 250ms
	}
}

ISR (INT0_vect){
	_delay_ms(2000);	//interrupt delay  2000ms
}



