/*
 * GccApplication1.c
 *
 * Created: 4/13/2021 11:11:39 AM
 * Author : Brian
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

int direction = 0;
volatile int count = 0;

//timer setup
void timer_set(void){
	//motor PWM timer
	TCCR2A |= (0 << COM2A1) | (1 << COM2A0) | (1 << WGM21) | (1 << WGM20);		//mode 7, OC2A toggle
	TCCR2B |= (1 << WGM22) | (1 << CS22) | (1 << CS21) | (1 << CS20);			//1024 prescale set
	OCR2A = 0x10;

	//delay timer
	TCCR1A |= (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (1 << CS10);
	TIMSK1 |=  (1 << OCIE1A);
	OCR1A = 0x3D07;
}

int main(void)
{
	DDRD |= (1<<2) | (1<<3);				//set PORTD output bits 2 & 3
	DDRB |= (1<<3);							//set PORTB output bit 3 (OC2A)
	//initialize function call
	timer_set();
	//turn on interrupts
	sei();
	while (1)
	{
		if (direction == 0){
			PORTD &= ~(1<<2);			//PINC2 low
			PORTD |= (1<<3);			//PINC3 high
		}

		if (direction == 1){
			PORTD |= (1<<2);			//PINC2 high
			PORTD &= ~(1<<3);			//PINC3 low
		}
	}
}

ISR(TIMER1_COMPA_vect){
	count++;				//increment 5s timer
	if (count == 5){		//check if 5s timer
	direction ^= 1;			//flip direction
	count = 0;				//reset timer
	}
}


