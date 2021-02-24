/*
 * GccApplication1.c
 *
 * Created: 2/23/2021 4:43:12 PM
 * Author : Brian
 */ 

#define F_CPU 16000000UL	//define CPU
#include <avr/io.h>
#include <util/delay.h>		//delay library

int main(void){
	
	DDRB = 0xff;			//setting PORTB as output
	PORTC |= (1<<2);		//setting PORTB pullup on PIN2
	int count = 0;			//counter variable
	while (1)
	{
		count = 0;			//reset count
		PORTB |= (1<<3);	//turn on PB.3 LED
		_delay_ms(250);		//delay 250ms
		PORTB ^= (1<<3);	//turn PB.3 LED off
		_delay_ms(750);		//delay 750ms
		
		if((PINC & 0x08) ==0x08){
			while (count < 1){
				PORTB |= (1<<2);	//turn on PB.2 LED
				PORTB |= (1<<3);	//turn on PB.3 LED
				_delay_ms(250);
				PORTB ^= (1<<3);
				_delay_ms(750);		//delay 750ms
				PORTB |= (1<<3);	//turn off PB.3 LED
				_delay_ms(250);		//delay 250ms
				PORTB ^= (1<<3);	//turn on PB.2 LED
				_delay_ms(750);		//delay 750ms
				PORTB = 0x00;		//turn off all PB LEDS
				count++;			//increment count
			}
		}
		else{
			count = 0;				//reset count
			
		}
	}
}