/*
 * GccApplication1.c
 *
 * Created: 4/17/2021 12:13:49 PM
 * Author : Brian
 */ 

#define F_CPU 16000000UL	//clock speed
#define BAUD 9600			//baud rate
#define IMEM 20

#define Pvalue 1.2
#define Ivalue 1.2
#define Dvalue 1.2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <stdlib.h>
#include <stdio.h>

volatile uint16_t pot;						//global ADC variable
volatile uint32_t rev_count, tick1, tick2, cap1, 
cap2, cap3, cap4, avg1, avg2, tick_tot;
int count = 0, edge = 0, finish = 0, tick_count = 0;

volatile int16_t duty = 0, duty_max = 250;
volatile int32_t mean_I_err[IMEM], PID = 0, err_new = 0, err_old = 0,
mean_I_error = 0.0, I_err = 0.0,
P_err = 0, D_err = 0;
volatile uint16_t TIMER1ovf;				//overflow value
volatile float rpm, rps;
volatile double SETSPEED = 60, CURSPEED = 0;
char out[20], out1[20], out2[20];			//terminal print variables

//ADC initialize
void adc_init(void){
	ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (0<<MUX3) | (0<<MUX2) | (0 << MUX1) | (0 << MUX0);
	ADCSRA = (1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}
//ADC read
void read_adc(void){
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);			//wait for flag
	ADCSRA |= (1<<ADIF);					//clear flag
	pot = ADC;								//read ADC
}
//initialize USART
void USART_init(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}
//print to terminal function
void USART_tx_string(char *data){
	while((*data != '\0')){				//while the data string is not empty
		while(!(UCSR0A & (1<<UDRE0)));	//while the data regsiter is not empty
		UDR0 = *data;					//UDR0 register receives data
		data++;							//next data value
	}
}
//timer setup function
void timer_setup(void){
	//compare timer
	TCCR2A |= (1<<WGM21) | (1<<WGM20);
	TCCR2B |= (1<<CS22) | (1<<CS21) | ( 1<<CS20);
	TIMSK2 |= (1<<OCIE2A);
	//dc motor and capture timer
	TCCR1A |= (1<<COM1A1) | (1<<WGM11) | (1<<WGM10);	//mode 7 fast PWM
	TCCR1B |= (1<<ICES1) | (1<<WGM12) | (1<<CS10);		//prescale of 1
	TIMSK1 |= (1<<ICIE1) | (1<<TOIE1);					//interrupt set
}


int main(void)
{
	//DDRD |= (1<<0);								//set PORTD outputs
	DDRB |= (1<<1);								//set PORTB outputs
	PORTB |= (1<<0);							//set pull up resistor
	//setup functions
	timer_setup();
	adc_init(); 
	USART_init();
	sei();
	//initialize array
	for(int i = 0; i < IMEM-1; i++){
		mean_I_err[i] = (int32_t)0.0;
	}
	while (1)
	{
		rps = 15625.0 / tick_tot;			//calc revolutions per second
		rpm = rps*60;						//calc revolutions per minute
		CURSPEED = rpm;						//set RPM to curretn speed
		snprintf(out, sizeof(out), "%.2f ", (float)rpm);	//print speed
		USART_tx_string(out);
		USART_tx_string(" \r\n");
	}
}

//PID algorithm
ISR(TIMER2_COMPA_vect){
	err_old = err_new;				//save new error
	err_new = SETSPEED - CURSPEED;	//calc speed error
	P_err = err_new;				//save new to last
	mean_I_err[IMEM-1] = (int32_t)err_new;
	mean_I_error = 0;
	//shift left and add all
	for(int i=0; i<IMEM-1; i++){
		mean_I_err[i] = (int32_t)mean_I_err[i+1];
		mean_I_error += (int32_t)mean_I_err[i];
	}
	I_err = (int32_t)mean_I_error;
	D_err = (int32_t)err_new - err_old;
	//calc PID
	PID = (int32_t)Pvalue * P_err + Ivalue * I_err * .1 + Dvalue * D_err / .1;
	//PID out of bounds check
	if(PID > duty_max)
		PID = duty_max;
	else if(PID < 0)
		PID = 0;
	duty = (uint16_t)PID;
	OCR1A = duty * 7.5;		//OCR1A scale calculation
}
//PID CAPTURE ISR
ISR(TIMER1_CAPT_vect) {
//rising edge 1
if(count==0 && edge==0){
	tick1 = ICR1;			//save tick time stamp
	cap1 = (uint32_t)(tick1) + ((uint32_t)TIMER1ovf*0x0400L);
	rev_count++;			//increment revolution counter
	count++;				//increment count
	edge = 1;				//toggle edge value
	TCCR1B ^= (1 << ICES1); //toggle capture select
}
//falling edge 1
else if(count==1 && edge==1){
	tick1 = ICR1;			//save tick time stamp
	cap2 = (uint32_t)(tick1) + ((uint32_t)TIMER1ovf*0x0400L);
	rev_count++;			//increment revolution counter
	count++;				//increment count
	edge = 0;				//toggle edge value
	TCCR1B ^= (1 << ICES1); //toggle capture select
}
//rising edge 2
else if(count==2 && edge==0){
	tick1 = ICR1;			//save tick time stamp
	cap3 = (uint32_t)(tick1) + ((uint32_t)TIMER1ovf*0x0400L);
	rev_count++;			//increment revolution counter
	count++;				//increment count
	edge = 1;				//toggle edge value
	TCCR1B ^= (1 << ICES1);	//toggle capture select
}
//falling edge 2
else if(count==3 && edge==1){
	tick1 = ICR1;			//save tick time stamp
	cap4 = (uint32_t)(tick1) + ((uint32_t)TIMER1ovf*0x0400L);
	rev_count++;			//increment revolution counter
	count = 0;				//reset count
	edge = 0;				//toggle edge value
	TCCR1B ^= (1 << ICES1); //toggle capture select
	finish = 1;				//set final position value
}
//calculate avg / restart
if(finish == 1){
	avg1 = cap3 - cap1;		//avg1 calculation
	avg2 = cap4 - cap2;		//avg2 caclulation
	tick_tot = (avg1 + avg2) / 2;	//total ticks
	TCNT1 = 0;				//reset timer
	TIMER1ovf = 0;			//reset overflow
	finish = 0;				//reset final position value
}
}
//TIMER1 OVF ISR
ISR(TIMER1_OVF_vect) {
	TIMER1ovf++;			//increment overflow count
}

