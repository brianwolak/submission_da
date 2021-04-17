/*
 * GccApplication1.c
 *
 * Created: 4/13/2021 2:24:08 PM
 * Author : Brian
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile unsigned int pot;			//temp read value from ADC

//ADC initialize PC0 input
void adc_init(void){
	ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0 << MUX3) | (0 << MUX2) |
	(0 << MUX1) | (0 << MUX0);
	ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE) | (1
	<< ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

//read ADC value
void read_adc(void){
	ADCSRA |= (1 << ADSC);
	while((ADCSRA & (1 << ADIF))==0);		//wait for ADIF flag
	ADCSRA |= (1 << ADIF);					//reset ADIF flag
	pot = ADC;								//read value
}

//timer setup
void timer_set(void){
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);	//mode 3 fast PWM top 0xFF non-invert
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);	//1024 prescale set
}

int main(void)
{
	DDRB |= (1<<3);									//set PORT B output PIN3
	DDRD |= (1<<0) | (1<<1);						//set PORTD outputs 
	//initialize function call
	adc_init();
	//initialize function call
	timer_set();
	PORTD |= (1<<0);			//PINC0 high
	//PORTD &= ~(1<<1);			//PINC0 low
	
	while (1)
	{
		read_adc();						//read ADC
		OCR2A = pot /4;					//set OCR2A to pot2 value
	}
}


