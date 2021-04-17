/*
 * GccApplication1.c
 *
 * Created: 4/17/2021 3:44:55 PM
 * Author : Brian
 */ 

#define F_CPU 16000000UL	
#define BAUD 9600	
		
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdlib.h>
#include <stdio.h>

volatile uint16_t pot;			//global pot variable
volatile float rpm, rps;		//rev per min, rev per sec
volatile uint32_t tick_rev;		//ticks per rev
volatile uint32_t rev_count;	//revolution count
volatile uint16_t TIMER1ovf;	//overflow value
volatile uint32_t tick1;		//temp tick value
volatile uint32_t tick_tot;		//total ticks
char display[20];				//print variable to terminal

//ADC initialze using PC0 input
void adc_init(void){
	ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (0<<MUX3) | (0<<MUX2) | (0 << MUX1) | (0 << MUX0);
	ADCSRA = (1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}
//ADC read
void read_adc(void){
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);		//wait for flag
	ADCSRA |= (1<<ADIF);				//clear flag
	pot = ADC;							//read ADC
	OCR1A = pot;						//set OCR1A
}
//USART initialize
void USART_init(void){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}
//print to terminal function
void USART_tx_string(char *data){
	while((*data != '\0')){				//while data is not empty
		while(!(UCSR0A & (1<<UDRE0)));	//while data register is not empty
		UDR0 = *data;					//UDR0 register gets data
		data++;							//next data value
	}
}
//timer setup 
void timer_setup(void){
		TCCR1A |= (1<<COM1A1) | (1<<WGM11) | (1<<WGM10);	//mode 7 fast PWM
		TCCR1B |= (1<<ICES1) | (1<<WGM12) | (1<<CS10);		//prescale of 1
		TIMSK1 |= (1<<ICIE1) | (1<<TOIE1);		//set bits for interrupts
}
//RPM calculate
void rpm_calc(void){
	rps = 15625.0 / tick_tot;		//calc rpm
	rpm = rps * 60;					//calc rps
	if(rpm < 5)						//check if RPM out of range
	rpm = 0;						//set RPM out of range
}


int main(void){
	DDRB |= (1<<1);				//output set
	PORTB |= (1<<0);			//pull up set
	//setup functions
	timer_setup();
	adc_init();
	USART_init();
	sei();
	while (1){
		read_adc();					//read ADC and set OCR1A
		rpm_calc();					//calulate rpm
		USART_tx_string("Motor RPM = ");
		snprintf(display, sizeof(display), "%.2f ", (float)rpm); //display rpm to terminal
		USART_tx_string(display);
		USART_tx_string(" \r\n");
	}
}//TIMER1 capture ISR
ISR(TIMER1_CAPT_vect) {
	tick1 = ICR1;			//record tick value
	tick_tot = (uint32_t)(tick1) + ((uint32_t)TIMER1ovf * 0x0400L);
	rev_count++;			//increment revolution count
	TCNT1 = 0;				//reset TIMER1
	TIMER1ovf = 0;			//reset overflow
}
//TIMER1 overflow 
ISR(TIMER1_OVF_vect) {
	TIMER1ovf++;			//increment overflow 
}


