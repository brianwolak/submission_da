/*
 * GccApplication1.c
 *
 * Created: 4/6/2021 10:14:02 AM
 * Author : Brian
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile unsigned int pot;		//temporary read value from ADC
int delay = 0;					//OCR2A manipulation value
int loop = 0;					//timer looping value
char display1[20];				//display output string

//usart initialize
void USART_init(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}
//ADC initialize
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
	delay = (pot / 4);						//modify pot value for OCR2A
	if(delay < 20){							//check min pot value
		delay = 20;							//set min value if below 20
	}
	OCR2A = delay;							//set OCR2A to delay value
}

//timer setup
void timer_set(void){
	TCCR2A |= (0 << COM2A1) | (0 << COM2A0) | (1 << WGM21) | (0 << WGM20);		//mode 2 CTC top 0xFF non-invert
	TCCR2B |= (0 << WGM22) | (1 << CS22) | (1 << CS21) | (1 << CS20);			//1024 prescale set
}

void motor_delay(){
	TCNT2 = 0;					//reset timer2
	while (OCR2A != TCNT2);		//compare timer2 with OCR2A delay
	loop++;						//increment loop
}

int main(void)
{
	DDRB = 0x0F;			//set PORTD low bits to output
	int position = 0;		//motor position variable
	//initialize function call
	USART_init();
	//initialize function call
	adc_init();
	//initialize function call
	timer_set();
	//turn on interrupts
	sei();
	while (1)
	{
		read_adc();				//read pot value call
		motor_delay();			//motor delay call
		if(loop == 4){
			switch(position){
				case 0:					//motor case 0
					PORTB = 0x03;		//pin 0 and 1 high
					position++;			//increment position
					loop = 0;			//reset loop
					break;
				case 1:					//motor case 1
					PORTB = 0x06;		//pin 1 and 2 high
					position++;			//increment position
					loop = 0;			//reset loop
					break;
				case 2:					//motor case 2
					PORTB = 0x0C;		//pin 3 and 4 high
					position++;			//increment position
					loop = 0;			//reset loop
					break;
				case 3:					//motor case 3
					PORTB = 0x09;		//pin 0 and 3 high
					position = 0;		//reset position
					loop = 0;			//reset loop
					break;		
			}
		}
	}
}



