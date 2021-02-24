/*
 * GccApplication1.c
 *
 * Created: 2/23/2021 5:31:39 PM
 * Author : Brian
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;		//initialize PORTB as output

	while (1)
	{
		PORTB &= (1<<3);	//PORTB pin 3 set to output
		_delay_ms(750);		//delay 750ms
		PORTB |= ~(1<<3);	//PORTB pin 3 turns off
		_delay_ms(250);		//delay 250ms
	}
}



